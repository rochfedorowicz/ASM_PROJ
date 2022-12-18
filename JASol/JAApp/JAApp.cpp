#include <stdio.h> 
#include <functional>

#include "bmp.h"
#include "dllHandling.h"
#include "functionTypes.h"
#pragma warning(disable : 4996)
int main() {
    HINSTANCE hinstLibC, hinstLibASM;
    BITMAP_CHANGE_FN_TYPE procAddC = NULL, procAddASM = NULL, procAddASMWithVI = NULL;
    loadDLL(hinstLibC, L"CDll.dll");
    loadDLL(hinstLibASM, L"JADll.dll");
    loadDLLFunction(hinstLibC, procAddC, "calculatePixels");
    loadDLLFunction(hinstLibASM, procAddASM, "calculatePixels");
    loadDLLFunction(hinstLibASM, procAddASMWithVI, "calculatePixelsWithVI");

    const char* files[] = { "image.bmp", "image2.bmp", "image3.bmp", "image6.bmp", "image7.bmp"};

    FILE* fptr;
    fptr = fopen("timeMeasurement.csv", "w");
    fprintf(fptr, "DATA_SIZE;THREAD_NR;C_TIME;ASM_TIME;BASM_TIME\n");
    fclose(fptr);

    for (auto file : files) {

        char outputName[] = "imageOutput.bmp";
        BMP newBMPFile;

        LoadBitmapFile((char* const)file, newBMPFile);
        //NEWLINE();
        //printBMP(newBMPFile, false);

        BYTE* outputBytes = (BYTE*)malloc(newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
        if (outputBytes != 0)
            memcpy(outputBytes, newBMPFile.copyOfBytes, newBMPFile.bmpInfo.sizeBytesOfRawData * sizeof(BYTE));
        auto inputBytes = newBMPFile.copyOfBytes;
        auto height = newBMPFile.bmpInfo.heightBytes;
        auto width = newBMPFile.bmpInfo.sizeBytesOfRawData / newBMPFile.bmpInfo.heightBytes;

        int threadNumbers[] = {1, 2, 4, 8, 16, 32, 64, 128};

        for (int threadNumber : threadNumbers) {

            auto foo1 = std::bind(instantiateThreads, threadNumber, procAddC, inputBytes, height, width, outputBytes);
            auto foo2 = std::bind(instantiateThreads, threadNumber, procAddASM, inputBytes, height, width, outputBytes);
            auto foo3 = std::bind(instantiateThreads, threadNumber, procAddASMWithVI, inputBytes, height, width, outputBytes);

            long long avg1 = 0, avg2 = 0, avg3 = 0;

            //NEWLINE();
            //printf("Ellapsed:\n\t %d nanoseconds,\n\t %d microseconds,\n\t %d miliseconds",
            //    (int)nanoseconds, (int)nanoseconds / 1000, (int)nanoseconds / 1000000);
            //NEWLINE();

            //newBMPFile.copyOfBytes = outputBytes;
            //ExportBitmapWithAppliedChanges(newBMPFile, outputName);
            //printBMP(newBMPFile, false);

            for (size_t i = 0; i < 10; ++i) {
                auto nanoseconds1 = measureTime(foo1);
                avg1 += measureTime(foo1);
                //NEWLINE();
                //printf("Ellapsed:\n\t %d nanoseconds,\n\t %d microseconds,\n\t %d miliseconds",
                //    (int)nanoseconds, (int)nanoseconds / 1000, (int)nanoseconds / 1000000);
                //NEWLINE();

                auto nanoseconds2 = measureTime(foo2);
                avg2 += measureTime(foo2);
                //NEWLINE();
                //printf("Ellapsed:\n\t %d nanoseconds,\n\t %d microseconds,\n\t %d miliseconds",
                //    (int)nanoseconds, (int)nanoseconds / 1000, (int)nanoseconds / 1000000);
                //NEWLINE();

                auto nanoseconds3 = measureTime(foo3);
                avg3 += measureTime(foo3);
            }
            avg1 /= 10;
            avg2 /= 10;
            avg3 /= 10;
            //NEWLINE();
            //printf("Ellapsed:\n\t %d nanoseconds,\n\t %d microseconds,\n\t %d miliseconds",
            //    (int)nanoseconds, (int)nanoseconds / 1000, (int)nanoseconds / 1000000);
            //NEWLINE();

            FILE* fptr;
            fptr = fopen("timeMeasurement.csv", "a");
            fprintf(fptr, "%d;%d;%d;%d;%d\n", newBMPFile.bmpInfo.sizeBytesOfRawData,
                                            threadNumber,
                                            (int)avg1 / 1000000,
                                            (int)avg2 / 1000000,
                                            (int)avg3 / 1000000);
            fclose(fptr);
        }
    }

    freeDLL(hinstLibC);
    freeDLL(hinstLibASM);

    return 0;
}