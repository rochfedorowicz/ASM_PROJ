#pragma warning(disable : 4996)
#include <windows.h> 
#include <stdio.h> 
#include <limits.h>

#define LOGINFO(...) printf("[INFO]: "); printf(__VA_ARGS__);  printf("\n");
#define NEWLINE() printf("\n\n");
typedef int(_stdcall * MY_ASM_PROC)(DWORD, DWORD);
typedef int(__cdecl * MY_C_FUN)(DWORD, DWORD);

struct BMP {
    UINT32 dataOffset, height, width;
    BYTE** pixels;
};

void loadBitmap(const char* _bitmapName) {

    FILE* file = fopen(_bitmapName, "rb");
    UINT32 dataOffset, height, width;
    BYTE** pixels;

    if (file == NULL) {
        LOGINFO("Failed to load image!");
        throw("Failed to load image!");
    }

    if (!(fgetc(file) == 'B' && fgetc(file) == 'M')) {
        LOGINFO("This is not a bitmap!");
        throw("This is not a bitmap!");
    }

    fseek(file, 8, SEEK_CUR);
    fread(&dataOffset, 4, 1, file);
    fseek(file, 4, SEEK_CUR);
    fread(&width, 4, 1, file);
    fread(&height, 4, 1, file);
    fseek(file, dataOffset, SEEK_SET);
    LOGINFO("%d", dataOffset);

    BYTE tempByte = NULL;
    for (int i = 0, bit = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (bit == CHAR_BIT) {
                bit = 0;
            }
            if (bit == 0) {
                fread(&tempByte, 1, 1, file);
            }
            printf("%d ", (tempByte >> bit) & 1);
            ++bit;
        }
        printf("\n");
    }
    
    NEWLINE();
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            fread(&tempByte, 1, 1, file);
            printf("%d ", tempByte);
        }
        printf("\n");
    }



}

int main()
{
    HINSTANCE hinstLib;
    MY_C_FUN procAddC = NULL;
    MY_ASM_PROC procAddASM = NULL;
    BOOL fFreeResult;

    hinstLib = LoadLibrary(TEXT("CDll.dll"));
    if (hinstLib != NULL) {
        LOGINFO("DLL written in C loaded successfuly!");
        procAddC = (MY_C_FUN)GetProcAddress(hinstLib, "adding");
        if (NULL != procAddC) {
            LOGINFO("Function from C-DLL found!");
            LOGINFO("Result of C function: %d", procAddC(4, 2));
        } else {
            LOGINFO("Function from C-DLL not found!");
        }
        fFreeResult = FreeLibrary(hinstLib);
    } else {
        LOGINFO("DLL written in C failed to load!");
    }

    NEWLINE();

    hinstLib = LoadLibrary(TEXT("JADll.dll"));
    if (hinstLib != NULL) {
        LOGINFO("DLL written in ASM loaded successfuly!");
        procAddASM = (MY_ASM_PROC)GetProcAddress(hinstLib, "adding");
        if (NULL != procAddASM) {
            LOGINFO("Function from ASM-DLL found!");
            LOGINFO("Result of ASM function: %d", procAddASM(4, 2));
        } else {
            LOGINFO("Function from ASM-DLL not found!");
        }
        fFreeResult = FreeLibrary(hinstLib);
    } else {
        LOGINFO("DLL written in ASM failed to load!");
    }

    NEWLINE();

    loadBitmap("image.bmp");


    return 0;
}