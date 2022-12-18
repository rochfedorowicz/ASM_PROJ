#include "dllHandling.h"

bool loadDLL(HINSTANCE& _hinstLib, const LPCWSTR& _libName) {
    _hinstLib = LoadLibrary(_libName);
    if (_hinstLib != NULL) {
        LOGINFO("DLL named %ws loaded successfuly!", _libName);
    }
    else {
        LOGINFO("DLL named %ws failed to load!", _libName);
    }
    return false;
}

bool loadDLLFunction(HINSTANCE& _hinstLib, BITMAP_CHANGE_FN_TYPE& _procAddress, const LPCSTR& _funName) {
    if (_hinstLib != NULL) {
        _procAddress = (BITMAP_CHANGE_FN_TYPE)GetProcAddress(_hinstLib, _funName);
        if (NULL != _procAddress) {
            LOGINFO("Function named %s found!", _funName);
            return TRUE;
        }
        else {
            LOGINFO("Function named %s not found!", _funName);
        }
    }
    else {
        LOGINFO("Used DLL does not seem to be loaded yet!");
    }
    return false;
}

bool freeDLL(HINSTANCE& _hinstLib) {
    if (FreeLibrary(_hinstLib)) {
        LOGINFO("Library freed successfully!");
        return true;
    }
    else {
        LOGINFO("Failed to free library! Error Code: %d", GetLastError());
        return false;
    }
}

void instantiateThreads(size_t _numberOfThreads, BITMAP_CHANGE_FN_TYPE& _functionPointer, BYTE* _inputByteData,
    DWORD _height, DWORD _width, BYTE* _outputByteData) {
    std::vector<std::thread> threads;
    if (_numberOfThreads > _height - 2) _numberOfThreads = _height - 2;
    size_t expectedLinesPerThread = _height / _numberOfThreads;
    size_t spareLines = _height % _numberOfThreads;
    size_t realLinesPerThread = 0;
    for (int i = 0, j = 0; i < _numberOfThreads; ++i, ++j) {
        _inputByteData += /*i != 0 ? (realLinesPerThread - 1) * _width :*/ realLinesPerThread * _width;
        _outputByteData += /*i != 0 ? (realLinesPerThread - 1) * _width : */ realLinesPerThread * _width;
        realLinesPerThread = j < spareLines ? expectedLinesPerThread + 1 : expectedLinesPerThread;
        threads.push_back(std::thread(_functionPointer, _inputByteData, /*_numberOfThreads > 1 ? realLinesPerThread + 2 :*/ realLinesPerThread, _width, _outputByteData));
    }
    for (auto& t : threads) t.join();
}

long long measureTime(const std::function<void()>& _wrappedFunction) {
    auto start = std::chrono::steady_clock::now();
    _wrappedFunction();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}