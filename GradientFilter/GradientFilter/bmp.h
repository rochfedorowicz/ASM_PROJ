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
bool loadBitmapFile(char* const, BMP&);

// Function exportig BMP file after it was changed
void exportBitmapWithAppliedChanges(BMP&, char* const&);