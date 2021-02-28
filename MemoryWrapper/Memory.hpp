#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <stdint.h>
#include <iostream>
#include "Memory.h"

namespace Memory
{
	DWORD GetProcID(const wchar_t* proc_name)
	{
		DWORD procID = 0;
		auto* const h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (h_snap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 proc_entry;
			proc_entry.dwSize = sizeof(proc_entry);

			if (Process32First(h_snap, &proc_entry))
			{
				do
				{
					if (!_wcsicmp(proc_entry.szExeFile, proc_name))
					{
						procID = proc_entry.th32ProcessID;
						break;
					}
				} while (Process32Next(h_snap, &proc_entry));
			}
		}
		CloseHandle(h_snap);
		return procID;
	}

	uintptr_t FindBaseAddress(const DWORD procID, const wchar_t* windowName)
	{
		uintptr_t baseAddress = 0;
		auto* const h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);

		if (h_snap != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 mod_entry;
			mod_entry.dwSize = sizeof(mod_entry);

			if (Module32First(h_snap, &mod_entry))
			{
				do
				{
					if (!_wcsicmp(mod_entry.szModule, windowName))
					{
						baseAddress = reinterpret_cast<uintptr_t>(mod_entry.modBaseAddr);
						break;
					}
				} while (Module32Next(h_snap, &mod_entry));
			}
		}
		CloseHandle(h_snap);
		return baseAddress;
	}

	uintptr_t FindAddress(HANDLE hProcess, uintptr_t baseAddress, std::vector<unsigned int> offsets)
	{
		auto address = baseAddress;
		std::cout << address << std::endl;

		for (auto offset : offsets)
		{
			ReadProcessMemory(hProcess, reinterpret_cast<BYTE*>(address), &address, sizeof(address), nullptr);
			address += offset;
			std::cout << address << std::endl;
		}

		return address;
	}

	int ReadMemory(HANDLE handle, uintptr_t target)
	{
		int memoryValue = 0;
		ReadProcessMemory(handle, (BYTE*)target, &memoryValue, sizeof(memoryValue), nullptr);
		return memoryValue;
	}

	int WriteMemory(HANDLE handle, uintptr_t target, int newValue)
	{
		WriteProcessMemory(handle, (BYTE*)target, &newValue, sizeof(newValue), nullptr);
		return newValue;
	}
}