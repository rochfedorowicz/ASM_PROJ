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

#include <string>
#include <map>

#include "bmp.h"
#include "functionTypes.h"
#include "dllHandling.h"

// Class responsible for DLL library and function handling
ref class LibManager {

	// Maps of DLL and loaded functions
	std::map<std::string, HINSTANCE>* hinstLibs;
	std::map<std::string, BITMAP_CHANGE_FN_TYPE>* loadedFunction;

	// Inner function translating string to wstring
	LPCWSTR strToWStr(std::string);

public:

	// Default constructor
	LibManager();

	// Default destructor
	~LibManager();

	// Function loading library by the name
	// Input parameters:
	//	• std::string _string - name of library to load
	// Output parameter:
	//	• bool - value indicating if function succeeded
	bool loadLibrary(std::string);

	// Function loading function from library by the name
	// Input parameters:
	//	• std::string _nameOfLibrary - name of library to load function from
	//	• std::string _nameOfFucntion - name of function to load
	// Output parameter:
	//	• bool - value indicating if function succeeded
	bool loadFunction(std::string, std::string);

	// Function getter for loaded function distinguishable by the name
	// Input parameters:
	//	• std::string _nameOfFucntion - name of function to get
	// Output parameter:
	//	• BITMAP_CHANGE_FN_TYPE - function pointer
	BITMAP_CHANGE_FN_TYPE getFunction(std::string);
};