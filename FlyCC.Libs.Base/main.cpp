#define ILIB_ADD_LIB_INTERFACE_FUNCTIONS

#include <ILib.h>
#include <IFlags.h>
#include <IUtils.h>
#include <ISoket.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

LibInfo information = {
	"FlyCC.Libs.Base",
	"Base",
	"1.0.0.0",
	"FlyCC (AirGroup)",
	"Базовая библиотека для демострации",
	"1.0"
};

class Lib : public ILib {
public:
	LibInfo GetLibInfo() const override;

	bool Load(const string, const string&) override;
	bool Init() override;
	vector<string> Execute(const vector<string>&) override;
	bool Shutdown() override;
	bool UnLoad() override;
};

LibInfo Lib::GetLibInfo() const
{
	return information;
}
bool Lib::Load(const string verCore, const string& path)
{
	return true;
}
bool Lib::Init()
{
	return true;
}
vector<string> Lib::Execute(const vector<string>& args)
{
	if (args[0] == "test")
	{
		MessageBoxA(nullptr, "Привет, мир!", "Base", MB_OK | MB_ICONINFORMATION);
		return { "ok" };
	}
}
bool Lib::Shutdown()
{
	return true;
}
bool Lib::UnLoad()
{
	return true;
}

LibInfo GetLibInfoAPI()
{
	return information;
}
ILib* CreateLibAPI(const string verCore, const string& path)
{
	ILib* lib = new Lib();
	if (!lib->Load(verCore, path))
	{
		return nullptr;
	}
	else
	{
		return lib;
	}
}
bool DestroyLibAPI(ILib* lib)
{
	lib->UnLoad();
	delete lib;
	return true;
}