#include "ILibManager.h"

ILibManager::~ILibManager()
{
	this->AddAllToQueueUnload();
	this->UnLoadLibFromQueue();
}

void ILibManager::AddAllToQueueUnload()
{
	for (uint64_t i = 0; i < this->libs.size(); i++)
	{
		this->queue_unloading.push_back(this->libs[i]->Info.id);
	}
}

void ILibManager::AddLibToQueueLoading(string path)
{
	this->queue_loading.push_back(path);
}
void ILibManager::AddLibToQueueUnLoading(string id)
{
	this->queue_unloading.push_back(id);
}

vector<ILibManagerLoad> ILibManager::LoadLibFromQueue()
{
	vector<ILibManagerLoad> answer;

	for (uint64_t i = 0; i < this->queue_loading.size(); i++)
	{
		ILibLoaded* lib = LoadLib(this->ver_core, this->queue_loading[i]);

		if (lib->Success == false)
		{
			answer.push_back({
				this->queue_loading[i],
				lib->Info.id != "" ? lib->Info.id : "None",
				false,
				lib->ErrorLoad
			});
		}
		else
		{
			answer.push_back({
				this->queue_loading[i],
				lib->Info.id,
				true,
				ILibLoadError::None
			});

			this->libs.push_back(lib);
		}
	}

	this->queue_loading.clear();
	return answer;
}

ILibLoaded* ILibManager::GetLibByID(string id)
{
	for (uint64_t i = 0; i < this->libs.size(); i++)
	{
		if (this->libs[i]->Info.id == id)
		{
			return this->libs[i];
		}
	}
	return nullptr;
}
void ILibManager::RemoveLibByID(string id)
{
	vector<ILibLoaded*> container;
	for (uint64_t i = 0; i < this->libs.size(); i++)
	{
		if (this->libs[i]->Info.id != id)
		{
			container.push_back(this->libs[i]);
		}
	}
	this->libs = container;
}

vector<ILibManagerUnLoad> ILibManager::UnLoadLibFromQueue()
{
	vector<ILibManagerUnLoad> answer;
	for (uint64_t i = 0; i < this->queue_unloading.size(); i++)
	{
		ILibManagerUnLoad tmp;
		ILibLoaded* lib = this->GetLibByID(this->queue_unloading[i]);

		tmp = {
			lib->Path,
			lib->Info.id,
			false,
			ILibUnLoadError::None
		};

		ILibUnLoadError unload_error = UnLoadLib(lib);
		
		if (unload_error == ILibUnLoadError::None)
		{
			tmp.Success = true;
			answer.push_back(tmp);
		}
		else
		{
			tmp.Error = unload_error;
			answer.push_back(tmp);
		}

		this->RemoveLibByID(tmp.Id);
	}

	this->queue_unloading.clear();
	return answer;
}

ILibManagerInfo ILibManager::GetLibInfoFromFile(string path)
{
	ILibManagerInfo answer;
	HMODULE hLib = LoadLibraryA(path.c_str());

	if (!hLib)
	{
		answer = {
			path,
			"None",
			nullptr
		};
	}

	GetLibInfoFunc get_info = (GetLibInfoFunc)GetProcAddress(hLib, "GetInfoLib");

	if (!get_info)
	{
		FreeLibrary(hLib);
		answer = {
			path,
			"None",
			nullptr
		};
	}

	LibInfo info = get_info();

	if (!get_info)
	{
		FreeLibrary(hLib);
		answer = {
			path,
			"None",
			nullptr
		};
	}

	FreeLibrary(hLib);

	answer = {
		path,
		info.id,
		info
	};

	return answer;
}
vector<ILibManagerInfo> ILibManager::GetLibInfoFromDir(string path)
{
	vector<ILibManagerInfo> answer;
	vector<string> container = WindowsUtils::GetListFiles(path, "*.dll");

	for (uint64_t i = 0; i < container.size(); i++)
	{
		answer.push_back(ILibManager::GetLibInfoFromFile(path + "\\" + container[i]));
	}
	return answer;
}