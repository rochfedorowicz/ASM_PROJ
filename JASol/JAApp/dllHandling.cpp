#include "dllHandling.h"

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