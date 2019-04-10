#include "getGPS.hpp"
#include <fstream>

GPS::GPS(std::string str)
{
    fileDescrip_ = str;
}

GPS::~GPS(void)
{
}

std::string GPS::getLatitude(void)
{
    return Latitude_;
}

std::string GPS::getLongitude(void)
{
    return Longitude_;
}

void GPS::updateCordinates(void)
{
    
    bool readError = true; // fla for error check
    char bufferChar_[300]; // buffer for string
    std::size_t posOfComma1 = 0, posOfComma2;

    std::ifstream inFile (fileDescrip_); //Opening file 
    int longofFileDe = inFile.tellg(); // getting size of file

    if (inFile.fail()) // checking if opening file has failed
    {
        Latitude_ = "Failed to get latitude GPS Data"; // GPS example string : $GPGGA,091224.00,5610.35994,N,01011.51373,E,1,07,1.49,59.3,M,42.8,M,,*68
        Longitude_ = "Failed to get Longitude GPS Data";
    }

    inFile.read(bufferChar_,longofFileDe);
    std::string bufferString_(bufferChar_);

    if(inFile)
    {
            while(bufferString_.substr(0,6) != "$GPGGA")
            {    
                inFile.read(bufferChar_,longofFileDe); // Reading 
                std::string bufferString_(bufferChar_);
            }


        readError = false;

                       
                while(bufferString_.substr(0,2) != "\0")
                {
                    char* nmeaCharBuffer_;
                    char* caseBuffer_;
                    std::string nmeaStringBuffer_;
                    int difInPos;
                    int numOfComma = 0;

                    if (numOfComma != 3 || 4) 
                    {
                       
                        posOfComma2 = bufferString_.find(",",posOfComma1+1);

                        numOfComma++;

                        difInPos = posOfComma2-posOfComma1;

                        bufferString_.copy(nmeaCharBuffer_,difInPos+2,posOfComma1+1); 

                        nmeaStringBuffer_ = std::string(nmeaCharBuffer_);

                        posOfComma1 = posOfComma1+2;
                        posOfComma2 = posOfComma2+2;
                    }
                    else
                    {
                        posOfComma2 = bufferString_.find(",",posOfComma1+1);

                        numOfComma++;

                        difInPos = posOfComma2-posOfComma1;

                        bufferString_.copy(nmeaCharBuffer_,difInPos,posOfComma1+1); 

                        nmeaStringBuffer_ = std::string(nmeaCharBuffer_);
                    }
                    
                
                    for(size_t i = 0; i < 10; i++)
                    {
                        nmeaStringBuffer_.copy(caseBuffer_,difInPos,posOfComma1+1);
                        switch (i)
                        {
                            case 0: 
                                gpsType_ = std::string(caseBuffer_);
                                break;
                            case 1:
                                fixTime_ = std::string(caseBuffer_);
                                break;
                            case 2:
                                Latitude_ = std::string(caseBuffer_);
                                break;
                            case 3:
                                Longitude_ = std::string(caseBuffer_);
                                break;
                            case 4:
                                fixQuality_ = std::string(caseBuffer_);
                                break;
                            case 5:
                                numOfSats_ = std::string(caseBuffer_);
                                break;
                            case 6:
                                hDilutionofPos_ = std::string(caseBuffer_);
                                break;
                            case 7:
                                altitudeMeters_ = std::string(caseBuffer_);
                                break;
                            case 8:
                                hOfGeoid_ = std::string(caseBuffer_);
                                break;
                            case 9:
                                checkSum_ = std::string(caseBuffer_);
                                break;
                        }
                    }
                }

        inFile.close();
        return;
    }
    readError = true;
    std::cout << "error reading. size of read data: " << inFile.gcount() <<std::endl;


    inFile.close();


}