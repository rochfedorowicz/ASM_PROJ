//////////////////////////////////////////////////////////////////////////////
//																			//
//	Project topic: Gradient filtering (north direction)						//
// 																			//
//	Short description of algorithm: 										//
//	Filtering with mask 3x3 by iterating over bytes and its neighbourhood.	//
//	Multiplied bytes are summed and then divided to calculate new value		//
//	achiving brighter colours for horizontal edges and detecting them.		//
//																			//
//	Date: 28.01.2023														//
//																			//
//	Semester: 5																//
//																			//
//	Academic year: 22/23													//
//																			//
//	Author: Roch Fedorowicz													//
//																			//
//	Version: 1.0															//
//																			//
//////////////////////////////////////////////////////////////////////////////

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