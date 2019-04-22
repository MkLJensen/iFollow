#include "getGPS.hpp"


GPS::GPS(std::string str)
{
    fileDescrip_ = str;
}

GPS::~GPS(void)
{
}

void GPS::updateCordinates(void)
{
    char bufferChar_[75]; // buffer for string
    std::string fileDescrip_ ="/dev/ttyAMA0";


    int dev = open(fileDescrip_.c_str(), O_RDWR | O_NOCTTY | O_SYNC);



    if (dev < 0) // checking if opening file has failed
    {
        std::cout << "could not open file" << std::endl;
    }
        std::cout << "file opened succesfully" << std::endl;

while (1) {
    int n = read(dev,bufferChar_,sizeof(bufferChar_));


    bufferString_ = std::string(bufferChar_);

    while(bufferString_.substr(0,6) != "$GPGGA")
            {
                n = read(dev,bufferChar_,sizeof(bufferChar_)); // Reading
                bufferString_ = std::string(bufferChar_);
            }

    bufferString_ = bufferString_.substr(0,72);
    std::cout << bufferString_ << std::endl;

  }

    close (dev);


                       
while(bufferString_.substr(0,1) != "\0")
                {
                    char nmeaCharBuffer_[30];
                    std::string caseBuffer_;
                    std::string nmeaStringBuffer_;
                    int difInPos;
                    int posOfComma2;
                    int posOfComma1 = 0;
                    std::size_t length;
                    size_t iFor;

                    
                    if (numOfComma == 2 || numOfComma == 3 || numOfComma == 7 || numOfComma == 8) 
                    {
                        posOfComma2 = bufferString_.find(",",posOfComma1+1);

                        numOfComma++;

                        difInPos = posOfComma2-posOfComma1;

                        length = bufferString_.copy(nmeaCharBuffer_,(difInPos+1),posOfComma1+1); 
                        nmeaCharBuffer_[length] = '\0';


                        nmeaStringBuffer_ = nmeaCharBuffer_;

                        posOfComma1 = posOfComma1+2;
                        posOfComma2 = posOfComma2+2;
                    }
                    else
                    {
                        posOfComma2 = bufferString_.find(",",posOfComma1+1);

                        numOfComma++;
                        difInPos = posOfComma2-posOfComma1;
                       
                        length = bufferString_.copy(nmeaCharBuffer_,difInPos-1,posOfComma1+1); 
                        nmeaCharBuffer_[length] = '\0';                     

                        nmeaStringBuffer_ = nmeaCharBuffer_;
                    }
                    

                        caseBuffer_ = nmeaStringBuffer_;
                        

                        switch (iFor)
                        {
                            case 0: 
                                setGpsType(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 1:
                                setfixTime(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 2:
                                setLatitude(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 3:
                                setLongitude(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 4:
                                setfixQuality(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 5:
                                setnumofSats(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 6:
                                sethDilutionofPos(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 7:
                                setaltitudeMeters(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 8:
                                sethOgGeoid(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 9:
                                bufferString_.replace(0,length+1,"");
                                break;
                            case 10:
                                setcheckSum(caseBuffer_);
                                bufferString_.replace(0,length+1,"");
                                break;
                                
                        }
                    iFor++;
                }

}