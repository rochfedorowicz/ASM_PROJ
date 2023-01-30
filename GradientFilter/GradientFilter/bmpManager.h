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
	// Input parameters:
	//	• System::String^ _pathToImage - path specifing image location
	void loadBitmap(System::String^);

	// Function exporting BMP file
	// Input parameters:
	//	• System::String^ _pathToImage - path specifing image location
	//	• BYTE* _bytePtr - new output bytes that should be exported
	void exportBitmap(System::String^, BYTE*);

	// Function getter for stored BMP file
	// Output parameter:
	//	• BMP - BMP file stored by manager
	BMP getBitmap();
};