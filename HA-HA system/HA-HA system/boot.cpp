#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <io.h>
#pragma comment(lib, "user32.lib")

#pragma warning(disable: 6271)

#include "Installer.h"
#include "Start.h"

using namespace std;

class Systema
{
public:
	bool sys_startup;
};

void sys_dump()
{
	try
	{
		SYSTEM_INFO siSysInfo;
		GetSystemInfo(&siSysInfo);

		printf("Hardware information: \n");
		printf("OEM ID: %u\n", siSysInfo.dwOemId);
		printf("The number of process: %u\n", siSysInfo.dwNumberOfProcessors);
		printf("Processor type: %u\n", siSysInfo.dwProcessorType);
		printf("Complete! \n \n");
	}
	catch (const std::exception&)
	{
		printf("Can't get hardware information");
	}
	
}




bool Check_filedata()
{
	const char *fname = "CringeOS/boot/username.txt";
	_finddata_t data;
	long nFind = _findfirst(fname, &data);
	if (nFind != -1) {
		// Если этого не сделать то произойдет утечка ресурсов
		_findclose(nFind);
		return true;
	}
	return false;
}



void main()
{
	setlocale(LC_ALL, "ru");

	cout << "Welcome to Cringe OS \n \n" << endl; 
	cout << "Collect information about your fucking system... \n \n" << endl;
	sys_dump();
	cout << "Check system datafile" << endl;
	bool checker = Check_filedata();
	if (!checker)
	{
		cout << "Can't find filedata! You miss him? HA-HA! It's time to reinstall, daddy~ \n \n";
		Sleep(5000);
		system("cls");
		Install_sys();

	}
	else
	{
		cout << "Complete.... \n \n"<<endl;
		Sleep(5000);
		system("cls");
		Startup_sys();

	}

}