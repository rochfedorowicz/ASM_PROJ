#pragma once
#include <thread>
#include <vector>
#include <string>
#include <mutex>

#include "macros.h"

template <typename PointerType, typename... Args>
void instantiateThreads(const size_t& _numberOfThreads, PointerType& _pointerType, Args... _args) {
    std::vector<std::thread> threads;
    std::mutex oStreamMutex;
    for (int i = 0; i < _numberOfThreads; i++) {
        threads.push_back(std::thread([&, i]() {
            oStreamMutex.lock();
            LOGINFO("Started %d thread", i + 1);
            oStreamMutex.unlock();
            _pointerType(_args...);
            oStreamMutex.lock();
            LOGINFO("Finished %d thread", i + 1);
            oStreamMutex.unlock();
            }));
    }
    for (auto& t : threads) t.join();
}

template <typename PointerType>
bool loadDLLFunction(HINSTANCE& _hinstLib, const LPCWSTR& _libName, PointerType& _procAddress, const LPCSTR& _funName) {
    _hinstLib = LoadLibrary(_libName);
    if (_hinstLib != NULL) {
        LOGINFO("DLL named %ws loaded successfuly!", _libName);
        _procAddress = (PointerType)GetProcAddress(_hinstLib, _funName);
        if (NULL != _procAddress) {
            LOGINFO("Function named %s found!", _funName);
            return TRUE;
        }
        else {
            LOGINFO("Function named %s not found!", _funName);
        }
    }
    else {
        LOGINFO("DLL named %ws failed to load!", _libName);
    }
    return false;
}

bool freeDLL(HINSTANCE&);