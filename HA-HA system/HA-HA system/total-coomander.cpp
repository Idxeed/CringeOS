#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>

#pragma comment(lib, "user32.lib")
#include "System.h"

using namespace std;
namespace fs = std::filesystem;
using std::filesystem::directory_iterator;


void printer(fs::path& path)
{
	auto current = fs::current_path();
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) {

			cout << entry.path().filename() << " DIR  " << endl;
		}
		if (entry.is_regular_file()) {
			cout << entry.path().filename() << " FILE " << endl;
		}

	}
}
	void sercher(fs::path& path, string parametr)
	{
		for (const auto& entry : fs::directory_iterator(path)) {
			if (entry.is_directory()) {
				cout << entry.path().filename() << " DIR  " << endl;
			}
			if (entry.is_regular_file()) {
				if (entry.path().extension() == parametr)
				{
					cout << entry.path().filename() << " FILE " << endl;
				}
			}
		}
	}
	void remover(fs::path& path)
	{
		string lol;
		cout << "Enter files or directories names what you want to delete:" << endl;
		cin >> lol;
		std::uintmax_t n = fs::remove_all(path / lol);
		std::cout << "Deleted " << n << " files or directories\n";
	}
	void creater(fs::path& path)
	{
		fs::create_directory(path);
	}
	void runner(fs::path& src)
	{
		ifstream file(src);
		cout << (file.is_open() ? "Y" : "N") << endl;
		string buffer;
		while (getline(file, buffer))
		{
			cout << buffer;
		}
		file.close();

	}

	void filesercher()
	{
		fs::path path;
		fs::path src;
		string parametr;
		int input;
		while (true)
		{
			printf("Choose number: \n");
			printf("[1] - view file on folder: \n");
			printf("[2] - search file or directory \n");
			printf("[3] - remove file or directory \n");
			printf("[4] - create file or directory \n");
			printf("[5] - open file(on host system) \n");
			printf("[0] - exit \n");
			printf("Your choose: ");
			cin >> input;
			try
			{
				switch (input)
				{
				case 0:
					System1();
					break;
				case 1:
					printf("Enter Path: ");
					cin >> path;
					printer(path);
					break;
				case 2:
					printf("Enter Path: ");
					cin >> path;
					sercher(path, parametr);
					break;

				case 3:
					printf("Enter Path: ");
					cin >> path;
					remover(path);
					break;
				case  4:
					printf("Enter Path: ");
					cin >> path;
					creater(path);
					break;
				case 5:
					printf("Enter source: ");
					cin >> src;
					runner(src);
					break;
				}
			}
			catch (const std::exception&)
			{
				printf("Error, restart! \n");
				filesercher();
			}

		}
	}