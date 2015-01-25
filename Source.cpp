//http://scripts.ge/topic/952-mysql-c-api-in-c-on-linux/

#include <iostream> 
#include <mysql.h>
#include <string.h> 
#include <cstdlib>
#include <string>
#include <my_global.h> 
#pragma comment(lib, "libmysql.lib")
using namespace std;


void clear(); 

void reset(); 


int main()
{


	MYSQL *connection = mysql_init(NULL);
	MYSQL_RES *result;
	MYSQL_ROW row;


	string shost;
	string suser;
	string spasswd;


	cout << " Input information" << endl;

	cout << " Host : ";
	cin >> shost;

	cout << " User : ";
	cin >> suser;

	cout << " Passwd : ";
	cin >> spasswd;

	const char *host = shost.c_str();
	const char *user = suser.c_str();
	const char *passwd = spasswd.c_str();

	connection = mysql_real_connect(connection, host, user, passwd, NULL, 0, NULL, 0);

	if (connection)
	{
		cout << " Connection Succeeded" << endl;
	}
	else
	{
		cout << " Connection failed!!!" << endl;
		mysql_library_end();
		return 0;
	}

	clear();
	cout << " You're logged in as : " << suser << "\n\n";

	const char *serverinfo;
	serverinfo = mysql_get_server_info(connection);
	cout << " Server Ifno : " << serverinfo << "\n";

	const char *hostinfo;
	hostinfo = mysql_get_host_info(connection);
	cout << " Host Info : " << hostinfo << "\n";

	unsigned int protoinfo;
	protoinfo = mysql_get_proto_info(connection);
	cout << " Protocol Info : " << protoinfo << "\n";

	const char *clientinfo;
	clientinfo = mysql_get_client_info();
	cout << " Client Info : " << clientinfo << "\n";

	cout << "\n";


	for (;;)
	{
		char archevani;
		do {

			cout << " Please choose your operation :\n\n";

			cout << " l --> Show databases list \n";
			cout << " s --> Choose database and work at it \n";
			cout << " d --> Work with database(), (create/delete) functions \n";
			cout << " u --> Change user \n";
			cout << " q --> Quit software \n\n";

			cout << " Your opinion is : ";
			cin >> archevani;
		} while (archevani == 'l' && archevani == 's' && archevani == 'd' && archevani == 'u' && archevani == 'q');


		if (archevani == 'q')
		{
			clear();
			cout << " Thanks for use our software. \n";
			mysql_close(connection);
			mysql_library_end();
			exit(0);
		}

		switch (archevani)
		{


		case 'l':
		{

			clear();

			cout << " Database List : \n";
			result = mysql_list_dbs(connection, NULL);
			while ((row = mysql_fetch_row(result)) != NULL)
			{
				cout << " \n" << row[0];
			} cout << " \n";
			mysql_free_result(result);

		} break;



		case 's':
		{

			clear();
			string schoosebase;

			const char *choosebase;

			char bazisarcheva;

			cout << " You must choose the database that you will work with. \n";

			do
			{

				cout << "Do you want databases list? y/other-key (q --> quit()) : ";
				cin >> bazisarcheva;

				if (bazisarcheva == 'y' || bazisarcheva == 'Y')
				{

					cout << " Database List : \n";

					result = mysql_list_dbs(connection, NULL);
					while ((row = mysql_fetch_row(result)) != NULL)
					{
						cout << "\n" << row[0];
					} cout << "\n";
					mysql_free_result(result);

				}

				else if (bazisarcheva == 'q')
				{
					clear();
					mysql_close(connection);
					mysql_library_end();
					exit(0);
				}


				cout << " Please choose database which you want to work with : ";
				cin >> schoosebase;

				choosebase = schoosebase.c_str();

				if ((mysql_select_db(connection, choosebase)))
				{
					cout << " Error occured : ";
					cout << mysql_errno(connection) << " : " << mysql_error(connection);
					cout << "\n";
				}
				else
				{
					clear();
					cout << " Database choosed \n";
				}

			} while ((mysql_select_db(connection, choosebase)) != 0);


			for (;;)
			{

				char archevani;

				cout << " Please choose your operation :\n\n";

				cout << " 1 --> show tables \n";
				cout << " 2 --> create table \n";
				cout << " 3 --> Add information (username,passwd,email) \n";
				cout << " 4 --> Add information from file \n";
				cout << " 5 --> Drop tables \n";
				cout << " r --> Return to main menu \n";

				cout << " Your opinion is : ";
				cin >> archevani;

				if (archevani == 'r')
				{
					clear();
					break;
				}

				if (archevani == '1')
				{
					clear();

					cout << "Table List in : " << schoosebase << " \n";
					result = mysql_list_tables(connection, NULL);
					while ((row = mysql_fetch_row(result)) != NULL)
					{
						cout << "\n" << row[0];
					}cout << "\n";
					mysql_free_result(result);

				}

				else if (archevani == '2')
				{

					string saddtable;

					cout << " Type your table's name ";
					cout << " name : ";
					cin >> saddtable;

					string ssaddtable;

					cout << " Type" << saddtable << "'s traits \n";
					cout << " For example : ID int(10) unsigned auto_increment primary key not null, username varchar(20) not null, password varchar(30) not null \n";
					cout << " Attributes(it's need edit,read this developer) : ";

					cin.get();
					getline(cin, ssaddtable);


					string sssaddtable = " CREATE TABLE " + saddtable + "(" + ssaddtable + ")";



					const char *addtable = sssaddtable.c_str();

					if ((mysql_real_query(connection, addtable, strlen(addtable))))
					{
						cout << " Error occured : ";
						cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
						cout << "\n";
					}
					else cout << " table " << saddtable << "Added successfully \n";


				}

				else if (archevani == '3')
				{
					clear();

					string tablename;

					cout << " Enter table's name,which you want to push information in it. \n";
					cout << " name : ";
					cin >> tablename;

					int informaciisraodenoba;
					int grafebisraodenoba;

					string grafname;

					cout << " Type graf's name,whic you want to push information int it. \n";
					cout << " For example : username,passwd,email \n";
					cout << " names : ";
					cin.get();
					getline(cin, grafname);


					cout << " How much informations do you want to push? \n";
					cout << " Informations quantity : ";
					cin >> informaciisraodenoba;

					string valuex;

					cout << " For example : 'username','passwd','email' \n";

					for (int x = informaciisraodenoba; x >= 1; x--)
					{

						cout << " Information : ";

						cin.get();
						getline(cin, valuex);

						string add = "insert into " + tablename + " (" + grafname.c_str() + ") value(" + valuex.c_str() + ")";

						const char *addtable = add.c_str();

						if ((mysql_query(connection, addtable)))
						{
							cout << " Error occured : ";
							cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
							cout << "\n";
							break;
						}
						else cout << " Information pushed successfully \n";
					}

				}


				else if (archevani == '4')
				{

					string stablename;

					cout << " Enter table's name,which you want to push information in it. \n";
					cout << " Name : ";
					cin >> stablename;

					string sloaddate;

					cout << " Type file address \n";
					cout << " Address : ";
					cin >> sloaddate;

					string ssloaddate = " LOAD DATA INFILE ' " + sloaddate + "' INTO TABLE " + stablename;

					const char *loaddate = ssloaddate.c_str();
					if ((mysql_query(connection, loaddate)))
					{
						cout << " Error occured : ";
						cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
						cout << "\n";
					}
					else cout << " Information pushed successfully \n";

				}

				else if (archevani == '5')
				{
					string sdroptable;

					cout << " Type table's name,which you want to remove :\n";
					cout << " name : ";
					cin >> sdroptable;

					string ssdroptable = " DROP TABLE " + sdroptable;

					const char *droptable = ssdroptable.c_str();

					if ((mysql_query(connection, droptable)))
					{
						cout << " Error occured : ";
						cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
						cout << "\n";
					}
					else cout << " Table '" << sdroptable << "' Removed successfully \n";

				}



			}

		} break;



		case 'd':
		{

			clear();

			for (;;)
			{

				char bazisarchevani;

				cout << " Please choose your operation :\n\n";

				cout << " l --> Databases list \n";
				cout << " c --> New database \n";
				cout << " d --> Remove database \n";
				cout << " r --> Return to main menu \n";

				cout << " Your opinion is : ";
				cin >> bazisarchevani;

				if (bazisarchevani == 'r')
				{
					clear();
					break;
				}

				if (bazisarchevani == 'l')
				{

					clear();

					cout << " Database List : \n";

					result = mysql_list_dbs(connection, NULL);
					while ((row = mysql_fetch_row(result)) != NULL)
					{
						cout << "\n" << row[0];
					} cout << "\n";
					mysql_free_result(result);


				}
				else if (bazisarchevani == 'c')
				{

					clear();

					string screatebasename;

					cout << " You want to add database : \n";

					cout << " Please type new database's name : ";
					cin >> screatebasename;

					string sscreatebasename = "CREATE DATABASE " + screatebasename;

					const char *createbasename = sscreatebasename.c_str();


					if ((mysql_query(connection, createbasename)))
					{
						cout << " Error occured : ";
						cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
						cout << "\n";
					}
					else cout << " Database '" << screatebasename << "' created successfully \n";

				}
				else if (bazisarchevani == 'd')
				{

					clear();

					char bazisarcheva;

					cout << " You want to remove database : \n";

					cout << " Do you want databases list? y/other-key : ";
					cin >> bazisarcheva;

					if (bazisarcheva == 'y' || bazisarcheva == 'Y')
					{

						cout << " Database List : \n";

						result = mysql_list_dbs(connection, NULL);
						while ((row = mysql_fetch_row(result)) != NULL)
						{
							cout << "\n" << row[0];
						} cout << "\n";
						mysql_free_result(result);

					}

					string sdropbasename;

					cout << " Please type database's name which you want to remove : ";
					cin >> sdropbasename;

					string ssdropbasename = "DROP DATABASE " + sdropbasename;

					const char *dropbasename = ssdropbasename.c_str();

					if ((mysql_query(connection, dropbasename)))
					{
						cout << " Error occured : ";
						cout << mysql_errno(connection) << " : " << mysql_error(connection) << "\n";
						cout << "\n";
					}
					else cout << " Database '" << sdropbasename << "' removed successfully \n";

				}

			}


		} break;



		case 'u':
		{

			clear();

			char changeuser;

			cout << " Do you want to change user? y/other-key : ";
			cin >> changeuser;

			if (changeuser == 'y' || changeuser == 'Y')
			{

				clear();

				string snewuser;
				string suserpasswd;

				cout << " Please type required information \n";

				cout << " User : ";
				cin >> snewuser;

				cout << " Passwd : ";
				cin >> suserpasswd;

				const char *newuser = snewuser.c_str();
				const char *userpasswd = suserpasswd.c_str();

				if (mysql_change_user(connection, newuser, userpasswd, NULL) == 0)
				{
					cout << " User changed to " << snewuser << " \n";
				}
				else cout << " User's change failed. Please check your information. \n\n";

			}
			else cout << " You have logged out of user's change function. \n\n";

		} break;


		}



	}

	mysql_close(connection);
	mysql_library_end();
};

void clear()
{ 

	cout << "\033c"; // Clears screen on linux.

}; 

void reset() 
{ 
	clear();
	main(); 

}; 