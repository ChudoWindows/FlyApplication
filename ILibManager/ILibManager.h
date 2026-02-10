#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <IUtils.h>
#include <ISoket.h>
#include <IFlags.h>
#include <ILib.h>
#include <WindowsUtils.h>

using namespace std;

struct ILibManagerLoad {
	string Path = "";
	string Id = "";
	bool Success = false;
	ILibLoadError Error = ILibLoadError::None;
};
struct ILibManagerUnLoad {
	string Path = "";
	string Id = "";
	bool Success = false;
	ILibUnLoadError Error = ILibUnLoadError::None;
};
struct ILibManagerInfo {
	string Path = "";
	string Id = "";
	LibInfo Info;
};

class ILibManager {
private:
	vector<ILibLoaded*> libs;
	vector<string> queue_loading; // Пути
	vector<string> queue_unloading; // Id
	string ver_core = "1.0";

	ILibLoaded* GetLibByID(string);
	void RemoveLibByID(string);

public:
	ILibManager() = default;
	~ILibManager();

	void SetVersionCore(string version) { this->ver_core = version; }
	string GetVersionCore() { return this->ver_core; }

	void AddAllToQueueUnload();

	void AddLibToQueueLoading(string);
	vector<string> GetQueueLibsToLoading() { return this->queue_loading; }

	void AddLibToQueueUnLoading(string);
	vector<string> GetQueueLibsToUnLoading() { return this->queue_unloading; }

	vector<ILibManagerLoad> LoadLibFromQueue();
	vector<ILibManagerUnLoad> UnLoadLibFromQueue();

	ILibLoaded* GetLib(string id) { return this->GetLibByID(id); }

	static vector<ILibManagerInfo> GetLibInfoFromDir(string);
	static ILibManagerInfo GetLibInfoFromFile(string);
};