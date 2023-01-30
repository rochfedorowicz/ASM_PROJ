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

#pragma warning(disable : 4996)
#include "pch.h"

#include "bmp.h"

#include <stdio.h>
#include <math.h>

bool loadBitmapFile(char* const _filename, BMP& _bmpVar) {
    FILE* filePtr = fopen(_filename, "rb");
    if (filePtr == NULL) {
        return false;
    }

    fread(&_bmpVar.bmpInfo, sizeof(BMPINFO), 1, filePtr);

    if (_bmpVar.bmpInfo.BMbytes != 0x4D42) {
        fclose(filePtr);
        return false;
    }

    fseek(filePtr, _bmpVar.bmpInfo.dataOffsetInBytes, SEEK_SET);
    _bmpVar.copyOfBytes = (BYTE*)malloc(_bmpVar.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    if (_bmpVar.copyOfBytes != nullptr)
        fread(_bmpVar.copyOfBytes, sizeof(BYTE), _bmpVar.bmpInfo.sizeBytesOfRawData, filePtr);
    else {
        fclose(filePtr);
        return false;
    }

    fclose(filePtr);
    return true;
}

void exportBitmapWithAppliedChanges(BMP& _bmpVar, char* const& _newFilename) {
    FILE* filePtr = fopen(_newFilename, "wb");

    fwrite(&_bmpVar.bmpInfo, sizeof(BMPINFO), 1, filePtr);
    fseek(filePtr, _bmpVar.bmpInfo.dataOffsetInBytes, SEEK_SET);
    fwrite(_bmpVar.copyOfBytes, sizeof(BYTE), _bmpVar.bmpInfo.sizeBytesOfRawData, filePtr);

    fclose(filePtr);
}