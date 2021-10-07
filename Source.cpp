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
	setlocale(LC_ALL, "Russian");
	DWORD nHigh = 0;
	DWORD nLow = 32767;
	HANDLE current_descriptor;
	char mf_name[MAX_KEY_LENGTH];
	LPVOID memory;
	wcout << "Enter the shared memory field' name: ";
	cin >> mf_name;
	cout << endl;
	LPCSTR mf_pointer = &mf_name[MAX_KEY_LENGTH];

	/*2*/
	OpenFileMappingA(NULL, FALSE, mf_pointer);
	DWORD err = GetLastError();
	cout << "Error # " << err;
	cout << endl;

	if (err == 2)
	{
		current_descriptor = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, nHigh, nLow, mf_pointer);
	}
	else
	{
		current_descriptor = OpenFileMappingA(NULL, FALSE, mf_pointer);
	}
	/*3*/
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
			fgets(input, sizeof(input), stdin);
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
		}
	} 
	while ( a == 0);
	UnmapViewOfFile(memory);
	CloseHandle(current_descriptor);
	return(0);
}
