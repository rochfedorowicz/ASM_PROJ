#include "pch.h"

#include "libManager.h"

LibManager::LibManager() {
	hinstLibs = new std::map<std::string, HINSTANCE>();
	loadedFunction = new std::map<std::string, BITMAP_CHANGE_FN_TYPE>();
}

LibManager::~LibManager() {
	delete hinstLibs;
	delete loadedFunction;
}

LPCWSTR LibManager::strToWStr(std::string _string) {
	std::wstring newWstring(_string.size(), L'#');
	mbstowcs(&newWstring[0], _string.c_str(), _string.size());
	return newWstring.c_str();
}

bool LibManager::loadLibrary(std::string _nameOfLibrary) {
	HINSTANCE newHinst = NULL;
	hinstLibs->insert(std::pair<std::string, HINSTANCE>(_nameOfLibrary, newHinst));
	if (loadDLL(hinstLibs->at(_nameOfLibrary), strToWStr(_nameOfLibrary))) {
		return true;
	}
	else {
		hinstLibs->erase(_nameOfLibrary);
		return false;
	}
}

bool LibManager::loadFunction(std::string _nameOfLibrary, std::string _nameOfFucntion) {
	if (hinstLibs->find(_nameOfLibrary) != hinstLibs->end() &&
		hinstLibs->at(_nameOfLibrary) != NULL) {
		BITMAP_CHANGE_FN_TYPE newFunc = NULL;
		loadedFunction->insert(std::pair<std::string, BITMAP_CHANGE_FN_TYPE>(_nameOfFucntion, newFunc));
		if (loadDLLFunction(hinstLibs->at(_nameOfLibrary),
			loadedFunction->at(_nameOfFucntion),
			_nameOfFucntion.c_str())) {
			return true;
		}
		else {
			loadedFunction->erase(_nameOfFucntion);
			return false;
		}
	}
	else {
		return false;
	}
}

BITMAP_CHANGE_FN_TYPE LibManager::getFunction(std::string _nameOfFunction) {
	return loadedFunction->at(_nameOfFunction);
}