#pragma once
#include <windows.h>

// Function pointer consistnent with used function from DLLs 
typedef void(__cdecl* BITMAP_CHANGE_FN_TYPE)(BYTE*, DWORD, DWORD, BYTE*);