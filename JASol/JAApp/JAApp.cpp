#include <stdio.h> 
#include <functional>
#include <chrono>

#include "bmp.h"
#include "dllHandling.h"

typedef void(__cdecl* BITMAP_CHANGE_FN_TYPE)(BYTE*, DWORD, DWORD);
typedef void(__cdecl* DO_NOTHING_FN_TYPE)(BYTE*, DWORD, DWORD);

int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    BITMAP_CHANGE_FN_TYPE procAddC = NULL, procAddASM = NULL;
    DO_NOTHING_FN_TYPE procAdd2C = NULL, procAdd2ASM = NULL;

    loadDLLFunction(hinstLibASM, L"JADll.dll", procAddASM, "calculatePixels");
    loadDLLFunction(hinstLibC, L"CDll.dll", procAddC, "calculatePixels");

    char name[] = "image2.bmp";
    BMP newBMPFile;

    LoadBitmapFile(name, newBMPFile);
    NEWLINE();
    printf("==================BitmapData==================\n");
    printBMP(newBMPFile, true);
    NEWLINE();

    procAddC(newBMPFile.copyOfBytes, 1, newBMPFile.bmpInfo.sizeBytesOfRawData);
    printf("==================AfterCFunction==================\n");
    printBMP(newBMPFile, true);
    NEWLINE();

    UpdateBitmapFile(newBMPFile);
    NEWLINE();

    procAddASM(newBMPFile.copyOfBytes, 1, newBMPFile.bmpInfo.sizeBytesOfRawData);
    printf("==================AfterASMProcedure==================\n");
    printBMP(newBMPFile, true);
    NEWLINE();

    printf("==================ThreadsTesting - Calling C==================\n");
    NEWLINE();
    instantiateThreads(size_t{ 4 }, procAddC, newBMPFile.copyOfBytes, DWORD{ 1 }, newBMPFile.bmpInfo.sizeBytesOfRawData);
    NEWLINE();

    freeDLL(hinstLibASM);
    freeDLL(hinstLibC);
    NEWLINE();

    loadDLLFunction(hinstLibASM, L"JADll.dll", procAdd2ASM, "doNothing");
    loadDLLFunction(hinstLibC, L"CDll.dll", procAdd2C, "doNothing");
    NEWLINE();

    printf("==================ThreadsTesting2 - Calling C doNothing==================\n");
    NEWLINE();
    auto t_start = std::chrono::high_resolution_clock::now();
    instantiateThreads(size_t{ 4 }, procAdd2C, newBMPFile.copyOfBytes, DWORD{ 1 }, newBMPFile.bmpInfo.sizeBytesOfRawData);
    auto t_end = std::chrono::high_resolution_clock::now();
    NEWLINE();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    LOGINFO("Time elapsed since threads started is %f ms", elapsed_time_ms);
    NEWLINE();

    printf("==================ThreadsTesting3 - Calling ASM doNothing==================\n");
    NEWLINE();
    t_start = std::chrono::high_resolution_clock::now();
    instantiateThreads(size_t{ 4 }, procAdd2ASM, newBMPFile.copyOfBytes, DWORD{ 1 }, newBMPFile.bmpInfo.sizeBytesOfRawData);
    t_end = std::chrono::high_resolution_clock::now();
    NEWLINE();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    LOGINFO("Time elapsed since threads started is %f ms", elapsed_time_ms);
    NEWLINE();

    freeDLL(hinstLibASM);
    freeDLL(hinstLibC);
    return 0;
}