#include "mySQLGPS.hpp"

mySQLGPS::mySQLGPS(std::string DBHOST, std::string USER, std::string PASSWORD, std::string DATABASE)
{
	strcpy(DBHOST_,DBHOST.c_str());
	strcpy(USER_, USER.c_str());
	strcpy(PASSWORD_, PASSWORD.c_str());
	strcpy(DATABASE_, DATABASE.c_str());
}


void mySQLGPS::mysql_connect(void)
{
   	mySQL = mysql_init(NULL);

    	if(mySQL == NULL) // Error connecting to Database
    	{
    		std::cout << "Error encountered" << mysql_error(mySQL) << std::endl;
    		return;
    	}

    	if(mysql_real_connect(mySQL, DBHOST_, USER_, PASSWORD_, DATABASE_, 0 , NULL, 0) ==  NULL )
		{
			std::cout << mysql_error(mySQL) << std::endl;
		}

    			
}

void mySQLGPS::mysql_disconnect(void)
{
	mysql_close(mySQL);
}

void mySQLGPS::mysql_sendQUERY(std::string QUERY)
{
	if(mySQL != NULL)
	{
		if(mysql_query(mySQL, QUERY.c_str()))
		{
			std::cout << mysql_error(mySQL) << std::endl;
			return;
		}
	}
}

