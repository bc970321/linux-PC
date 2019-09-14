/*************************************************************************
	> File Name:    CC_VarStore.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时01分10秒
 ************************************************************************/

#ifndef _CC_VARSTORE_H
#define _CC_VARSTORE_H

#include <map>
#include <string>
#include <stdexcept>

#include "CC_Types.h"

using std::map;
using std::string;
using std::runtime_error;

namespace SKL {
    class VarStore { 
    private : 
        map<string, Types> memory;
        VarStore *FatherStore;
    public : 
        VarStore (VarStore *newStore) : 
            FatherStore (newStore) {}
        bool setValue(string varName, const Types& val);
        void setValue(string varName);
        Types& getValue(string varName);
    };
}

#endif
