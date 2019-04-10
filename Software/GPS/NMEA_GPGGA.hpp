    #include <iostream>
    #include <string>
    
    class NMEA_GPGGA
    {
        public:
            NMEA_GPGGA(void);
            void setGpsType(std::string);
        private:
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

    };