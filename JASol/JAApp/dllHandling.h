#pragma once
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <functional>
#include <chrono>

#include "macros.h"
#include "functionTypes.h"

bool loadDLLFunction(HINSTANCE&, const LPCWSTR&, BITMAP_CHANGE_FN_TYPE&, const LPCSTR&);

bool freeDLL(HINSTANCE&);

void instantiateThreads(size_t, BITMAP_CHANGE_FN_TYPE&, BYTE*, DWORD, DWORD, BYTE*);

long long measureTime(const std::function<void()>&);