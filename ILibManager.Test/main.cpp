#include <iostream>
#include <WindowsUtils.h>
#include <IFlags.h>
#include <ILib.h>
#include <IUtils.h>
#include <ILibManager.h>

using namespace std;

int main()
{
	ILibManager manager;

	manager.AddLibToQueueLoading("F:\\FlyApplication\\Dist\\FlyCC.Libs.Base\\x64.Debug\\FlyCC.Libs.Base.dll");
	manager.SetVersionCore("1.0");
	
	vector<ILibManagerLoad> container = manager.LoadLibFromQueue();

	for (uint64_t i = 0; i < container.size(); i++)
	{
		if (container[i].Success == false)
		{
			cout << "Fail load \"" << container[i].Id << "\"" << endl;
			cout << "Path: \"" << container[i].Path << "\"" << endl;
			cout << "Error code: " << (uint64_t) container[i].Error << endl;
			cout << endl;
		}
	}

	ILib* lib = manager.GetLib("FlyCC.Libs.Base")->Lib;
	lib->Init();
	lib->Execute({"test"});
	lib->Shutdown();

	manager.AddAllToQueueUnload();
	manager.UnLoadLibFromQueue();

	manager.AddLibToQueueLoading("F:\\FlyApplication\\Dist\\FlyCC.Libs.Base\\x64.Debug\\FlyCC.Libs.Base.dll");
	container = manager.LoadLibFromQueue();

	for (uint64_t i = 0; i < container.size(); i++)
	{
		if (container[i].Success == false)
		{
			cout << "Fail load \"" << container[i].Id << "\"" << endl;
			cout << "Path: \"" << container[i].Path << "\"" << endl;
			cout << "Error code: " << (uint64_t)container[i].Error << endl;
			cout << endl;
		}
	}

	ILib* lib2 = manager.GetLib("FlyCC.Libs.Base")->Lib;
	lib2->Init();
	lib2->Execute({ "test" });
	lib2->Shutdown();

	manager.AddAllToQueueUnload();
	manager.UnLoadLibFromQueue();

	return 0;
}