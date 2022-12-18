#pragma once
#include <limits.h>

#include "macros.h"


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

struct BMP {
    const char* fileName;
    BMPINFO bmpInfo;
    BYTE* copyOfBytes;
};

bool LoadBitmapFile(char* const, BMP&);

void ExportBitmapWithAppliedChanges(BMP&, char* const&);

void printBMP(const BMP&, bool = false);