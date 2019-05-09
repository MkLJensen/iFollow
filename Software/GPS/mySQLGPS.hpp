    #include <iostream>
    #include <string>
	#include <stdio.h>
	#include <string.h>
	
	//MySQL++ include
	#include <mysql/mysql.h>

	#include "getGPS.hpp"

    
    class mySQLGPS : public GPS
    {
    	public:
    		mySQLGPS(std::string, std::string, std::string, std::string, unsigned int );
    		void mysql_connect(void);
			void mysql_disconnect(void);
			void mysql_sendQUERY(std::string);

			void mysql_secure_sendQUERY(std::string,GPS);

    	private:
    		char DBHOST_[30];
    		char USER_[30];
    		char PASSWORD_[30];
    		char DATABASE_[30];
			unsigned int PORT_;
			MYSQL *mySQL;
			
			bool sql_error = false;
			int param_count;
    };
