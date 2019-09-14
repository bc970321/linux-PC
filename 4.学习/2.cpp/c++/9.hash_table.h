/*************************************************************************
	> File Name:    9.hash_table.h
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月16日 星期二 19时54分09秒
 ************************************************************************/

#ifndef _9.HASH_TABLE_H
#define _9.HASH_TABLE_H

namespace haizei {
    template<typename T, typename U>
    struct pair {
        pair() : first(), second() {}
        pair(const T &&a, const U &&b) : first(a), second(b) {} 
        T first;
        U second;
    };

    template<typename K> struct hash;
    template<>
    struct hash<int> {
        size_t operator()(int x) {
            return x;
        }
    };

    template<>
    struct hash<double> {
        size_t operator()(double x) {
            return *(size_t *)(&x);
        }
    };
    
    template<>
    struct hash<string> {
        size_t operator()(const string  &s) {
            int Hash = 0;
            for (int i = 0; i < s.length(); i++) {
                Hash = (Hash << 5) ^ s[i] ^ (Hash >> 3);
            }
            return Hash;
        }
    };

    template<typename K, typename T, typename HashT = haizei::hash<K>>
    class HashTable {
    public:
        HashTable(int size = 100) : size(size) {
            this->__data = new (pair<K, T> *)[this->size];
            this->map = new bool[this->size];
            for (int i = 0; i < size)
        }
        ~HashTable() {
            delete this->data;
            delete this->size;
        }
        T 





    private:
        size_t size;
        pair<K, T> **__data;
        bool *map;
        HashT hash_func;
    };




}

#endif
