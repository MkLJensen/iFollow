#include "getGPS.hpp"
#include <iostream>
#include <unistd.h>

//SQL Includes
#include "mySQLGPS.hpp"



#define DBHOST "localhost"
#define PORT 0
#define USER "Jesus"
#define PASSWORD "pi"
#define DATABASE "DatabaseGPS"



int main(void)
{

    while (1)
    {

    GPS myGPS("/dev/ttyAMA0");

    //SQL Declerations
    mySQLGPS sqlGPS(DBHOST, USER, PASSWORD, DATABASE, PORT);

    
    /*Updating Coordinates */
    myGPS.updateCoordinates();

    /* Making QUERY String */
    char executeQueryChar[300];
    int n = sprintf(executeQueryChar,"INSERT INTO `GPSData`(`nmeaType`, `fixTime`, `Latitude`, `Longitude`, `fixQuality`, `numOfSats`, `horizDilofPos`, `Altitude`, `heightofGeoID`, `checkSum`) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');",
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
    

    /* Connecting to DATABASE */
    sqlGPS.mysql_connect();

    std::cout << "Connected to mySQL Server" << std::endl;

    /* Sending QUERY */
    sqlGPS.mysql_secure_sendQUERY(executeQueryChar, myGPS);

    std::cout << "QUERY SENT" << std::endl;

    /* Closing Connecting to SQL Server */
    sqlGPS.mysql_disconnect();

    std::cout << "Diconnected from mySQL Server" << std::endl;
   
    sleep(30);

    }


    return 0;
}
