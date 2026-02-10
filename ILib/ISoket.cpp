#include "ISoket.h"

void ISoket::AddToQueue(string value)
{
	if (this->IsAttachedCallback())
	{
		this->callback(value);
	}
	else
	{
		this->container.push_back(value);
	}
}
void ISoket::AddToQueue(int value)
{
	this->AddToQueue(to_string(value));
}
void ISoket::AddToQueue(float value) 
{
	this->AddToQueue(to_string(value));
}
void ISoket::AddToQueue(double value)
{
	this->AddToQueue(to_string(value));
}
void ISoket::AddToQueue(char value)
{
	this->AddToQueue(string(value, 1));
}
void ISoket::AddToQueue(bool value)
{
	this->AddToQueue(value == true ? "true" : "false");
}
void ISoket::AddToQueue(char* buffer, uint64_t size)
{
	string tmp = "";
	for (uint64_t i = 0; i < size; i++)
	{
		tmp += buffer[i];
	}
	this->AddToQueue(tmp);
}

string ISoket::GetLastValueString()
{
	string end = this->container.back();
	this->container.pop_back();
	return end;
}
int ISoket::GetLastValueInt()
{
	return stoi(this->GetLastValueString());
}
float ISoket::GetLastValueFloat()
{
	return stof(this->GetLastValueString());
}
double ISoket::GetLastValueDouble()
{
	return stod(this->GetLastValueString());
}
bool ISoket::GetLastValueBool()
{
	string tmp = this->GetLastValueString();
	return tmp == "true" or tmp == "True" or tmp == "Yes" or tmp == "yes" or tmp == "1" ? true : false;
}
char ISoket::GetLastValueChar()
{
	return this->GetLastValueString()[0];
}
void ISoket::GetLastValueCString(char* buffer, uint64_t size)
{
	string tmp = this->GetLastValueString();

	for (uint64_t i = 0; i < tmp.length(); i++)
	{
		if (i + 1 > size) {
			return;
		}
		buffer[i] = tmp[i];
	}
}