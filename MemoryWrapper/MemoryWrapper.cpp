// MemoryWrapper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Memory.hpp"

int main()
{
    // Search for process ID
    DWORD procID = Memory::GetProcID(L"ac_client.exe");
    std::string checkPID = (procID == 0) ? "Process not found!" : "Process Detected! (";
    std::cout << checkPID << procID << ")";
   
    // Get a handle to access process
    HANDLE hProcess = 0;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

    // Find base address

}

