#pragma once

#define EXPORT extern "C" __declspec(dllexport)

EXPORT void calculatePixels(BYTE*, DWORD, DWORD);