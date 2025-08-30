#ifndef DB_CONF_H
#define DB_CONF_H

#include<string>

namespace dbCred{
  const std::string getUser();
  const std::string getPwd();
  const std::string getUrl();
  const std::string getDbName();
}

#endif
