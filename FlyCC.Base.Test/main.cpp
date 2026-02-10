#define ILIB_SHOW_ERRORS


#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <ILib.h>
#include <IUtils.h>
#include <IFlags.h>
#include <ISoket.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	string path = "F:\\FlyApplication\\Dist\\FlyCC.Libs.Base\\x64.Debug\\FlyCC.Libs.Base.dll";
	string verCore = "1.0";

	ILibLoaded* loaded_lib = LoadLib(verCore, path);

	if (loaded_lib->Success == false)
	{
		cout << (uint64_t) loaded_lib->ErrorLoad << endl;
		UnLoadLib(loaded_lib);
		return -1;
	}

	LibInfo information = loaded_lib->Info;

	cout << "Lib information:" << endl;
	cout << "  - ID: \"" << information.id << "\"" << endl;
	cout << "  - Name: \"" << information.name << "\"" << endl;
	cout << "  - Version: \"" << information.version << "\"" << endl;
	cout << "  - Author: \"" << information.author << "\"" << endl;
	cout << "  - Description: \"" << information.description << "\"" << endl;
	cout << "  - Minimum version core: \"" << information.minVerCore << "\"" << endl;
	cout << endl;

	loaded_lib->Lib->Init();

	loaded_lib->Lib->Execute({"test"});

	loaded_lib->Lib->Shutdown();

	UnLoadLib(loaded_lib);

	return 0;
}