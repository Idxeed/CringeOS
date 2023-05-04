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

	//преобразование string в const wchar_t*
	wstring_convert <codecvt_utf8_utf16<wchar_t >> converter;
	wstring processname = converter.from_bytes(processName);
	const wchar_t* ProcessName = processname.c_str();


	//тут храним информацию о процессе
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	//делаем снапшот процессов 
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	//получаем 
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
	cout << "Введите название exe файла: ";
	cin >> exec;
	fstream file(format("CringeOS/user/{}.txt", exec));
	if (file.good())
	{
		DWORD PID = GetProcessPID(exec);
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
		if (hProcess == NULL)
		{
			DWORD error = GetLastError();
			printf("Не удалось открыть процесс (Ошибка %d)\n", error);
		}
		if(TerminateProcess(hProcess, 0)) {
			printf("Процесс %d успешно завершен\n", PID);
		}
		else {
			DWORD error = GetLastError();
			printf("Не удалось завершить процесс (Ошибка %d)\n", error);
		}

		CloseHandle(hProcess);
		PassiveScan();
	}
	else
	{
		cout << "Некорректно введено название файла или файла не существует\n";
	}
}


void CreateNewTask()
{
	Tasker task1{};
	string Exes;
	cout << "Введите название exe файла: ";
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
		cout << "Некорректно введено название файла или файла не существует\n";
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
		cout << "1. Добавить задачу\n";
		cout << "2. Удаление задачи\n";
		cout << "3. Показать список задач\n";
		cout << "4. Выйти\n";
		cout << "5. Справка\n";
		cout << "Выберите действие: ";
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
			cout << "Неверный формат ввода, повторите попытку";
			break;
		}
		

	}
}