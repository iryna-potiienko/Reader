// Reader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Psapi.h>
#include <iostream>
#include <memoryapi.h>
#include <Shlwapi.h>

#pragma warning(disable: 4996)
#pragma comment(lib, "Shlwapi")


int wmain(int argc, wchar_t* argv[]) {
	DWORD pid = _wtoi(argv[1]);
	LONGLONG address;
	CHAR buffer[100];
	SIZE_T bytesRead;
	StrToInt64Ex(argv[2], STIF_SUPPORT_HEX, &address);
	HANDLE process;
	if (!(process = OpenProcess(PROCESS_VM_READ, false, pid))) {
		std::cout << "An error occured! The process can't be opened";
	}
	else {
		_tprintf(_T("Reading address: 0x%I64x\nPID: %d\n"), address, pid);
		memset(buffer, 0x0, 100);
		if (!(ReadProcessMemory(process, (LPCVOID)address, (LPVOID)buffer, 95, &bytesRead))) {
			std::cout << "An error occured! Can't read the process' memory";
		}
		else {
			_tprintf(_T("Reading successfully completed! Read info: %hs\n"), buffer);
		}
	}
	return 0;
}