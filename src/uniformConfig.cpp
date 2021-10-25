#include<uniformConfig.h>
uniformConfig::uniformConfig() {

}

uniformConfig::uniformConfig(std::vector<std::string> Name, std::vector<void*> DataPtr) {
	uniformName = Name;
	uniformDataPtr = DataPtr;
}

void uniformConfig::printName() {
	for (auto& element : uniformName) {
		std::cout << element << std::endl;
	}
}

void uniformConfig::printValue() {
	for (auto& element : uniformDataPtr) {
		std::cout << *((float*)element+1) << std::endl;
	}
}

std::vector<std::string> uniformConfig::getUniformList() {
	return uniformName;
}

std::vector<void*>	uniformConfig::getUniformDataPtrList() {
	return uniformDataPtr;
};

uniformConfig::~uniformConfig() {

}