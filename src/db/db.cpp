#include "../libs/db-conf.hpp"
#include "../libs/db.hpp"

namespace db{
std::shared_ptr<sql::Connection> crmDB::retconn() {
    try {
      // create a driver
      sql::Driver *driver = sql::mariadb::get_driver_instance();

      // setup the options to connect to the db
      sql::SQLString url = dbCred::getUrl() + dbCred::getDbName();
      sql::Properties props({
        {"user",dbCred::getUser()},
        {"password",dbCred::getPwd()}
      });

      // if it is succesful, return it
      return std::shared_ptr<sql::Connection>(driver->connect(url,props));
    }
    catch (sql::SQLException & e){
      // else return a null
      return nullptr;
    }
}

void crmDB::getTbl(tbl tblName, std::string *table_name, std::string *cols, std::string *idCol){
  switch(tblName){
    case cust_tbl:
      *table_name = "customer";
      if (cols) *cols = "uid, name, dob";
      if (idCol) *idCol = "uid";
      break;
    case sv_tbl:
      *table_name = "service";
      if (cols) *cols = "id, name, price";
      if (idCol) *idCol = "id";
      break;
    case scrl_tbl:
      *table_name = "scroll";
      if (cols) *cols = "id, name, doe";
      if (idCol) *idCol = "id";
      break;
    default:
      return;
      break;
  }
}


void crmDB::disconnect(std::shared_ptr<sql::Connection>& conn) {
    if (conn && conn->isClosed() == false) {
        conn->close();
    }
}

bool crmDB::userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd){
  try {
      // create a statement
      std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT mobile, passwd FROM user WHERE mobile=? AND passwd=?"));
      pstmt->setString(1, uname);
      pstmt->setString(2, passwd);
      
      // Execute a query using the statement
      std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
      
      // Check if a matching record was found
      return res->next();
    }
    catch (sql::SQLException &e) {
        return false;
    }
}

std::string crmDB::newEntry(std::shared_ptr<sql::Connection>& conn, tbl tblName, const std::vector<std::string>& values){
  sql::SQLString query;
  std::string tbl_name, col_name, placeholders;
  getTbl(tblName, &tbl_name, &col_name);
  
  for (size_t i = 0; i < values.size(); ++i) {
      placeholders += "?,";
  }
  if (!placeholders.empty()) {
      placeholders.resize(placeholders.size() - 1); // Remove trailing comma
  }

  query = "INSERT INTO " + tbl_name + " (" + col_name + ") VALUES (" + placeholders + ")";
  
  try {
      std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
      switch (tblName) {
        case db::cust_tbl:
          // For customers, bind the first value as a number and the rest as strings
          pstmt->setInt64(1, std::stoll(values[0])); // UID
          pstmt->setString(2, values[1]);             // Name
          pstmt->setString(3, values[2]);             // DOB
          break;

        default:
          // For all other tables (Services, Scroll), bind all values as strings
          for (size_t i = 0; i < values.size(); ++i) {
              pstmt->setString(i + 1, values[i]);
          }
          break;
      }      pstmt->execute();
      return "";
  }
  catch (sql::SQLException e) {
    return e.what();
  }
}

std::string crmDB::remEntry(std::shared_ptr<sql::Connection>& conn, tbl tblName, const int64_t id){
  std::string tbl_name, idCol, query;
  getTbl(tblName, &tbl_name, nullptr, &idCol);

  query = "DELETE FROM " + tbl_name + " WHERE " + idCol + " = ?";
  try {
    std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
    switch(tblName){
      case db::cust_tbl:
        pstmt->setInt64(1, id);
        break;
      default:
        pstmt->setInt(1, id);
        break;
    }
    pstmt->execute();
    return "";
  } catch (sql::SQLException e) {
    return e.what();
  }
}

}
