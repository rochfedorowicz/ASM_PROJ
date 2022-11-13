#pragma once
#include <windows.h>

#define LOGINFO(...) printf("[INFO]: "); printf(__VA_ARGS__);  printf("\n");
#define NEWLINE() printf("\n\n");