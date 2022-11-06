#pragma once
#include <limits.h>

#include "macros.h"


struct BMP {
    DWORD size;
    DWORD dataOffset;
    DWORD width;
    DWORD height;
    WORD bitsPerPixel;
    DWORD sizeOfData;
    BYTE* bitmapImageData;
};

struct COLORMAP {
    BYTE* byteArray;
    DWORD width;
    DWORD height;
};

struct RGBMAP {
    COLORMAP redMap;
    COLORMAP greenMap;
    COLORMAP blueMap;
    COLORMAP combinedMap;
};

bool LoadBitmapFile(char* const&, BMP&);

void printBMP(const BMP&, bool = false);

RGBMAP getRGBMap(const BMP&);

void printRGBMAP(const RGBMAP&, bool = false);