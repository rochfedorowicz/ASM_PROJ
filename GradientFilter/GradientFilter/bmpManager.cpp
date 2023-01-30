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

#include "pch.h"

#include "bmpManager.h"

BMPManager::BMPManager() {
	bmpFile = new BMP();
}

BMPManager::~BMPManager() {
	delete bmpFile;
}

void BMPManager::loadBitmap(System::String^ _pathToImage) {
	char* _convertedPathToImage = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_pathToImage)).ToPointer();
	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)_convertedPathToImage));
	loadBitmapFile(_convertedPathToImage, *bmpFile);
}

void BMPManager::exportBitmap(System::String^ _pathToImage, BYTE* _bytePtr) {
	BYTE* bytes = bmpFile->copyOfBytes;
	bmpFile->copyOfBytes = _bytePtr;
	char* _convertedPathToImage = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(_pathToImage)).ToPointer();
	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)_convertedPathToImage));
	exportBitmapWithAppliedChanges(*bmpFile, _convertedPathToImage);
	bmpFile->copyOfBytes = bytes;
}

BMP BMPManager::getBitmap() {
	return *bmpFile;
}
