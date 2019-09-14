/*************************************************************************
	> File Name:    6.virtual.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月07日 星期日 19时28分25秒
 ************************************************************************/

#include<iostream>
using namespace std;


class Animal {
public :
    Animal () {}
    Animal(string name) : __name(name), __age(3) {}
    virtual void run() {
        cout<< __name << " : I don't know how to run" << endl;
    }
    int &age() {return this->__age;}
    string name() { return this->__name; }
    virtual ~Animal() {
        cout << "Animal Destructor" << endl;
    }
private :
    string __name;
    int __age;
};

class Cat : public Animal {
public :
    Cat() : Animal("Cat-1") {}
    void run() {
        cout << name() << " : I can run with four legs" << endl;
    }
    ~Cat() {
        cout << "Cat Destructor" << endl;
    }

};

class Dog : virtual public Animal {
public : 
    Dog() : Animal("Dog-1") {}
    void run() {
        cout << name() << " : I can wang wang run" << endl;
    }
    int seek_age() {
        cout << "Dog seek age : " << &age() << endl;
        return age();
    }
    ~Dog() {
        cout << "Dog Destructor" << endl;
    }
};

class Bat : virtual public Animal {
public:
    Bat() : Animal("Bat-1") {} 
    void run () {
        cout << name() << " : I can flying" << endl;
    }
    void change_age() {
        age() += 1;
        cout << "Bat change age : " << age() << " " << &age() << endl;
    }
    ~Bat() {
        cout << "Bat Destructor" << endl;
    }

};

class SkyDog : public Dog, public Bat{
public:
    void run() {
        this->Dog::run();
    }
};

Animal *getAnimal() {
    int val = rand() % 3;
    switch (val) {
        case 0 : return new Cat();
        case 1 : return new Dog();
        case 2 : return new Bat();
    }
    return nullptr;
}

void func(Animal *p) {
    cout << "func p = " << p << endl;
}

void func(int x) {
    cout << "func x(int) = " << x << endl;
}

int main() {
    srand(time(0));
    func(nullptr);
    Animal **arr = new Animal*[20];
    for (int i = 0; i < 20; i++) {
        arr[i] = getAnimal();
    }
    for (int i = 0; i < 20; i++) {
        arr[i]->run();
    }
    for (int i = 0; i < 20; i++) {
        delete arr[i];
    }
    SkyDog sd;
    sd.change_age();
    sd.change_age();
    sd.change_age();
    sd.change_age();
    sd.change_age();
    sd.change_age();
    cout << sd.seek_age() << endl;
    return 0;
}
