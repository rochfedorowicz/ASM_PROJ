#include <stdio.h> 

#include "bmp.h"
#include "dllHandling.h"

int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    MY_FUN_PTR procAddC = NULL, procAddASM = NULL;

    loadDLLFunction(hinstLibASM, L"JADll.dll", procAddASM, "calculatePixels");
    loadDLLFunction(hinstLibC, L"CDll.dll", procAddC, "calculatePixels");

    char name[] = "image2.bmp";
    BMP newBMPFile;

    LoadBitmapFile(name, newBMPFile);
    NEWLINE();
    printf("==================BitmapData==================\n");
    printBMP(newBMPFile);
    NEWLINE();

    RGBMAP newRGBMap = getRGBMap(newBMPFile);
    NEWLINE();
    printf("==================Normal-RGBData==================\n");
    printRGBMAP(newRGBMap);
    NEWLINE();

    procAddC(newRGBMap.combinedMap.byteArray, newRGBMap.combinedMap.height, newRGBMap.combinedMap.width);
    NEWLINE();
    printf("==================CFunctionUsed-RGBData==================\n");
    printRGBMAP(newRGBMap);
    NEWLINE();

    procAddASM(newRGBMap.combinedMap.byteArray, newRGBMap.combinedMap.height, newRGBMap.combinedMap.width);
    NEWLINE();
    printf("==================ASMProcedureUsed-RGBData==================\n");
    printRGBMAP(newRGBMap);
    NEWLINE();

    freeDLL(hinstLibASM);
    freeDLL(hinstLibC);
    return 0;
}