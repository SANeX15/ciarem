#include <mariadb/conncpp.hpp>

namespace db{
  std::shared_ptr<sql::Connection> connect();
  void disconnect(std::shared_ptr<sql::Connection>& conn));
  bool userAuth(std::shared_ptr<sql::Connection>& conn, std::string * uname, std::string * passwd));
}
