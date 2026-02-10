#include "ILib.h"
#include "IUtils.h"

void ShowError(const string textError, uint8_t errorCode, bool isException = false, const string exceptionError = "")
{
	if (_SHOW_ERRORS)
	{
		string message = "Во время загрузки библиотеки произошла ошибка!\n";
		message += "Ошибка:\n";
		message += "  - Код ошибки: ";
		message += to_string(errorCode);
		message += "\n  - Ошибка: ";
		message += textError;
		message += "\n";

		if (isException)
		{
			message += "\nИсключение выполнения:\n";
			message += "  - ";
			message += exceptionError;
			message += "\n";
		}

		message += "Для решения проблемы попробуйте переустановить программу";

		MessageBoxA(nullptr, message.c_str(), "Интерфейс ILib", MB_OK | MB_ICONERROR);
	}
}

void ShowErrorUnLoad(const string text, uint8_t errorCode)
{
	if (_SHOW_ERRORS)
	{
		string message = "Во время выгрузки библиотеки из памяти произошла ошибка!\n";
		message += "Ошибка:\n";
		message += "  - Код ошибки: ";
		message += to_string(errorCode);
		message += "\n  - Ошибка: ";
		message += text;
		message += "\nДля решения проблемы попробуйте перезапустить или переустановить программу";

		MessageBoxA(nullptr, message.c_str(), "Интерфейс ILib", MB_OK | MB_ICONERROR);
	}
}

ILibLoaded* LoadLib(const string ver_core, string path)
{
	ILibLoaded* answer = new ILibLoaded();
	answer->Path = path;

	ifstream file(path);

	if (!file or !file.is_open())
	{
		answer->ErrorLoad = ILibLoadError::FailOpenFile;
		answer->Success = false;

		ShowError("Не удалось открыть файл для чтения", (uint8_t) answer->ErrorLoad);
		return answer;
	}
	else
	{
		file.close();
	}

	try
	{
		answer->Descriptor = LoadLibraryA(path.c_str());

		if (!answer->Descriptor)
		{
			answer->Success = false;
			answer->ErrorLoad = ILibLoadError::FailOpenDescriptor;

			ShowError("Не удалось открыть дескриптор для загрузки библиотеки", (uint8_t)answer->ErrorLoad);
			return answer;
		}

		answer->Functions.GetInfo = (GetLibInfoFunc)GetProcAddress(answer->Descriptor, "GetLibInfo");
		answer->Functions.Create = (CreateLibFunc)GetProcAddress(answer->Descriptor, "CreateLib");
		answer->Functions.Destroy = (DestroyLibFunc)GetProcAddress(answer->Descriptor, "DestroyLib");

		if (!answer->Functions.GetInfo or !answer->Functions.Create or !answer->Functions.Destroy)
		{
			answer->Success = false;
			answer->ErrorLoad = ILibLoadError::FailLoadInterfaceFunctions;

			ShowError("Не удалось загрузить одну или несколько функций интерфейса библиотеки", (uint8_t) answer->ErrorLoad);
			return answer;
		}

		answer->Info = answer->Functions.GetInfo();

		if (IUtils::CompareVersion(answer->Info.minVerCore, ver_core) == IUtils::CompareResult::Above)
		{
			answer->Success = false;
			answer->ErrorLoad = ILibLoadError::RequireNewCore;

			ShowError("Данной расширение требует более новое версию ядра программы", (uint8_t) answer->ErrorLoad);
			return answer;
		}

		answer->Lib = answer->Functions.Create(path, ver_core);

		if (!answer->Lib)
		{
			answer->Success = false;
			answer->ErrorLoad = ILibLoadError::FailCreateLibInMemory;

			ShowError("Не удалось создать новый экземпляр интерфеса библиотеки в памяти", (uint8_t) answer->ErrorLoad);
			return answer;
		}

		answer->Success = true;
		answer->ErrorLoad = ILibLoadError::None;

		return answer;
	}
	catch (exception& e)
	{
		answer->Success = false;
		answer->ErrorLoad = ILibLoadError::Exception;

		ShowError("Во время выполнения произошло неожиданное исключение", (uint8_t) answer->ErrorLoad, true, e.what());
		return answer;
	}
}

ILibUnLoadError UnLoadLib(ILibLoaded* lib)
{
	if (!lib)
	{
		ShowErrorUnLoad("Не передан объект для выгрузки", (uint8_t) ILibUnLoadError::FoundNull);
		return ILibUnLoadError::FoundNull;
	}

	if (lib->Lib)
	{
		if (!lib->Functions.Destroy(lib->Lib))
		{
			ShowErrorUnLoad("Не удалось выгрузить библиотеку из памяти. Работа программы может быть не стабильна! Ситуация 1", (uint8_t) ILibUnLoadError::FailUnLoad);
			
			FreeLibrary(lib->Descriptor);
			delete lib;
			
			return ILibUnLoadError::FailUnLoad;
		}

		if (!FreeLibrary(lib->Descriptor))
		{
			ShowErrorUnLoad("Не удалось освободить дескриптор библиотеки. Работа программы может быть не стабильна! Ситуация 2", (uint8_t) ILibUnLoadError::FailFree);
			delete lib;

			return ILibUnLoadError::FailFree;
		}

		return ILibUnLoadError::None;
	}

	if (lib->Descriptor)
	{
		if (!FreeLibrary(lib->Descriptor))
		{
			ShowErrorUnLoad("Не удалось освободить дескриптор библиотеки. Работа программы может быть не стабильна! Ситуация 3", (uint8_t) ILibUnLoadError::FailFree);
			delete lib;

			return ILibUnLoadError::FailFree;
		}
	}

	delete lib;
	return ILibUnLoadError::None;
}