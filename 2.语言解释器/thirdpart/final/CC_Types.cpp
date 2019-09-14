/*************************************************************************
	> File Name:    CC_Types.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年08月15日 星期四 11时05分25秒
 ************************************************************************/
#include "CC_Types.h"


    template <typename T>
    class Types {
    private :
        T data;
    public :
        Types (T initData) : data (initData) {}
        bool setVal (T newVal) {
            return (this->data = newVal);
        }
        T getValue () {
            return this->data;
        }
    };

