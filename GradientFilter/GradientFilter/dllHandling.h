//////////////////////////////////////////////////////////////////////////////
//																			//
//	Project topic: Gradient filtering (north direction)						//
// 																			//
//	Short description of algorithm: 										//
//	Filtering with mask 3x3 by iterating over bytes and its neighbourhood.	//
//	Multiplied bytes are summed and then divided to calculate new value		//
//	achiving brighter colours for horizontal edges and detecting them.		//
//																			//
//	Date: 28.01.2023														//
//																			//
//	Semester: 5																//
//																			//
//	Academic year: 22/23													//
//																			//
//	Author: Roch Fedorowicz													//
//																			//
//	Version: 1.0															//
//																			//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <functional>
#include <chrono>

#include "functionTypes.h"

// Function loading DLL
// Input parameters:
//	• HINSTANCE _hinstLib - empty library handler
//	• LPCWSTR _libName - library name
// Output parameter:
//	• bool - value indicating if function succeeded
bool loadDLL(HINSTANCE&, const LPCWSTR&);

// Function loading function from loaded DLL
// Input parameters:
//	• HINSTANCE _hinstLib - loaded library handler
//  • BITMAP_CHANGE_FN_TYPE _procAddress - empty function handler
//	• LPCWSTR _libName - function name
// Output parameter:
//	• bool - value indicating if function succeeded
bool loadDLLFunction(HINSTANCE&, BITMAP_CHANGE_FN_TYPE&, const LPCSTR&);

// Function freeing DLL
// Input parameters:
//	• HINSTANCE _hinstLib - library handler to be freed
// Output parameter:
//	• bool - value indicating if function succeeded
bool freeDLL(HINSTANCE&);

// Function instatiaing threads accordingly to number of them
// Input parameters:
//	• size_t _numberOfThreads - number of threads that function should be instantiate with
//	• BITMAP_CHANGE_FN_TYPE _functionPointer - function to instantiate
//	• BYTE* _inputByteData - byte pointer to input data
//	• DWORD _height - height of data table pointed by _inputByteData
//	• DWORD _width - width of data table pointed by _inputByteData
//	• BYTE* _outputByteData - byte pointer to output data
void instantiateThreads(size_t, BITMAP_CHANGE_FN_TYPE&, BYTE*, DWORD, DWORD, BYTE*);

// Function measuring time of passed function wrapper
// Input parameters:
//	• std::function<void()> _wrappedFunction - wrapped function that execution time should be measured
// Output parameter:
//	• long long - time elapsed in nanoseconds
long long measureTime(const std::function<void()>&);