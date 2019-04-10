#include "NMEA_GPGGA.hpp"

NMEA_GPGGA::NMEA_GPGGA(void)
{

}

void NMEA_GPGGA::setGpsType(std::string str)
{
    gpsType_ = str;
}