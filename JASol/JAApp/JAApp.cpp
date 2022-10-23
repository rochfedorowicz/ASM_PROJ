#pragma warning(disable : 4996)
#include <windows.h> 
#include <stdio.h> 
#include <limits.h>

#include <thread>
#include <vector>

#define LOGINFO(...) printf("[INFO]: "); printf(__VA_ARGS__);  printf("\n");
#define NEWLINE() printf("\n\n");
typedef int(__cdecl* MY_FUN_PTR)(DWORD, DWORD);

#pragma pack(2)

struct BMP {
    DWORD size;
    DWORD dataOffset;
    DWORD width;
    DWORD height;
    WORD bitsPerPixel;
    DWORD sizeOfData;
    BYTE* bitmapImageData;
};

bool LoadBitmapFile(char* const & filename, BMP& _bmpVar)
{
    FILE* filePtr = filePtr = fopen(filename, "rb");
    if (filePtr == NULL) return false;

    BYTE BMBytes[2];
    fread(&BMBytes, 1, 2, filePtr);

    if (!(BMBytes[0] == 'B' && BMBytes[1] == 'M')) {
        fclose(filePtr);
        return false;
    }

    fread(&_bmpVar.size, 4, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.dataOffset, 4, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.width, 4, 1, filePtr);
    fread(&_bmpVar.height, 4, 1, filePtr);
    fseek(filePtr, 2, SEEK_CUR);
    fread(&_bmpVar.bitsPerPixel, 2, 1, filePtr);
    fseek(filePtr, 4, SEEK_CUR);
    fread(&_bmpVar.sizeOfData, 4, 1, filePtr);
    fseek(filePtr, _bmpVar.dataOffset, SEEK_SET);

    _bmpVar.bitmapImageData = (BYTE*)malloc(_bmpVar.sizeOfData);
    if (_bmpVar.bitmapImageData != NULL) {
        fread(_bmpVar.bitmapImageData, sizeof(BYTE), _bmpVar.sizeOfData, filePtr);
    }
    else {
        fclose(filePtr);
        return false;
    }

    if (!_bmpVar.bitmapImageData)
    {
        free(_bmpVar.bitmapImageData);
        fclose(filePtr);
        return NULL;
    }

    fclose(filePtr);
    return true;
}

void printBMP(const BMP &_bmpVar) {
    printf("Size: %d\n", _bmpVar.size);
    printf("Data offset: %d\n", _bmpVar.dataOffset);
    printf("Width: %d\n", _bmpVar.width);
    printf("Height: %d\n", _bmpVar.height);
    printf("Bits per pixel: %d\n", _bmpVar.bitsPerPixel);
    printf("Size of data: %d\n", _bmpVar.sizeOfData);
    printf("Data:\n");
    for (size_t i = 0; i < _bmpVar.sizeOfData; ++i) {
        printf("%d ", _bmpVar.bitmapImageData[i]);
    }
}

void instantiateThreads(const size_t &_numberOfThreads, MY_FUN_PTR functionToBeCalled) {
    std::vector<std::thread> threads;
    for (int i = 0; i < _numberOfThreads; i++) {
        threads.push_back(std::thread([&functionToBeCalled]() {
            printf("\nThread finished! Output is %d\n", functionToBeCalled(3, 5));
         }));
    }
    for (auto& t : threads) t.join();
}

int main()
{
    HINSTANCE hinstLib;
    MY_FUN_PTR procAddC = NULL, procAddASM = NULL;
    BOOL fFreeResult;

    hinstLib = LoadLibrary(TEXT("CDll.dll"));
    if (hinstLib != NULL) {
        LOGINFO("DLL written in C loaded successfuly!");
        procAddC = (MY_FUN_PTR)GetProcAddress(hinstLib, "adding");
        if (NULL != procAddC) {
            LOGINFO("Function from C-DLL found!");
            LOGINFO("Result of C function: %d", procAddC(4, 2));
        } else {
            LOGINFO("Function from C-DLL not found!");
        }
        //fFreeResult = FreeLibrary(hinstLib);
    } else {
        LOGINFO("DLL written in C failed to load!");
    }

    NEWLINE();

    hinstLib = LoadLibrary(TEXT("JADll.dll"));
    if (hinstLib != NULL) {
        LOGINFO("DLL written in ASM loaded successfuly!");
        procAddASM = (MY_FUN_PTR)GetProcAddress(hinstLib, "adding");
        if (NULL != procAddASM) {
            LOGINFO("Function from ASM-DLL found!");
            LOGINFO("Result of ASM function: %d", procAddASM(4, 2));
        } else {
            LOGINFO("Function from ASM-DLL not found!");
        }
        //fFreeResult = FreeLibrary(hinstLib);
    } else {
        LOGINFO("DLL written in ASM failed to load!");
    }

    NEWLINE();

    char name[] = "image2.bmp";
    BMP newBMPFile;
    if (LoadBitmapFile(name, newBMPFile)) {
        LOGINFO("Bitmap loaded successfuly!");
    }
    else {
        LOGINFO("Bitmap loading failed!");
    }

    NEWLINE();

    printBMP(newBMPFile);

    instantiateThreads(3, procAddASM);

    return 0;
}