#include "../libs/db-conf.hpp"
#include <memory>
#include "../libs/db.hpp"

namespace db {
std::shared_ptr<sql::Connection> retconn() {
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

void disconnect(std::shared_ptr<sql::Connection>& conn) {
    if (conn && conn->isClosed() == false) {
        conn->close();
    }
}

bool userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd){
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
}

void newEntry(std::shared_ptr<sql::Connection>& conn, int tbl_name, std::string values){
  sql::SQLString tblName, colName;
  switch (tbl_name) {
    case db::cust_tbl:
      tblName = "customer";
      colName = "uid, name, dob";
      break;
    case db::sv_tbl:
      tblName = "services";
      break;
    case db::scrl_tbl:
      tblName = "scroll";
      break;
    default:
      tblName = NULL;
      break;
  }
  try {
      std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO ? (?) VALUES (?)"));
  }
  catch (sql::SQLException e) {
  
  }
}
