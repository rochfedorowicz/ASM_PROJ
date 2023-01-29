#pragma once

#include <string>
#include <map>

#include "bmp.h"

// Class responsible for BMP file handling
ref class BMPManager {

	// Stored BMP file
	BMP* bmpFile;

public:

	// Default constructor
	BMPManager();

	// Default destructor
	~BMPManager();

	// Function loading BMP file
	void loadBitmap(System::String^);

	// Function exporting BMP file
	void exportBitmap(System::String^, BYTE*);

	// Function getter for stored BMP file
	BMP getBitmap();
};