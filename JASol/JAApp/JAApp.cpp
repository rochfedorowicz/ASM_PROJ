#include <stdio.h> 
#include <functional>
#include <chrono>

#include "bmp.h"
#include "dllHandling.h"

typedef void(__cdecl* BITMAP_CHANGE_FN_TYPE)(BYTE*, DWORD, DWORD, BYTE*);
typedef int(__cdecl* TEST_FN_TYPE)(void);

int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    BITMAP_CHANGE_FN_TYPE procAddC = NULL, procAddASM = NULL;
    //TEST_FN_TYPE procAddASM;

    loadDLLFunction(hinstLibASM, L"JADll.dll", procAddASM, "calculatePixels");
    loadDLLFunction(hinstLibC, L"CDll.dll", procAddC, "calculatePixels");

    char name[] = "image4.bmp";
    char outputName[] = "imageOutput.bmp";
    BMP newBMPFile;

    LoadBitmapFile(name, newBMPFile);
    NEWLINE();

    BYTE* outputBytes = (BYTE*)malloc(newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    procAddASM(newBMPFile.copyOfBytes, newBMPFile.bmpInfo.heightBytes, newBMPFile.bmpInfo.sizeBytesOfRawData / newBMPFile.bmpInfo.heightBytes , outputBytes);
    newBMPFile.copyOfBytes = outputBytes;

    ExportBitmapWithAppliedChanges(newBMPFile, outputName);
    NEWLINE();
    //procAddASM();
    //procAddASM(newBMPFile.copyOfBytes, 1, newBMPFile.bmpInfo.sizeBytesOfRawData);
    //printf("==================AfterASMProcedure==================\n");
    //printBMP(newBMPFile, true);
    //NEWLINE();

    freeDLL(hinstLibASM);
    freeDLL(hinstLibC);
    return 0;
}