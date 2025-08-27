#include <iostream>
#include <mariadb/conncpp.hpp>
#include "../libs/db-conf.h"

// A namespace to encapsulate the database logic
namespace db {

// The connect function now returns a shared pointer to a Connection object.
// Using a shared pointer allows the connection to be shared safely among
// multiple parts of the application.
std::shared_ptr<sql::Connection> connect() {
    try {
        // We get the driver instance right before we need it. This avoids
        // potential issues with global object initialization order.
        sql::Driver *driver = sql::mariadb::get_driver_instance();

        // We create the connection options map on the stack.
        sql::ConnectOptionsMap connectionOptions;
        connectionOptions["host"] = "localhost";
        connectionOptions["port"] = "3306";
        connectionOptions["user"] = dbCred::getUser();
        connectionOptions["password"] = dbCred::getPwd();
        connectionOptions["db"] = dbCred::getDbName();

        // The connect function returns a unique_ptr. We convert it to a shared_ptr
        // and return it.
        return std::shared_ptr<sql::Connection>(driver->connect(connectionOptions));
    }
    catch (sql::SQLException & e){
        std::cerr << "SQLException: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        return nullptr;
    }
}

// The disconnect function is no longer needed since a shared_ptr
// will automatically close the connection when it goes out of scope.
// However, if you were using a raw pointer, you would implement it here.
void disconnect(std::shared_ptr<sql::Connection>& conn) {
    if (conn && conn->isClosed() == false) {
        conn->close();
    }
    // The shared_ptr will handle memory cleanup.
}

} // namespace db
