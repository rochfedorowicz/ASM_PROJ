#include "pch.h" 
#include "mycode.h"

void calculatePixels(BYTE* _inputByteData, DWORD _height, DWORD _width, BYTE* _outputByteData) {

	for (size_t i = 1; i < _height - 1; ++i) {
		for (size_t j = 1; j < _width - 1; ++j) {
			LONG sum = 0;
			sum += _inputByteData[(i - 1) * _width + (j - 1)];
			sum += _inputByteData[(i - 1) * _width + j];
			sum += _inputByteData[(i - 1) * _width + (j + 1)];
			sum += _inputByteData[i * _width + (j - 1)];
			sum += -2 * _inputByteData[i * _width + j];
			sum += _inputByteData[i * _width + (j + 1)];
			sum += -1 * _inputByteData[(i + 1) * _width + (j - 1)];
			sum += -1 * _inputByteData[(i + 1) * _width + j];
			sum += -1 * _inputByteData[(i + 1) * _width + (j + 1)];
			_outputByteData[i * _width + j] = sum / 9 < 0 ? 0 : sum / 9;
		}
	}
}

void doNothing(BYTE* _byteData, DWORD _height, DWORD _width) {}