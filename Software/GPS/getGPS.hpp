#ifndef GETGPS_HPP_ // include guard
#define GETGPS_HPP_

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "NMEA_GPGGA.hpp"

    class GPS : public NMEA_GPGGA
    {
    public:
        GPS(std::string);
        void updateCordinates(void);
        ~GPS();
    private:
        std::string fileDescrip_;
        std::string bufferString_;
        int numOfComma = 0;

        /*
        std::string gpsType_;
        std::string fixTime_;
        std::string Latitude_;
        std::string Longitude_;
        std::string fixQuality_;
        std::string numOfSats_;
        std::string hDilutionofPos_;
        std::string altitudeMeters_;            
        std::string hOfGeoid_;
        std::string checkSum_;
        */
    };

#endif /* Message */
