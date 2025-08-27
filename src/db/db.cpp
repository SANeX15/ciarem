#include <mariadb/conncpp.hpp>
#include "../libs/db-conf.h"

sql::Driver * driver;
sql::SQLString url("jdbc:mariadb://localhost:3306/" + dbCred::getDbName());
sql::Properties props({{"user", "ciarem"},{"password", "151108"}});


bool connect(){
  try {
    if (driver != NULL){
      driver = sql::mariadb::get_driver_instance();
    }
    std::unique_ptr<sql::Connection> conn(driver->connect(url, props));
    return true;
  }
  catch (sql::SQLException & e){
    return false;
  }
}

bool disconnect(){}
