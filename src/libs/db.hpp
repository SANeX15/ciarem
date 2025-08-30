#ifndef DB_H
#define DB_H

#include <mariadb/conncpp.hpp>
#include <string>

namespace db{
  // Returns a shared pointer to the database connection
  std::shared_ptr<sql::Connection> connect();
  
  // A helper function to close a connection
  void disconnect(std::shared_ptr<sql::Connection>& conn);
  
  // Authenticates a user with a username and password
  bool userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd);
}

#endif
