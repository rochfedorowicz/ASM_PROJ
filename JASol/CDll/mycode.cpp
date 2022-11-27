#include "pch.h" 
#include "mycode.h"

void calculatePixels(BYTE* _inputByteData, DWORD _height, DWORD _width, BYTE* _outputByteData) {

	for (size_t i = 1; i < _height - 1; ++i) {
		for (size_t j = 1; j < (_width - 1)/3 - 1; ++j) {
			for (size_t channel = 0; channel < 3; ++channel) {
				LONG sum = 0;
				sum += _inputByteData[(i - 1) * _width + (j - 1) * 3 + channel];
				sum += _inputByteData[(i - 1) * _width + j * 3 + channel];
				sum += _inputByteData[(i - 1) * _width + (j + 1) * 3 + channel];
				sum += _inputByteData[i * _width + (j - 1) * 3 + channel];
				sum += -2 * _inputByteData[i * _width + j * 3 + channel] ;
				sum += _inputByteData[i * _width + (j + 1) * 3 + channel];
				sum += -1 * _inputByteData[(i + 1) * _width + (j - 1) * 3 + channel];
				sum += -1 * _inputByteData[(i + 1) * _width + j * 3 + channel];
				sum += -1 * _inputByteData[(i + 1) * _width + (j + 1) * 3 + channel];
			_outputByteData[i * _width + j * 3 + channel] = sum / 9 < 0 ? 0 : sum / 9;
			}
		}
	}
}

void doNothing(BYTE* _byteData, DWORD _height, DWORD _width) {}