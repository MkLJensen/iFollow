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

std::string LongitudeOld = "00000000";
std::string LatitudeOld = "00000000";



int main(void)
{

    GPS myGPS("/dev/ttyAMA0");

    //SQL Declerations
    mySQLGPS sqlGPS(DBHOST, USER, PASSWORD, DATABASE, PORT);

    myGPS.updateCoordinates();

    while (1)
    {

    while( (myGPS.getLongitude().substr(0,8) == LongitudeOld.substr(0,8)) || (myGPS.getLatitude().substr(0,7) == LatitudeOld.substr(0,7)) )
    {    
    /*Updating Coordinates */
    myGPS.updateCoordinates();
    }

    LongitudeOld = myGPS.getLongitude();
    LatitudeOld = myGPS.getLatitude();

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

    /*CHECKING COUNT */
    while(sqlGPS.mysql_COUNT() >= 25)
    {
        sqlGPS.mysql_send_delete_row();
    }


    /* Sending QUERY */
    sqlGPS.mysql_secure_sendQUERY(executeQueryChar, myGPS);

    std::cout << "QUERY SENT" << std::endl;

    /* Closing Connecting to SQL Server */
    sqlGPS.mysql_disconnect();

    std::cout << "Diconnected from mySQL Server" << std::endl;
   
    sleep(4);

    }


    return 0;
}
