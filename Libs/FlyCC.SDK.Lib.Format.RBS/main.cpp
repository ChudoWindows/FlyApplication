#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ILib.h>
#include <IFlags.h>
#include <ISoket.h>
#include <IUtils.h>

using namespace std;

LibInfo lib_information = {
	"FlyCC.SDK.Lib.Format.RBS",
	"RBS Format",
	"1.0"
	"FlyCC",
	"Формат файлов RBS",
	"1.0"
};

class MainLib : public ILib {
public:
	LibInfo GetLibInfo() const override;

	bool Load(const string, const string&) override;
	bool UnLoad() override;
	bool Init() override;
	bool Shutdown() override;
	vector<string> Execute(const vector<string>& args) override;
};

LibInfo MainLib::GetLibInfo() const
{
	return lib_information;
}
