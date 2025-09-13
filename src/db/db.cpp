#include "../libs/db-conf.hpp"
#include "../libs/db.hpp"
#include <iostream>

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

void crmDB::disconnect(std::shared_ptr<sql::Connection>& conn) {
    if (conn && conn->isClosed() == false) {
        conn->close();
    }
}

bool crmDB::userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd){
  try {
      // create a statement
      std::unique_ptr<sql::Statement> stmt(conn->createStatement());

      // Execute a query using the statement
      std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT mobile, passwd FROM user WHERE mobile='" + uname + "' AND passwd='" + passwd + "'"));
      
      // Check if a matching record was found
      return res->next();
    }
    catch (sql::SQLException &e) {
        return false;
    }
}

template<typename T>
std::vector<T> crmDB::getEntries(std::shared_ptr<sql::Connection>& conn, tbl tblName){
  std::vector<T> entries;
  if(!conn){
    return entries;
  }

  std::string str_tbl_name, str_cols;

  switch (tblName) {
    case db::cust_tbl:
            str_tbl_name = "customer";
            str_cols = "uid, name, dob";
            break;
        case db::sv_tbl:
            str_tbl_name = "service";
            str_cols = "uid, name, dob";
            break;
        case db::scrl_tbl:
            str_tbl_name = "scroll";
            str_cols = "uid, name, dob";
            break;
    default:
      return entries;
      break;
  }
  try {
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery("SELECT " + str_cols + " FROM " + str_tbl_name));

    while(rs->next()){
      T entry;
      if (tblName == db::cust_tbl) {
              entry.uid = rs->getString("uid");
              entry.name = rs->getString("name");
              entry.dob = rs->getString("dob");
      }
      entries.push_back(entry);
    }
    
  } catch (sql::SQLException e) {
    std::cerr << "SQL Exception: " << e.what() << std::endl;
  }
  return entries;
}

std::string crmDB::newEntry(std::shared_ptr<sql::Connection>& conn, tbl tblName, const std::vector<std::string>& values){
  sql::SQLString query;
  std::string tbl_name, col_name, placeholders;
  switch (tblName) {
    case db::cust_tbl:
      tbl_name = "customer";
      col_name = "uid, name, dob";
      break;
    case db::sv_tbl:
      tbl_name = "service";
      col_name = "uid, name, dob";
      break;
    case db::scrl_tbl:
      tbl_name = "scroll";
      col_name = "uid, name, dob";
      break;
    default:
      return "invalid table";
  }
  
  for (size_t i = 0; i < values.size(); ++i) {
      placeholders += "?,";
  }
  if (!placeholders.empty()) {
      placeholders.resize(placeholders.size() - 1); // Remove trailing comma
  }

  query = "INSERT INTO " + tbl_name + " (" + col_name + ") VALUES (" + placeholders + ")";
  
  try {
      std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(query));
      for (size_t i = 0; i < values.size(); ++i) {
          pstmt->setString(i + 1, values[i]);
      }
      pstmt->execute();
      return "";
  }
  catch (sql::SQLException e) {
    return e.what();
  }
}
}
