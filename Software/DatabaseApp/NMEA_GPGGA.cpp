#include "NMEA_GPGGA.hpp"

NMEA_GPGGA::NMEA_GPGGA(void)
{

}
/*Simple set and get Methods */
void NMEA_GPGGA::setGpsType(std::string str)
{
    gpsType_ = str;
}
void NMEA_GPGGA::setfixTime(std::string str)
{
    fixTime_ = str;
}
void NMEA_GPGGA::setLatitude(std::string str)
{
    Latitude_ = str;
}
void NMEA_GPGGA::setLongitude(std::string str)
{
    Longitude_ = str;
}
void NMEA_GPGGA::setfixQuality(std::string str)
{
    fixQuality_ = str;
}
void NMEA_GPGGA::setnumofSats(std::string str)
{
    numOfSats_ = str;
}
void NMEA_GPGGA::sethDilutionofPos(std::string str)
{
    hDilutionofPos_ = str;
}
void NMEA_GPGGA::setaltitudeMeters(std::string str)
{
    altitudeMeters_ = str;
}
void NMEA_GPGGA::sethOgGeoid(std::string str)
{
    hOfGeoid_ = str;
}
void NMEA_GPGGA::setcheckSum(std::string str)
{
    checkSum_ = str;
}

std::string NMEA_GPGGA::getGpsType(void)
{
    return gpsType_;
}
std::string NMEA_GPGGA::getfixTime(void)
{
    return fixTime_;
}
std::string NMEA_GPGGA::getLatitude(void)
{
    return Latitude_;
}
std::string NMEA_GPGGA::getLongitude(void)
{
    return Longitude_;
}
std::string NMEA_GPGGA::getfixQuality(void)
{
    return fixQuality_;
}
std::string NMEA_GPGGA::getnumOfSats(void)
{
    return numOfSats_;
}
std::string NMEA_GPGGA::gethDilutionofPos(void)
{
    return hDilutionofPos_;
}
std::string NMEA_GPGGA::getaltitudeMeters(void)
{
    return altitudeMeters_;
}
std::string NMEA_GPGGA::gethOgGeoid(void)
{
    return hOfGeoid_;
}
std::string NMEA_GPGGA::getcheckSum(void)
{
    return checkSum_;
}
