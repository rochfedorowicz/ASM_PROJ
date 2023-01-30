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

#include "dllHandling.h"

bool loadDLL(HINSTANCE& _hinstLib, const LPCWSTR& _libName) {
    _hinstLib = LoadLibrary(_libName);
    if (_hinstLib != NULL) {
        return true;
    }
    return false;
}

bool loadDLLFunction(HINSTANCE& _hinstLib, BITMAP_CHANGE_FN_TYPE& _procAddress, const LPCSTR& _funName) {
    if (_hinstLib != NULL) {
        _procAddress = (BITMAP_CHANGE_FN_TYPE)GetProcAddress(_hinstLib, _funName);
        if (NULL != _procAddress) {
            return true;
        }
    }
    return false;
}

bool freeDLL(HINSTANCE& _hinstLib) {
    if (FreeLibrary(_hinstLib)) {
        return true;
    }
    return false;
}

void instantiateThreads(size_t _numberOfThreads, BITMAP_CHANGE_FN_TYPE& _functionPointer, BYTE* _inputByteData,
    DWORD _height, DWORD _width, BYTE* _outputByteData) {
    std::vector<std::thread> threads;
    if (_numberOfThreads > _height - 2) _numberOfThreads = _height - 2;
    size_t expectedLinesPerThread = _height / _numberOfThreads;
    size_t spareLines = _height % _numberOfThreads;
    size_t realLinesPerThread = 0;
    for (int i = 0, j = 0; i < _numberOfThreads; ++i, ++j) {
        _inputByteData += realLinesPerThread * _width;
        _outputByteData += realLinesPerThread * _width;
        realLinesPerThread = j < spareLines ? expectedLinesPerThread + 1 : expectedLinesPerThread;
        threads.push_back(std::thread(_functionPointer, _inputByteData, realLinesPerThread, _width, _outputByteData));
    }
    for (auto& t : threads) t.join();
}

long long measureTime(const std::function<void()>& _wrappedFunction) {
    auto start = std::chrono::steady_clock::now();
    _wrappedFunction();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}