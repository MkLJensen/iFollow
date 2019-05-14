#include "mySQLGPS.hpp"

mySQLGPS::mySQLGPS(std::string DBHOST, std::string USER, std::string PASSWORD, std::string DATABASE, unsigned int PORT)
{
	strcpy(DBHOST_,DBHOST.c_str());
	strcpy(USER_, USER.c_str());
	strcpy(PASSWORD_, PASSWORD.c_str());
	strcpy(DATABASE_, DATABASE.c_str());
	unsigned int PORT_ = PORT;
}


void mySQLGPS::mysql_connect(void)
{
   	mySQL = mysql_init(NULL);

    	if(mySQL == NULL) // Error connecting to Database
    	{
    		std::cout << "Error encountered" << mysql_error(mySQL) << std::endl;
    		return;
    	}

    	if(mysql_real_connect(mySQL, DBHOST_, USER_, PASSWORD_, DATABASE_, PORT_ , NULL, 0) ==  NULL )
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
			std::cout << "QUERY ADDED TO DATABASE" << std::endl;
			return;
		}
	}
}

unsigned int mySQLGPS::mysql_COUNT(void)
{
	mysql_query(mySQL,"SELECT COUNT(*) FROM GPSData");
	MYSQL_RES *res = mysql_store_result(mySQL);
	MYSQL_ROW row;

    if(row=mysql_fetch_row(res)){
		return (unsigned int) std::stoi(row[0]);
    }

}

void mySQLGPS::mysql_send_delete_row(void)
{
	mysql_query(mySQL, "DELETE FROM GPSData LIMIT 1");
}


void mySQLGPS::mysql_secure_sendQUERY(std::string QUERY, GPS myGPS)
{
	MYSQL_STMT *sql_statement;
	MYSQL_BIND sql_bind_parameters[10];

	sql_statement = mysql_stmt_init(mySQL);
		if(!sql_statement)
		{
			sql_error = 1;
		}

	if(mysql_stmt_prepare(sql_statement, QUERY.c_str(), strlen(QUERY.c_str())))
	{
		sql_error = 1;
	}

	param_count = mysql_stmt_param_count(sql_statement);

	//Reseting sql_bind_parameters to secure 0 in whole bind. 
	memset(sql_bind_parameters, 0, sizeof(sql_bind_parameters));


	//String GPSType
	char buffer[30];
	unsigned long str_length;

	str_length = sprintf(buffer,"%s",myGPS.getGpsType().c_str());
	sql_bind_parameters[0].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[0].buffer = (char*) &buffer;
	sql_bind_parameters[0].buffer_length = sizeof(buffer);
	sql_bind_parameters[0].is_null = 0;
	sql_bind_parameters[0].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getfixTime().c_str());
	sql_bind_parameters[1].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[1].buffer = (char*) &buffer;
	sql_bind_parameters[1].buffer_length = sizeof(buffer);
	sql_bind_parameters[1].is_null = 0;
	sql_bind_parameters[1].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getLatitude().c_str());
	sql_bind_parameters[2].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[2].buffer = (char*) &buffer;
	sql_bind_parameters[2].buffer_length = sizeof(buffer);
	sql_bind_parameters[2].is_null = 0;
	sql_bind_parameters[2].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getLongitude().c_str());
	sql_bind_parameters[3].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[3].buffer = (char*) &buffer;
	sql_bind_parameters[3].buffer_length = sizeof(buffer);
	sql_bind_parameters[3].is_null = 0;
	sql_bind_parameters[3].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getfixQuality().c_str());
	sql_bind_parameters[4].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[4].buffer = (char*) &buffer;
	sql_bind_parameters[4].buffer_length = sizeof(buffer);
	sql_bind_parameters[4].is_null = 0;
	sql_bind_parameters[4].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getnumOfSats().c_str());
	sql_bind_parameters[5].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[5].buffer = (char*) &buffer;
	sql_bind_parameters[5].buffer_length = sizeof(buffer);
	sql_bind_parameters[5].is_null = 0;
	sql_bind_parameters[5].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.gethDilutionofPos().c_str());
	sql_bind_parameters[6].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[6].buffer = (char*) &buffer;
	sql_bind_parameters[6].buffer_length = sizeof(buffer);
	sql_bind_parameters[6].is_null = 0;
	sql_bind_parameters[6].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getaltitudeMeters().c_str());
	sql_bind_parameters[7].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[7].buffer = (char*) &buffer;
	sql_bind_parameters[7].buffer_length = sizeof(buffer);
	sql_bind_parameters[7].is_null = 0;
	sql_bind_parameters[7].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.gethOgGeoid().c_str());
	sql_bind_parameters[8].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[8].buffer = (char*) &buffer;
	sql_bind_parameters[8].buffer_length = sizeof(buffer);
	sql_bind_parameters[8].is_null = 0;
	sql_bind_parameters[8].length = &str_length;

	str_length = sprintf(buffer,"%s",myGPS.getcheckSum().c_str());
	sql_bind_parameters[9].buffer_type = MYSQL_TYPE_STRING;
	sql_bind_parameters[9].buffer = (char*) &buffer;
	sql_bind_parameters[9].buffer_length = sizeof(buffer);
	sql_bind_parameters[9].is_null = 0;
	sql_bind_parameters[9].length = &str_length;

	//binding buffers
	if(mysql_stmt_bind_param(sql_statement,sql_bind_parameters))
	{
		sql_error = 1;
	}

	/* Executing QUERY */
	if(!sql_error)
	{
		if(mysql_stmt_execute(sql_statement))
		{
			sql_error = 1;
		}
	}

	/* Closing Statement */

	if(sql_statement)
	{
		if(mysql_stmt_close(sql_statement))
		{
			sql_error = 1;
		}
	}

}
