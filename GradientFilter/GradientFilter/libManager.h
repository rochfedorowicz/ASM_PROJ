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
	bool loadLibrary(std::string);

	// Function loading function from library by the name
	bool loadFunction(std::string, std::string);

	// Function getter for loaded function distinguishable by the name
	BITMAP_CHANGE_FN_TYPE getFunction(std::string);
};