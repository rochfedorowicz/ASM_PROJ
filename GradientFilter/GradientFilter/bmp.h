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
#include <windows.h>

// Struct imitating structure of BMP info file
#pragma pack(2)
struct BMPINFO {
    // BMP HEADER
    WORD BMbytes;               // 2 bytes
    DWORD sizeBytesOfFile;      // 4 bytes
    DWORD unused;               // 2 * 2 bytes
    DWORD dataOffsetInBytes;    // 4 bytes
    // DIB HEADER
    DWORD sizeBytesOfDIBHeader; // 4 bytes
    DWORD widthBytes;           // 4 bytes
    DWORD heightBytes;          // 4 bytes
    WORD colorPlanesNumber;     // 2 bytes
    WORD bitsPerPixel;          // 2 bytes
    DWORD compressionMethod;    // 4 bytes
    DWORD sizeBytesOfRawData;   // 4 bytes
    // Irrelevant rest of BMP file atributes and raw data
};

// Struct putting togehter BMP info and pointer to raw data
struct BMP {
    BMPINFO bmpInfo;
    BYTE* copyOfBytes;
};

// Function loading BMP file
// Input parameters:
//	• char* _filename - name of file
// 	• BMP _bmpVar - BMP file to load data to
// Output parameter:
//	• bool - value indicating if function succeeded
bool loadBitmapFile(char* const, BMP&);

// Function exportig BMP file after it was changed
// Input parameters:
// 	• BMP _bmpVar - BMP file to export data from
//	• char* _newFilename - new name of file
void exportBitmapWithAppliedChanges(BMP&, char* const&);