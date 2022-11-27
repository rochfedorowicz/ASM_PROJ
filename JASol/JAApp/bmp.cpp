#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>

#include "bmp.h"
#include "macros.h"

bool LoadBitmapFile(char* const& _filename, BMP& _bmpVar) {
    _bmpVar.fileName = _filename;

    FILE* filePtr = fopen(_filename, "rb");
    if (filePtr == NULL) {
        LOGINFO("Unable to open a file named %s!!!", _filename);
        return false;
    }

    fread(&_bmpVar.bmpInfo, sizeof(BMPINFO), 1, filePtr);

    if (_bmpVar.bmpInfo.BMbytes != 0x4D42) {
        fclose(filePtr);
        LOGINFO("Open file is not a BMP file!!!")
        return false;
    }

    fseek(filePtr, _bmpVar.bmpInfo.dataOffsetInBytes, SEEK_SET);
    _bmpVar.copyOfBytes = (BYTE*)malloc(_bmpVar.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    if (_bmpVar.copyOfBytes != nullptr)
        fread(_bmpVar.copyOfBytes, sizeof(BYTE), _bmpVar.bmpInfo.sizeBytesOfRawData, filePtr);
    else {
        fclose(filePtr);
        LOGINFO("Could not allocate memory!!!")
        return false;
    }

    fclose(filePtr);
    LOGINFO("Loaded bitmap info successfully!!!");
    return true;
}

void ExportBitmapWithAppliedChanges(BMP& _bmpVar, char* const& _newFilename) {
    FILE* filePtr = fopen(_newFilename, "wb");

    fwrite(&_bmpVar.bmpInfo, sizeof(BMPINFO), 1, filePtr);
    fseek(filePtr, _bmpVar.bmpInfo.dataOffsetInBytes, SEEK_SET);
    fwrite(_bmpVar.copyOfBytes, sizeof(BYTE), _bmpVar.bmpInfo.sizeBytesOfRawData, filePtr);

    LOGINFO("Bitmap exported successfully!!!");
    fclose(filePtr);
}

void printBMP(const BMP& _bmpVar, bool _extended) {
    printf("File name: %s\n", _bmpVar.fileName);
    printf("Size: %dB\n", _bmpVar.bmpInfo.sizeBytesOfFile);
    printf("Data offset: %dB\n", _bmpVar.bmpInfo.dataOffsetInBytes);
    printf("Width: %dp\n", _bmpVar.bmpInfo.widthBytes);
    printf("Height: %dp\n", _bmpVar.bmpInfo.heightBytes);
    printf("Bits per pixel: %db\n", _bmpVar.bmpInfo.bitsPerPixel);
    printf("Size of data: %dB\n", _bmpVar.bmpInfo.sizeBytesOfRawData);

    if (_extended) {
        printf("Data:\n");
        DWORD bytesPerRow = ceil(double(_bmpVar.bmpInfo.bitsPerPixel) * _bmpVar.bmpInfo.widthBytes / 32.) * 4;
        for (int i = 0; i < _bmpVar.bmpInfo.heightBytes; ++i) {
            printf("\t");
            for (int j = 0; j < bytesPerRow; ++j) {
                printf("%3d   ", _bmpVar.copyOfBytes[i * bytesPerRow + j]);
            }
            printf("\n");
        }
    }
}