#ifndef DB_H
#define DB_H

#include <mariadb/conncpp.hpp>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <memory>

namespace db{
  
  enum tbl{
  cust_tbl,
  sv_tbl,
  scrl_tbl
  };

  class crmDB{
    public :
      // Returns a shared pointer to the database connection
      std::shared_ptr<sql::Connection> retconn();

      void getTbl(tbl tblName, std::string *table_name, std::string *cols = nullptr, std::string *idCol = nullptr);
      
      template<typename T>
      std::vector<T> getEntries(std::shared_ptr<sql::Connection>& conn, tbl tblName){
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
            str_cols = "id, name, price";
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
      
      std::string newEntry(std::shared_ptr<sql::Connection>& conn, tbl tblName, const std::vector<std::string>& values);
      std::string remEntry(std::shared_ptr<sql::Connection>& coon, tbl tblName, const long id);
      
      // A helper function to close a connection
      void disconnect(std::shared_ptr<sql::Connection>& conn);
  
      // Authenticates a user with a username and password
      bool userAuth(std::shared_ptr<sql::Connection>& conn, const std::string& uname, const std::string& passwd);
  };
}

#endif
