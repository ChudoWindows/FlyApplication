#include "WindowsUtils.h"

vector<string> WindowsUtils::GetListFiles(string path, string mask)
{
	vector<string> container;

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA((path + "\\" + mask).c_str(), &findData);

	do
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			container.push_back(findData.cFileName);
		}
	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);

	return container;
}