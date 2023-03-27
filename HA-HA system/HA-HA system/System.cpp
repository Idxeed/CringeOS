#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#pragma comment(lib, "user32.lib")

#include "Installer.h"
#include "Start.h"
#include "boot.h"
#include "Unistaller.h"
#include "filesercher.h"

using namespace std;

void System1();

class Sus
{
public:
	string username;
	ifstream filedata;
	void getUsername()
	{

		filedata.open("CringeOS/boot/username.txt");
		while (!filedata.eof())
		{
			if (username == "")
			{
				getline(filedata, username);
			}
			else
			{
				break;
			}
		}
		filedata.close();
	}
};

void commandChecker(string input1)
{
	if (input1 == "/uninstall")
	{
		Uninsthelp();
		System1();
	}
	if (input1 == "/filesercher")
	{
		filesercher();
		System1();
	}
	else
	{
		printf("crsh: unknown command \n");
	}
}

void System1()
{
	while (true)
	{
		Sus data;
		data.getUsername();
		string inputcomm;
		cout << "#@" << data.username << ":";
		cin >> inputcomm;
		commandChecker(inputcomm);
	}
}

