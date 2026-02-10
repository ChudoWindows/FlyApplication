#pragma once

#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class WindowsUtils {
public:
	static vector<string> GetListFiles(string path, string mask);
};