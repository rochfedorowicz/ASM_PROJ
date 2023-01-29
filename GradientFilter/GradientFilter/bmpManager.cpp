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
