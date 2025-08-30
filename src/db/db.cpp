#include "../libs/db-conf.h"
#include "../libs/db.h"

namespace db {

std::shared_ptr<sql::Connection> connect() {
    try {
      // create a driver
      sql::Driver *driver = sql::mariadb::get_driver_instance();

      // setup the options to connect to the db
      sql::ConnectOptionsMap connectionOptions;
      connectionOptions["host"] = "localhost";
      connectionOptions["port"] = "3306";
      connectionOptions["user"] = dbCred::getUser();
      connectionOptions["password"] = dbCred::getPwd();
      connectionOptions["db"] = dbCred::getDbName();

      // if it is succesful, return it
      return std::shared_ptr<sql::Connection>(driver->connect(connectionOptions));
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

bool userAuth(std::shared_ptr<sql::Connection>& conn, std::string & uname, std::string & passwd){
  try {
      // create a statement
      std::unique_ptr<sql::Statement> stmt(conn->createStatement());

      // Execute a query using the statement
      std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT mobile, passwd FROM user"));

      std::string dbUname, dbPasswd;
      // Check the results
      while (res->next()) {
        dbUname = res->getString("username").c_str();
        dbPasswd = res->getString("password").c_str();
      }
      if (uname == dbUname && passwd == dbPasswd) {
        return true;
      }
      else {
        return false;
      }
      
    }
    catch (sql::SQLException &e) {
        return false;
    }
}
}



