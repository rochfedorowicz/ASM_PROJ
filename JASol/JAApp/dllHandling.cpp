#include "dllHandling.h"

void instantiateThreads(const size_t& _numberOfThreads, MY_FUN_PTR& _functionToBeCalled) {
    std::vector<std::thread> threads;
    for (int i = 0; i < _numberOfThreads; i++) {
        threads.push_back(std::thread([&_functionToBeCalled]() {
            //printf("\nThread finished! Output is %d\n", functionToBeCalled(3, 5));
            //
            //
            }));
    }
    for (auto& t : threads) t.join();
}

bool loadDLLFunction(HINSTANCE& _hinstLib, const LPCWSTR& _libName, MY_FUN_PTR& _procAddress, const LPCSTR& _funName) {
    _hinstLib = LoadLibrary(_libName);
    if (_hinstLib != NULL) {
        LOGINFO("DLL named %ws loaded successfuly!", _libName);
        _procAddress = (MY_FUN_PTR)GetProcAddress(_hinstLib, _funName);
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

bool freeDLL(HINSTANCE& _hinstLib) {
    if (FreeLibrary(_hinstLib)) {
        LOGINFO("Library freed successfully!");
        return true;
    }
    else {
        LOGINFO("Failed to free library!");
        return false;
    }
}