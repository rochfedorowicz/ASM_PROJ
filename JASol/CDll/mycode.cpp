#include <stdio.h>
#include <stdlib.h>

#include "pch.h" 
#include "mycode.h"

void calculatePixels(BYTE* _byteData, DWORD _height, DWORD _width) {
	for (int i = 0; i < _height * _width; ++i) {
		if (_byteData[i] == 0) _byteData[i] = 255;
		else if (_byteData[i] == 255) _byteData[i] = 0;
	}
}

void doNothing(BYTE* _byteData, DWORD _height, DWORD _width) {}