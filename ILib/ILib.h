#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "ISoket.h"
#include "IFlags.h"
#include "IUtils.h"

using namespace std;

#ifdef ILIB_SHOW_ERRORS
const bool _SHOW_ERRORS = true;
#else
const bool _SHOW_ERRORS = false;
#endif

struct LibInfo {
	string id = "";
	string name = "";
	string version = "";
	string author = "";
	string description = "";
	string minVerCore = "";
};

class ILib {
public:
	virtual LibInfo GetLibInfo() const = 0;

	virtual bool Load(const string, const string&) = 0;
	virtual bool Init() = 0;
	virtual vector<string> Execute(const vector<string>&) = 0;
	virtual bool Shutdown() = 0;
	virtual bool UnLoad() = 0;

	ISoket* SoketToCore = nullptr;
	ISoket* SoketToLib = nullptr;
};

LibInfo GetLibInfoAPI();
ILib* CreateLibAPI(const string, const string&);
bool DestroyLibAPI(ILib*);

enum class ILibLoadError {
	None,
	FailOpenFile,
	FailOpenDescriptor,
	FailLoadInterfaceFunctions,
	RequireNewCore,
	FailCreateLibInMemory,
	Exception
};
enum class ILibUnLoadError {
	None,
	FoundNull,
	FailUnLoad,
	FailFree
};

typedef LibInfo (*GetLibInfoFunc)();
typedef ILib* (*CreateLibFunc)(const string, const string&);
typedef bool (*DestroyLibFunc)(ILib*);

struct ILibFunctions {
	GetLibInfoFunc GetInfo = nullptr;
	CreateLibFunc Create = nullptr;
	DestroyLibFunc Destroy = nullptr;
};
struct ILibLoaded {
	string Path = "";
	bool Success = false;
	ILibLoadError ErrorLoad = ILibLoadError::None;
	HMODULE Descriptor = nullptr;
	ILib* Lib = nullptr;
	LibInfo Info;
	ILibFunctions Functions;
};

ILibLoaded* LoadLib(string, string);
ILibUnLoadError UnLoadLib(ILibLoaded*);