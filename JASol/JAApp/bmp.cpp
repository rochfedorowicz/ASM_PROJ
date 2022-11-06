#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>

#include "bmp.h"
#include "macros.h"

bool LoadBitmapFile(char* const& _filename, BMP& _bmpVar)
{
    FILE* filePtr = fopen(_filename, "rb");
    if (filePtr == NULL) {
        LOGINFO("Unable to open a file named %s!!!", _filename);
        return false;
    }

    BYTE BMBytes[2];
    fread(&BMBytes, 1, 2, filePtr);

    if (!(BMBytes[0] == 'B' && BMBytes[1] == 'M')) {
        fclose(filePtr);
        LOGINFO("Open file is not a BMP file!!!")
        return false;
    }

    fread(&_bmpVar.size, 4, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.dataOffset, 4, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.width, 4, 1, filePtr);
    fread(&_bmpVar.height, 4, 1, filePtr);
    fseek(filePtr, 2, SEEK_CUR);
    fread(&_bmpVar.bitsPerPixel, 2, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.sizeOfData, 4, 1, filePtr);
    fseek(filePtr, _bmpVar.dataOffset, SEEK_SET);

    _bmpVar.bitmapImageData = (BYTE*)malloc(_bmpVar.sizeOfData);
    if (_bmpVar.bitmapImageData != NULL) {
        fread(_bmpVar.bitmapImageData, sizeof(BYTE), _bmpVar.sizeOfData, filePtr);
    }
    else {
        fclose(filePtr);
        LOGINFO("Could not allocate memory!!!")
        return false;
    }

    if (!_bmpVar.bitmapImageData)
    {
        free(_bmpVar.bitmapImageData);
        fclose(filePtr);
        LOGINFO("Memory read failed!!!");
        return false;
    }

    fclose(filePtr);
    LOGINFO("Loaded bitmap successfully!!!");
    return true;
}

void printBMP(const BMP& _bmpVar, bool _extended) {
    printf("Size: %dB\n", _bmpVar.size);
    printf("Data offset: %dB\n", _bmpVar.dataOffset);
    printf("Width: %dp\n", _bmpVar.width);
    printf("Height: %dp\n", _bmpVar.height);
    printf("Bits per pixel: %db\n", _bmpVar.bitsPerPixel);
    printf("Size of data: %dB\n", _bmpVar.sizeOfData);

    if (_extended) {
        printf("Data:\n");
        DWORD bytesPerRow = ceil(double(_bmpVar.bitsPerPixel) * _bmpVar.width / 32.) * 4;
        for (int i = 0; i < _bmpVar.height; ++i) {
            printf("\t");
            for (int j = 0; j < bytesPerRow; ++j) {
                printf("%3d   ", _bmpVar.bitmapImageData[i * bytesPerRow + j]);
            }
            printf("\n");
        }
    }
}

RGBMAP getRGBMap(const BMP& _bmpVar) {
    RGBMAP newRgbMap;

    DWORD bytesPerRow = ceil(double(_bmpVar.bitsPerPixel) * _bmpVar.width / 32.) * 4;
    DWORD bytesReallyNeadedPerRow = _bmpVar.bitsPerPixel * _bmpVar.width / 8;
    DWORD realLengthInBytes = bytesReallyNeadedPerRow * _bmpVar.height;

    newRgbMap.combinedMap.byteArray = (BYTE*)malloc(realLengthInBytes * sizeof(BYTE));
    newRgbMap.redMap.byteArray = (BYTE*)malloc(realLengthInBytes * sizeof(BYTE) / 3);
    newRgbMap.greenMap.byteArray = (BYTE*)malloc(realLengthInBytes * sizeof(BYTE) / 3);
    newRgbMap.blueMap.byteArray = (BYTE*)malloc(realLengthInBytes * sizeof(BYTE) / 3);

    newRgbMap.combinedMap.height = newRgbMap.redMap.height = 
        newRgbMap.greenMap.height = newRgbMap.blueMap.height = _bmpVar.height;

    newRgbMap.combinedMap.width = bytesReallyNeadedPerRow;
    newRgbMap.redMap.width = newRgbMap.greenMap.width =
        newRgbMap.blueMap.width = bytesReallyNeadedPerRow / 3;

    for (int i = 0, z = 0; i < _bmpVar.height; ++i) {
        for (int j = 0; j < bytesReallyNeadedPerRow; ++j, ++z) {
            newRgbMap.combinedMap.byteArray[z] = _bmpVar.bitmapImageData[i * bytesPerRow + j];
            if (j % 3 == 0) {
                newRgbMap.redMap.byteArray[z / 3] = _bmpVar.bitmapImageData[i * bytesPerRow + j];
            }
            if (j % 3 == 1) {
                newRgbMap.greenMap.byteArray[z / 3] = _bmpVar.bitmapImageData[i * bytesPerRow + j];
            }
            if (j % 3 == 2) {
                newRgbMap.blueMap.byteArray[z / 3] = _bmpVar.bitmapImageData[i * bytesPerRow + j];
            }
        }
    }

    return newRgbMap;
}

void printRGBMAP(const RGBMAP& _rgbMap, bool _extended) {
    printf("Combined map:\n");
    printf("\tHeight: %dB\n", _rgbMap.combinedMap.height);
    printf("\tWidth: %dB\n", _rgbMap.combinedMap.width);
    printf("\tData:\n");
    for (int i = 0; i < _rgbMap.combinedMap.height; ++i) {
        printf("\t\t");
        for (int j = 0; j < _rgbMap.combinedMap.width; ++j) {
            printf("%3d   ", _rgbMap.combinedMap.byteArray[i * _rgbMap.combinedMap.width + j]);
        }
        printf("\n");
    }

    if (_extended) {
        printf("Red map:\n");
        printf("\tHeight: %dB\n", _rgbMap.redMap.height);
        printf("\tWidth: %dB\n", _rgbMap.redMap.width);
        printf("\tData:\n");
        for (int i = 0; i < _rgbMap.redMap.height; ++i) {
            printf("\t\t");
            for (int j = 0; j < _rgbMap.redMap.width; ++j) {
                printf("%3d   ", _rgbMap.redMap.byteArray[i * _rgbMap.redMap.width + j]);
            }
            printf("\n");
        }
        printf("Green map:\n");
        printf("\tHeight: %dB\n", _rgbMap.greenMap.height);
        printf("\tWidth: %dB\n", _rgbMap.greenMap.width);
        printf("\tData:\n");
        for (int i = 0; i < _rgbMap.greenMap.height; ++i) {
            printf("\t\t");
            for (int j = 0; j < _rgbMap.greenMap.width; ++j) {
                printf("%3d   ", _rgbMap.greenMap.byteArray[i * _rgbMap.greenMap.width + j]);
            }
            printf("\n");
        }
        printf("Blue map:\n");
        printf("\tHeight: %dB\n", _rgbMap.blueMap.height);
        printf("\tWidth: %dB\n", _rgbMap.blueMap.width);
        printf("\tData:\n");
        for (int i = 0; i < _rgbMap.blueMap.height; ++i) {
            printf("\t\t");
            for (int j = 0; j < _rgbMap.blueMap.width; ++j) {
                printf("%3d   ", _rgbMap.blueMap.byteArray[i * _rgbMap.blueMap.width + j]);
            }
            printf("\n");
        }
    }
}