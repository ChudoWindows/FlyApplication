#pragma once

#include <vector>
#include <string>
#include <functional>

using namespace std;

class ISoket {
private:
	vector<string> container;
	function<void(string)> callback = nullptr;

public:
	ISoket() = default;
	~ISoket() = default;

	void AttachCallback(function<void(string)> callback) { this->callback = callback; }
	void DetachCallback() { this->callback = nullptr; }
	bool IsAttachedCallback() { return this->callback == nullptr ? false : true; }
	bool IsEmpty() { return this->container.size() == 0 ? true : false; }

	void AddToQueue(string);
	void AddToQueue(int);
	void AddToQueue(float);
	void AddToQueue(double);
	void AddToQueue(char);
	void AddToQueue(bool);
	void AddToQueue(char*, uint64_t);

	string GetLastValueString();
	int GetLastValueInt();
	float GetLastValueFloat();
	double GetLastValueDouble();
	char GetLastValueChar();
	bool GetLastValueBool();
	void GetLastValueCString(char*, uint64_t);
};