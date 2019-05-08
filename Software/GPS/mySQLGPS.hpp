    #include <iostream>
    #include <string>
	#include <stdio.h>
	#include <string.h>
	
	//MySQL++ include
	#include <mysql/mysql.h>

    
    class mySQLGPS
    {
    	public:
    		mySQLGPS(std::string, std::string, std::string, std::string );
    		void mysql_connect(void);
			void mysql_disconnect(void);
			void mysql_sendQUERY(std::string);

    	private:
    		char DBHOST_[30];
    		char USER_[30];
    		char PASSWORD_[30];
    		char DATABASE_[30];
			MYSQL *mySQL;
    };
