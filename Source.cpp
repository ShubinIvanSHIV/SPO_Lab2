#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <Lmcons.h>
#include <cstdlib>
#include <tchar.h>
#define WINVER 0x0502
#define BUFSIZE MAX_PATH 
#define FILESYSNAMEBUFSIZE MAX_PATH
#define MAX_KEY_LENGTH 255
#pragma warning(disable : 4996)
#define BUFFER_SIZE 32767;
using namespace std;

int main()
{
	/*1*/
	DWORD nHigh = 0;
	DWORD nLow = 32767;
	HANDLE current_descriptor = INVALID_HANDLE_VALUE;
	char mf_name[MAX_PATH];
	LPVOID memory;
	wcout << "Enter the shared memory field' name: ";
	cin >> mf_name;
	cout << endl;

	/*2*/
	OpenFileMappingA(NULL, FALSE, &mf_name[0]);
	DWORD err = GetLastError();
	cout << endl;

	if (err != ERROR_FILE_EXISTS)
	{
		current_descriptor = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, nLow, &mf_name[0]);
	}
	else
	{
		current_descriptor = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, &mf_name[0]);
	}
	/*3*/
	if (current_descriptor != NULL)

	{
		memory = MapViewOfFile(current_descriptor, FILE_MAP_ALL_ACCESS, 0, 0, nLow);
		/*4*/
		int indicator;
		int a = 0;
		do
		{
			cout << "Enter 1 for writing, 2 for reading, 3 for exit: ";
			cin >> indicator;
			cout << endl;
			if (indicator == 1)
			{
				auto message = reinterpret_cast<char*>(memory);
				cout << "Enter the message: ";
				char input[128];
				cin >> input;
				strcpy(message, input);
			}
			else if (indicator == 2)
			{
				printf("Message from shared memory: %s\n", memory);
				cout << endl;
			}
			else if (indicator == 3)
			{
				cout << "Exited" << endl;
				a = 1;
			}
			else
			{
				cout << "Error:Unrecognized identificator value" << endl;
				a = 1;
			}
		} while (a == 0);
		UnmapViewOfFile(memory);
		CloseHandle(current_descriptor);
		return(0);
	}
	else
	{
		printf("Could not create file mapping object (%d).\n"),
			GetLastError();
		return 1;
	}
}
