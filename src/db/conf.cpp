#include "../libs/db-conf.hpp"

namespace dbCred {
  const std::string getUser() {
    return "ciarem";
  }

  const std::string getPwd() {
    return "151108";
  }

  const std::string getUrl() {
    return "jdbc:mariadb://localhost:3306/";
  }

  const std::string getDbName() {
    return "ciarem";
  }
}
