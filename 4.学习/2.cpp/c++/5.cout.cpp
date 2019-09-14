/*************************************************************************
	> File Name:    5.cout.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年07月06日 星期六 19时09分33秒
 ************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
namespace haizei {
    class ostream {
    public:
        ostream &operator<<(int x) {
            printf("%d", x);
            return *this;
        }
        ostream &operator<<(const std::string &str) {
            printf("%s", str.c_str());
            return *this;
        }
        ostream &operator<<(const char &ch) {
            printf("%c", ch);
            return *this;
        }
        ostream &operator<<(double &a) {
            printf("%g", a);
            return *this;
        }
    };
    char endl = '\n';
    ostream cout;
}

int main() {
    haizei::cout << "hello world" << haizei::endl;
    
    double a = 3.78787878;
    haizei::cout << a << haizei::endl;
    std::cout << a << std::endl;
    return 0;
}
