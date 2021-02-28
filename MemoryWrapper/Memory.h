#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD GetProcID(const wchar_t* windowName);

uintptr_t FindBaseAddress(DWORD procID, const wchar_t* windowName);

uintptr_t FindAddress(HANDLE hProcess, uintptr_t baseAddress, std::vector<unsigned int> offsets);

int ReadMemory(HANDLE handle, uintptr_t target);

int WriteMemory(HANDLE handle, uintptr_t target, int newValue);
