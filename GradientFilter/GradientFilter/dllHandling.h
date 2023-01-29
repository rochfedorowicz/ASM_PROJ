#pragma once
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <functional>
#include <chrono>

#include "functionTypes.h"

// Function loading DLL
bool loadDLL(HINSTANCE&, const LPCWSTR&);

// Function loading function from loaded DLL
bool loadDLLFunction(HINSTANCE&, BITMAP_CHANGE_FN_TYPE&, const LPCSTR&);

// Function freeing DLL
bool freeDLL(HINSTANCE&);

// Function instatiaing threads accordingly to number of them
void instantiateThreads(size_t, BITMAP_CHANGE_FN_TYPE&, BYTE*, DWORD, DWORD, BYTE*);

// Function measuring time of passed function wrapper
long long measureTime(const std::function<void()>&);