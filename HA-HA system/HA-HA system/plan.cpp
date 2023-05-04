#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <fstream>
#include <windows.h>
#include <tlhelp32.h>
#include <locale>
#include <cassert>
#include <codecvt>
#include <cstdint>

#include "plan.h"
#include "System.h"

#pragma warning(disable  : 4996)

using namespace std;


struct Tasker
{
public:
	vector<string>tasklist;
};

void PassiveScan()
{
	Tasker task3{};
	for (int i = 0; i < task3.tasklist.size(); i++)
	{
		LPCSTR g = task3.tasklist.at(i).c_str();
		HWND hwnd = FindWindowA(NULL, g);
		if (hwnd == NULL)
		{
			task3.tasklist.erase(task3.tasklist.begin() - i);
		}
	}
}
DWORD GetProcessPID(string processName)
{

	//�������������� string � const wchar_t*
	wstring_convert <codecvt_utf8_utf16<wchar_t >> converter;
	wstring processname = converter.from_bytes(processName);
	const wchar_t* ProcessName = processname.c_str();


	//��� ������ ���������� � ��������
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	//������ ������� ��������� 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	//�������� 
	while (Process32First(snapshot, &entry) == true)
	{
		if (_wcsicmp(entry.szExeFile, ProcessName) == 0)
		{
			return entry.th32ProcessID;
		}
	}


}

void DeleteTask()
{
	Tasker task4{};
	string exec;
	cout << "������� �������� exe �����: ";
	cin >> exec;
	fstream file(format("CringeOS/user/{}.txt", exec));
	if (file.good())
	{
		DWORD PID = GetProcessPID(exec);
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
		if (hProcess == NULL)
		{
			DWORD error = GetLastError();
			printf("�� ������� ������� ������� (������ %d)\n", error);
		}
		if(TerminateProcess(hProcess, 0)) {
			printf("������� %d ������� ��������\n", PID);
		}
		else {
			DWORD error = GetLastError();
			printf("�� ������� ��������� ������� (������ %d)\n", error);
		}

		CloseHandle(hProcess);
		PassiveScan();
	}
	else
	{
		cout << "����������� ������� �������� ����� ��� ����� �� ����������\n";
	}
}


void CreateNewTask()
{
	Tasker task1{};
	string Exes;
	cout << "������� �������� exe �����: ";
	cin >> Exes;
	fstream file(format("CringeOS/user/{}.txt", Exes));
	if (file.good())
	{
		string path = format("path/to/{}.exe", Exes);
		system(path.c_str());
		task1.tasklist.push_back(Exes);
	}
	else
	{
		cout << "����������� ������� �������� ����� ��� ����� �� ����������\n";
	}

}

void viewAllTasks()
{
	Tasker task2;
	for (int i = 0; i < task2.tasklist.size(); i++)
	{
		cout << format("{}) {}.exe", i, task2.tasklist.at(i));
	}
}

void taskLinstener()
{
	PassiveScan();
	int choice = 0;
	while (true)
	{
		cout << "1. �������� ������\n";
		cout << "2. �������� ������\n";
		cout << "3. �������� ������ �����\n";
		cout << "4. �����\n";
		cout << "5. �������\n";
		cout << "�������� ��������: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			CreateNewTask();
			break;
		case 2:
			DeleteTask();
			break;
		case 3:
			PassiveScan();
			viewAllTasks();
			break;
		case 4:
			break;
		default:
			cout << "�������� ������ �����, ��������� �������";
			break;
		}
		

	}
}