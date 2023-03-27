#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <filesystem>
#include <cstdlib>
#pragma comment(lib, "user32.lib")

#pragma warning(disable: 6271)

#include "Installer.h"
#include "Start.h"
#include "boot.h"
#include "Unistaller.h"
#include "System.h"

using namespace std;
namespace fs = std::filesystem;


void Uninst()
{
	string input;
	const char* frame = "CringeOS";

	cout << "				===== Welcome to CringeOS uninstaller 1.0.0v ===== \n" << endl;
	cout << "[+] Are you sure to uninstall system? T.T [y/n]" << endl;
	cin >> input;
	if (input == "y")
	{
		fs::remove_all(frame);
		printf("Complete!");
		exit(EXIT_SUCCESS);
		system("exit");

	}
	else
	{
		main();
	}
}

void helper(int inputdata)
{
	try
	{
		if (inputdata == 1)
		{
			Uninsthelp();
		}

		else if (inputdata == 2)
		{
			Uninst();
		}
		else if (inputdata == 3)
		{
			System1();
		}
		else
		{
			printf("Incorrect input, restart\n");
			Uninsthelp();
		}
	}
	catch (const std::exception&)
	{
		printf("Incorrect input, restart\n");
		Uninsthelp();
	}
}

void Uninsthelp()
{
	int input=0;
	printf("=== Help Page === \n");
	printf("[1] - view help page \n");
	printf("[2] - start uninstaller \n");
	printf("[3] - exit \n");
	printf("Enter number: ");
	cin >> input;
	helper(input);
	
}