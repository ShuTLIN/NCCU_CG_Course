#pragma once
#include<string>
#include<vector>
#include<iostream>

class uniformConfig {
public:
	uniformConfig();
	uniformConfig(std::vector<std::string> uniformName, std::vector<void*> uniformDataPtr);
	~uniformConfig();

	std::vector<std::string> getUniformList();
	std::vector<void*>	getUniformDataPtrList();
	void printName();
	void printValue();
private:
	std::vector<std::string> uniformName;
	std::vector<void*> uniformDataPtr;
};