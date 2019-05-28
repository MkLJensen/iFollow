    #include <iostream>
    #include <string>
    
    class NMEA_GPGGA
    {
        public:
            NMEA_GPGGA(void);

            void setGpsType(std::string);
            void setfixTime(std::string);
            void setLatitude(std::string);
            void setLongitude(std::string);
            void setfixQuality(std::string);
            void setnumofSats(std::string);
            void sethDilutionofPos(std::string);
            void setaltitudeMeters(std::string);
            void sethOgGeoid(std::string);
            void setcheckSum(std::string);

            std::string getGpsType(void);
            std::string getfixTime(void);
            std::string getLatitude(void);
            std::string getLongitude(void);
            std::string getfixQuality(void);
            std::string getnumOfSats(void);
            std::string gethDilutionofPos(void);
            std::string getaltitudeMeters(void);
            std::string gethOgGeoid(void);
            std::string getcheckSum(void);

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