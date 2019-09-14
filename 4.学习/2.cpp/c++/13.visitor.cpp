/*************************************************************************
	> File Name:    13.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月26日 星期五 18时43分29秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
using namespace std;

struct Cat;
struct Dog;
struct People;

struct Animal {
    struct IVisitor {
        virtual void visit(Cat *) = 0;
        virtual void visit(Dog *) = 0;
        virtual void visit(People *) = 0;
    };
    virtual void Accept(IVisitor *vis) = 0;
    virtual void say() = 0;
};

struct Cat : Animal {
    void say() {
        cout << "miao miao miao" << endl;
    }
    virtual void Accept(IVisitor *vis) {
        vis->visit(this);
    }
};

struct Dog : Animal {
    void say() {
        cout << "wang wang wang" << endl;
    }
    virtual void Accept(IVisitor *vis) {
        vis->visit(this);
    }
};

struct  People : Animal {
    void say() {
        cout << "ha ha ha" << endl;
    }
    virtual void Accept(IVisitor *vis) {
        vis->visit(this);
    }
};


Animal *getCat() {
    return new Cat;
}


Animal *getDog() {
    return new Dog;
}


Animal *getPeople() {
    return new People;
}

struct Output : Animal::IVisitor {
    void visit(Cat *a) {
        cout << "miao miao miao" << endl;
    }
    void visit(Dog * a) {
        cout << "this is a dog" << endl;
    }
    void visit(People *a) {
        cout << "this is a person" << endl;
    }
};

struct shu : Animal::IVisitor {
    void visit(Cat *a) {
        cout << 1 << endl;
    }
    void visit(Dog *a) {
        cout << 2 << endl;
    
    }
    void visit(People *a) {
        cout << 3 << endl;
    }
};

Animal *(*getFunc[3])() = {getCat, getDog, getPeople};

int main() {
    srand(time(0));
    Animal *arr[20];
    for (int i = 0; i < 20; i++) {
        arr[i] = getFunc[rand() % 3]();
    }
    for (int i = 0; i < 20; i++) {
        Output vis;
        shu sss;
        arr[i]->Accept(&sss);
        arr[i]->Accept(&vis);
    }
    return 0;
}
