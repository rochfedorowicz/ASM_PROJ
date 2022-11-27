#include <stdio.h> 
#include <functional>

#include "bmp.h"
#include "dllHandling.h"

typedef void(__cdecl* BITMAP_CHANGE_FN_TYPE)(BYTE*, DWORD, DWORD, BYTE*);

int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    BITMAP_CHANGE_FN_TYPE procAddC = NULL, procAddASM = NULL;
    loadDLLFunction(hinstLibC, L"CDll.dll", procAddC, "calculatePixels");
    loadDLLFunction(hinstLibASM, L"JADll.dll", procAddASM, "calculatePixels");

    char name[] = "image2.bmp";
    char outputName[] = "imageOutput.bmp";
    BMP newBMPFile;

    LoadBitmapFile(name, newBMPFile);
    NEWLINE();
    printBMP(newBMPFile, false);

    BYTE* outputBytes = (BYTE*)malloc(newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    if (outputBytes != 0)
        memcpy(outputBytes, newBMPFile.copyOfBytes, newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    procAddASM(newBMPFile.copyOfBytes, newBMPFile.bmpInfo.heightBytes, newBMPFile.bmpInfo.sizeBytesOfRawData / newBMPFile.bmpInfo.heightBytes, outputBytes);
    newBMPFile.copyOfBytes = outputBytes;

    ExportBitmapWithAppliedChanges(newBMPFile, outputName);
    NEWLINE();
    printBMP(newBMPFile, false);

    freeDLL(hinstLibC);
    freeDLL(hinstLibASM);

    return 0;
}