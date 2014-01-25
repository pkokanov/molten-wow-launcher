/*
 * Main.cpp
 *
 *  Created on: 22.01.2014
 *      Author: Plamen_2
 */

#include <string>
#include <iostream>
#include <Windows.h>

int GetVirtualKeyCode(char ch);
void GenerateKey(int vk , BOOL bExtended);

int main(int argc, char* argv[]) {

	std::string string = "D:\\Games\\HUHUE\\WoW.exe";
	LPCSTR lpApplicationName = string.c_str();
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// set the size of the structures
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// start the program up
	CreateProcess(lpApplicationName,   // the path
			NULL,           // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory
			&si,            // Pointer to STARTUPINFO structure
			&pi 	        // Pointer to PROCESS_INFORMATION structure
			);
	HWND wow;

	Sleep(10000);
	if(argc<2)
	{
		std::cout << "Not enough arguments";
		return 0;
	}
	std::cout << argv[1];
	for(int i=0; argv[1][i]!='\0'; i++)
	{
		int vCode = GetVirtualKeyCode(argv[1][i]);
		GenerateKey(vCode, FALSE);
		Sleep(1000);
	}
	GenerateKey(VK_RETURN, TRUE);
	// Close process and thread handles.12

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void GenerateKey(int vk, BOOL bExtended) {
	KEYBDINPUT kb = { 0 };
	INPUT Input = { 0 };
	// generate down
	if (bExtended)
		kb.dwFlags = KEYEVENTF_EXTENDEDKEY;
	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;

	Input.ki = kb;
	::SendInput(1, &Input, sizeof(Input));

	// generate up
	::ZeroMemory(&kb,sizeof(KEYBDINPUT));
	::ZeroMemory(&Input,sizeof(INPUT));
	kb.dwFlags = KEYEVENTF_KEYUP;
	if (bExtended)
		kb.dwFlags |= KEYEVENTF_EXTENDEDKEY;

	kb.wVk = vk;
	Input.type = INPUT_KEYBOARD;
	Input.ki = kb;
	::SendInput(1, &Input, sizeof(Input));
}

int GetVirtualKeyCode(char ch)
{
	if(ch>=65 && ch<=90)
		GenerateKey(VK_CAPITAL, TRUE);
	else if(ch>=97 && ch<=122)
		ch-=32;
	return ch;
}
