/*************************************************************************
	> File Name:    CC_VarStore.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时06分01秒
 ************************************************************************/
#include "../include/CC_VarStore.h"

bool SKL::VarStore::setValue (string varName, const Types& val) {
    if (varName == "") {
        throw runtime_error("Invalid variable name <The variable name is empty>");
        return false;
    }
    if (this->memory.find(varName) == this->memory.end()) {
        if (this->FatherStore == nullptr) 
            throw runtime_error("No found this variable in this variable store");
        return this->FatherStore->setValue(varName, val);
    }
    this->memory[varName] = val;
    return true;
}

void SKL::VarStore::setValue (string varName) {
    Types _temp;
    this->memory[varName] = _temp;
}

SKL::Types& SKL::VarStore::getValue (string varName) {
    if (varName == "") {
        throw runtime_error("Invalid variable name <The variable name is empty>");
    }
    if (this->memory.find(varName) == this->memory.end()) {
        if (this->FatherStore == nullptr) 
            throw runtime_error("No found this variable in this variable store");
        return this->FatherStore->getValue(varName);
    }
    return this->memory[varName];
}
