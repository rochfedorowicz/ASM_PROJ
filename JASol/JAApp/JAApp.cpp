#include <stdio.h> 
#include <functional>

#include "bmp.h"
#include "dllHandling.h"
#include "functionTypes.h"

int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    BITMAP_CHANGE_FN_TYPE procAddC = NULL, procAddASM = NULL;
    loadDLLFunction(hinstLibC, L"CDll.dll", procAddC, "calculatePixels");
    loadDLLFunction(hinstLibASM, L"JADll.dll", procAddASM, "calculatePixels");

    char name[] = "image7.bmp";
    char outputName[] = "imageOutput.bmp";
    BMP newBMPFile;

    LoadBitmapFile(name, newBMPFile);
    NEWLINE();
    printBMP(newBMPFile, false);

    BYTE* outputBytes = (BYTE*)malloc(newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    if (outputBytes != 0)
        memcpy(outputBytes, newBMPFile.copyOfBytes, newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
    auto inputBytes = newBMPFile.copyOfBytes;
    auto height = newBMPFile.bmpInfo.heightBytes;
    auto width = newBMPFile.bmpInfo.sizeBytesOfRawData / newBMPFile.bmpInfo.heightBytes;

    auto foo = std::bind(instantiateThreads, 4, procAddASM, inputBytes, height, width, outputBytes);
    auto nanoseconds = measureTime(foo);
    newBMPFile.copyOfBytes = outputBytes;

    ExportBitmapWithAppliedChanges(newBMPFile, outputName);
    NEWLINE();
    printf("Ellapsed:\n\t %d nanoseconds,\n\t %d microseconds,\n\t %d miliseconds",
        (int)nanoseconds, (int)nanoseconds / 1000, (int)nanoseconds / 1000000);
    NEWLINE();
    printBMP(newBMPFile, false);

    freeDLL(hinstLibC);
    freeDLL(hinstLibASM);

    return 0;
}