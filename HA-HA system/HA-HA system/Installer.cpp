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

using namespace std;
namespace fs = std::filesystem;
class GiveData
{
public:
	string input;
	int num;
	string passwd;
	bool change;


};

void Install_sys()
{
	cout << "				===== Welcome to CringeOS installer 1.0.0v ===== \n" << endl;
	GiveData data;
	ofstream passwd;
	ofstream username;


	//create dir 
	cout << "[+] Creating filesystem ..." << endl;
	try
	{
		fs::create_directory("CringeOS");
		fs::create_directory("CringeOS/boot");
		fs::create_directory("CringeOS/swap");
		fs::create_directory("CringeOS/data");
		fs::create_directory("CringeOS/user");
	}
	catch (const std::exception&)
	{
		cout << "Can't create filesystem, goodby noob!"<<endl;
	}

	//open txt file 
	cout << "[+] Creating datafiles in CringeOS/boot ..." << endl;
	try
	{
		username.open("CringeOS/boot/username.txt");
		username.close();
		passwd.open("CringeOS/boot/passwd.txt");
		passwd.close();

	}
	catch (const std::exception&)
	{
		cout << "Can't create datafiles, goodby noob!" << endl;
	}
	cout << "[+] Now, pls tell me your username: " << endl;
	cin >> data.input;
	cout << "Seruoisly?...." << endl;
	cout << "[+] Saving..." << endl;
	try
	{
		username.open("CringeOS/boot/username.txt");
		username << data.input;
		username.close();
	}
	catch (const std::exception&)
	{
		cout << "Can't save username in datafiles, goodby noob!" << endl;
	}
	
	//take passws
	cout << "[+] Now, pls tell me your password: " << endl;
	cin >> data.passwd;
	cout << "[+] Saving..." << endl;
	try
	{
		passwd.open("CringeOS/boot/passwd.txt");
		passwd << data.passwd;
		passwd.close();
	}
	catch (const std::exception&)
	{
		cout << "Can't save password in datafiles, goodby noob!" << endl;
	}

	cout << "[+] Install complete! Start system..." << endl;
	Sleep(5000);
	system("cls");
	Startup_sys();


}