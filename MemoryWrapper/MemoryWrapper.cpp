// MemoryWrapper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Memory.hpp"

int main()
{
    //---------- Global Variables -------------------------------------------------------------
    wchar_t windowName[1024] = L"ac_client.exe";       // Name of target application window   
    std::vector<unsigned int> ammoOffsets = { 0x384, 0x14, 0x0 };   // current weapon ammo offsets
    int pointerAddress = 0x10F4F4;
    //-----------------------------------------------------------------------------------------


    // Search for process ID
        DWORD procID = Memory::GetProcID(windowName);
        std::string checkPID = (procID == 0) ? "Process not found!" : "Process Detected! (";
        std::cout << checkPID << procID << ")" << std::endl;
   
    // Get a handle to access process
        HANDLE hProcess = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);
        std::string checkHandle = (hProcess == 0) ? "Failed to get handle!" : "Sucessfully opened handle! (";
        std::cout << checkHandle << hProcess << ")" << std::endl;

    // Find base address
        uintptr_t baseAddress = 0;
        baseAddress = Memory::FindBaseAddress(procID, windowName);
        std::string checkBaseAddress = (baseAddress == 0) ? "Failed to find base address!" : "Sucessfully found base address! (";
        uintptr_t pointerBaseAddress = baseAddress + pointerAddress;
        std::cout << checkBaseAddress << "0x" << std::hex << pointerAddress << ")" << std::endl;

    // Resolve pointer chain
        uintptr_t targetAddress = 0;
        targetAddress = Memory::FindAddress(hProcess, pointerBaseAddress, ammoOffsets);
        std::string checkAddress = (targetAddress == 0) ? "Failed to find target address!" : "Sucessfully found target address! (";
        std::cout << checkAddress << "0x" << std::hex << targetAddress << ")" << std::endl;

    // Read memory
        int ammoValue = Memory::ReadMemory(hProcess, targetAddress);
        std::cout << "Current Value: " << std::dec << ammoValue << std::endl;

    // Write memory
        int desiredAmmo = 69420;
        Memory::WriteMemory(hProcess, targetAddress, desiredAmmo);

    // Read memory again
        ammoValue = Memory::ReadMemory(hProcess, targetAddress);
        std::cout << "New Value: " << std::dec << ammoValue << std::endl;
}

