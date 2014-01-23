/*
 * Main.cpp
 *
 *  Created on: 22.01.2014
 *      Author: Plamen_2
 */

#include <string>
#include <Windows.h>

int main(int argc, char* argv[])
{

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
    // Close process and thread handles.
	HWND wow;

	// Get the handle of the WoW window.
	wow = FindWindow("World of Warcraft", NULL );
	if( wow == NULL )
		return 0;

	if( !SetForegroundWindow( wow ) )
	        return 0;

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

