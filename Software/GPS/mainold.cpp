#include "getGPS.hpp"
#include <iostream>

//SQL Includes


#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define DBHOST "tcp://10.192.139.5:3306"
#define USER "Jesus"
#define PASSWORD "pi"
#define DATABASE "DatabaseGPS"


int main(void)
{
    GPS myGPS("/dev/ttyAMA0");

    //SQL Declerations
    sql::Driver *driver;
    sql::Connection *conn;
    sql::Statement *stmt;
    sql::ResultSet *res;

    /*Create a Connection*/
    driver = get_driver_instance();
    conn = driver->connect(DBHOST,USER,PASSWORD);

    /*Connecting to mySQL database */
    conn->setSchema(DATABASE);

    char executeQueryChar[1000];

    myGPS.updateCordinates();

    
    int n = sprintf(executeQueryChar,"INSERT INTO `GPSData`(`nmeaType`, `fixTime`, `Latitude`, `Longitude`, `fixQuality`, `numOfSats`, `horizDilofPos`, `Altitude`, `heightofGeoID`, `checkSum`) VALUES (`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`);",
        myGPS.getGpsType().c_str(),
        myGPS.getfixTime().c_str(),
        myGPS.getLatitude().c_str(),
        myGPS.getLongitude().c_str(),
        myGPS.getfixQuality().c_str(),
        myGPS.getnumOfSats().c_str(),
        myGPS.gethDilutionofPos().c_str(),
        myGPS.getaltitudeMeters().c_str(),
        myGPS.gethOgGeoid().c_str(),
        myGPS.getcheckSum().c_str()
        );

    std::string executeQueryString = executeQueryChar;
    
    stmt = conn->createStatement();
    res = stmt->executeQuery(executeQueryString);


    delete res;
    delete stmt;
    delete conn;

    return 0;
}
