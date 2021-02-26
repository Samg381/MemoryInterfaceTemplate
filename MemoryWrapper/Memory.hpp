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


}