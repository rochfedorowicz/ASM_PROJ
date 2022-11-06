#pragma once
#include <thread>
#include <vector>
#include <string>

#include "macros.h"

void instantiateThreads(const size_t&, const MY_FUN_PTR&);

bool loadDLLFunction(HINSTANCE&, const LPCWSTR&, MY_FUN_PTR&, const LPCSTR&);

bool freeDLL(HINSTANCE&);