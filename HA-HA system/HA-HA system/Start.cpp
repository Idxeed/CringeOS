#include "Start.h"
#include "System.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#pragma comment(lib, "user32.lib")

#pragma warning(disable : 4715)

using namespace std;


class Sta1rt
{
public:
	string user;
	string pass;
	ifstream passwd;
	ifstream username;
	bool check;


	string getUsername()
	{

		username.open("CringeOS/boot/username.txt");
		while (!username.eof())
		{
			if (user == "")
			{
				getline(username, user);
				return user;
			}
			else
			{
				break;
			}
		}
		username.close();

	}
	string getPasswd()
	{

		passwd.open("CringeOS/boot/passwd.txt");
		while (!passwd.eof())
		{
			pass = "";
			getline(passwd, pass);
			return pass;
		}
		passwd.close();
	}

};

bool checkUsername(string& input)
{
	Sta1rt hi;
	string gg = hi.getUsername();
	if (input == gg)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

bool checkPasswd(string& input)
{
	Sta1rt hi;
	string gg = hi.getPasswd();
	if (input == gg)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void Startup_sys()
{
	Sta1rt g;
	string input;

	cout << "Welcome to CringeOS! \n" << endl;
	cout << "[+] Enter your username: " << endl;
	cin >> input;
	char y = 'y';
	while (y == 'y')
	{
		if (checkUsername(input))
		{
			cout << "Hello, " << input << endl;
			break;
		}
		else
		{
			printf("Error, can't find this user, restart \n");
			cout << "[+] Enter your username: " << endl;
			cin >> input;
			checkUsername(input);
			y = 'y';
		}
	}

	cout << "[+] Enter your password: ";
	cin >> input;
	while (y == 'y')
	{
		if (checkPasswd(input))
		{
			printf("Success! \n \n");
			break;
			
		}
		else
		{
			printf("Error, restart");
			checkPasswd(input);
			y = 'y';
		}
	}
	Sleep(1000);
	system("cls");
	System1();

}

