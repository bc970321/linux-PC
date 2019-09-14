/*************************************************************************
	> File Name:    27.hashtable.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月07日 星期日 19时10分45秒
 ************************************************************************/

#ifndef _27.HASHTABLE_H
#define _27.HASHTABLE_H

typedef int (*HashFuncRaw)(const void *value);

class HashFunc {
public :
    virtual int operator()(const void *value) = 0;
    virtual ~HashFunc() {}
};

class HashTable {
public :
    HashTable(HashFunc &hc) : __hc(&hc), __hcr(nullptr) {}
    HashTable(HashFuncRaw hc) : __hcr(hc), __hc(nullptr) {}
    int get_hash(const void *data) {
        if (this->__hc) {
            return (*(this->__hc))(data);
        } else {
            return this->__hcr(data);
        }
    }
private :
    HashFunc *__hc;
    HashFuncRaw __hcr;
}

#endif
