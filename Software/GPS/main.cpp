#include "getGPS.hpp"
#include <iostream>



int main(void)
{
    GPS myGPS("/dev/ttyAMA0");



        myGPS.updateCordinates();

        std::cout << "GPSType: " << myGPS.getGpsType() << std::endl;
        std::cout << "fixTime: " << myGPS.getfixTime() << std::endl;
        std::cout << " Lat: " << myGPS.getLatitude() << " Long: " << myGPS.getLongitude() << std::endl;
        std::cout << "fixQuality: " << myGPS.getfixQuality() << std::endl;
        std::cout << "Number of Satelites: " << myGPS.getnumOfSats() << std::endl;
        std::cout << "hDilutionofPos: " << myGPS.gethDilutionofPos() << std::endl;
        std::cout << "Altitude in Meters: " << myGPS.getaltitudeMeters() << std::endl;
        std::cout << "Geo ID: " << myGPS.gethOgGeoid() << std::endl;
        std::cout << "checkSum: " << myGPS.getcheckSum() << std::endl;
    return 0;
}
