#ifndef DB_H
#define DB_H

#include <mariadb/conncpp.hpp>

namespace db{
  
  enum tbl{
  cust_tbl,
  sv_tbl,
  scrl_tbl
  };
  
  // Returns a shared pointer to the database connection
  std::shared_ptr<sql::Connection> retconn();

  void newEntry(std::shared_ptr<sql::Connection>& conn, tbl tblName, std::string values);
  
  // A helper function to close a connection
  void disconnect(std::shared_ptr<sql::Connection>& conn);
  
  // Authenticates a user with a username and password
  bool userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd);
}

#endif
