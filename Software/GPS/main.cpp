#include "getGPS.hpp"
#include <iostream>



int main(void)
{
    GPS myGPS("/dev/ttyAMA0");


    while(1){
    
        myGPS.updateCordinates();


        std::cout << " Lat: " << myGPS.getLatitude() << " Long: " << myGPS.getLongitude() << std::endl;
        
    }
    return 0;
}