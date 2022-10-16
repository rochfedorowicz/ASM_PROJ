#pragma once

#define EXPORT extern "C" __declspec(dllexport)

EXPORT int adding(const int, const int);