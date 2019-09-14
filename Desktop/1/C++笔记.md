# C++笔记

#### 数组与vector类

数组求和

```c++
vector<int> a = {1, 2, 3, 4, 5};
int sum = 0;
for (auto x : a) {
    aum += x;
}
```

寻找a数组里是否有b数组里的任意数字

```c++
vector<int> a = {1, 2, 3, 4, 5};
vector<int> b = {3, 4, 5, 6, 7};
auto it = find_first_of(begin(a), end(a), begin(b), end(b));
bool found = (it != end(a));
```

注：此时it是迭代器

倒序排序

```c++
#include <vector>
#include <algorithm>

int main() {
    vector<int> a = {2, 4, 5, 3, 1};
    sort(
    	begin(a);
    	end(a);
    	[](int x, int y) {return x >= y;}
    );
}
```

查找子字符串

strstr函数

```c++
char s[] = "abcdefg";
char* x = strstr(s, "cde"); // x == s + 2
char* y = strstr(s, "CDE"); // y == nullptr
```

find函数

```c++
string s = "abcdefg";
auto x = s.find("cde"); // x == 2
auto y = s.find("CDE"); // y == string::npos
```

替换子字符串

```c++
void Replace(string& str, const string& toFind, const string& toReplace)
{
    while (true)
    {
        auto pos = str.find(toFind);
        if (pos == string::npos)
        {
            break;
        }
        str.replace(begin(str) + pos, begin(str) + pos + toFind.size(), toReplace);
    }
}
```

#### 对象

##### 1.缺省函数

当类里没有任何构造函数、或者使用了=default时 系统会替我们生成一个缺省构造函数

#### lambda表达式

语法： [捕获] (参数) {一些语句}

[=]：需要的值都复制，不可以修改外边的值

[&]：需要的值都复制它们的引用，可以使用外部的vector，并可修改它

[&, x]：除x外需要的值就复制它们的引用

#### struct和class

##### 区别：

struct的成员和基类默认是public访问权限，class是priva

当前置声名的时候，如果对于同一个类型，有的时候用class，有点时候用struct，或者前置声明跟实际不一样，会有警告

##### 注：c语言struct声明的类型和变量可以是一样的，c++则不可以

#### 左值与右值

在这条语句中，i 是左值，0 是临时值，就是右值。在下面的代码中，i 可以被引用，0 就不可以了。立即数都是右值。

```c++
int i = 0;
```

在这个例子中，0 作为右值出现在了”=”的左边。但是赋值对象是 i 或者 j，都是左值。

```c++
((i>0) ? i : j) = 1;
```

在 C++11 之前，右值是不能被引用的，最大限度就是用常量引用绑定一个右值。

```c++
const int &a = 1;
```

在这种情况下，右值不能被修改的。但是实际上右值是可以被修改的

```c++
T().set().get();
```

T 是一个类，set 是一个函数为 T 中的一个变量赋值，get 用来取出这个变量的值。在这句中，T() 生成一个临时对象，就是右值，set() 修改了变量的值，也就修改了这个右值。

既然右值可以被修改，那么就可以实现右值引用。右值引用能够方便地解决实际工程中的问题，实现非常有吸引力的解决方案。

##### 左值和右值的语法符号

左值的声明符号为”&”， 为了和左值区分，右值的声明符号为”&&”。

```c++
void process_value(int& i) { 
 std::cout << "LValue processed: " << i << std::endl; 
} 
 
void process_value(int&& i) { 
 std::cout << "RValue processed: " << i << std::endl; 
} 
 
int main() { 
 int a = 0; 
 process_value(a); 
 process_value(1); 
}
```

运行结果 :

```c++
LValue processed: 0 
RValue processed: 1
```

Process_value 函数被重载，分别接受左值和右值。由输出结果可以看出，临时对象是作为右值处理的。

但是如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象。

```c++
void process_value(int& i) { 
 std::cout << "LValue processed: " << i << std::endl; 
} 
 
void process_value(int&& i) { 
 std::cout << "RValue processed: " << i << std::endl; 
} 
 
void forward_value(int&& i) { 
 process_value(i); 
} 
 
int main() { 
 int a = 0; 
 process_value(a); 
 process_value(1); 
 forward_value(2); 
}
```

运行结果：

```c++
LValue processed: 0 
RValue processed: 1 
LValue processed: 2
```

虽然 2 这个立即数在函数 forward_value 接收时是右值，但到了 process_value 接收时，变成了左值。

##### 转移语句的定义

右值引用是用来支持转移语义的。转移语义可以将资源 ( 堆，系统对象等 ) 从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，能够大幅度提高 C++ 应用程序的性能。临时对象的维护 ( 创建和销毁 ) 对性能有严重影响。

转移语义是和拷贝语义相对的，可以类比文件的剪切与拷贝，当我们将文件从一个目录拷贝到另一个目录时，速度比剪切慢很多。

通过转移语义，临时对象中的资源能够转移其它的对象里。

在现有的 C++ 机制中，我们可以定义拷贝构造函数和赋值函数。要实现转移语义，需要定义转移构造函数，还可以定义转移赋值操作符。对于右值的拷贝和赋值会调用转移构造函数和转移赋值操作符。如果转移构造函数和转移拷贝操作符没有定义，那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用。

普通的函数和操作符也可以利用右值引用操作符实现转移语义。

##### 实现转移构造函数和转移赋值函数

以一个简单的 string 类为示例，实现拷贝构造函数和拷贝赋值操作符。

```c++
class MyString { 
private: 
 char* _data; 
 size_t   _len; 
 void _init_data(const char *s) { 
   _data = new char[_len+1]; 
   memcpy(_data, s, _len); 
   _data[_len] = '\0'; 
 } 
public: 
 MyString() { 
   _data = NULL; 
   _len = 0; 
 } 
 
 MyString(const char* p) { 
   _len = strlen (p); 
   _init_data(p); 
 } 
 
 MyString(const MyString& str) { 
   _len = str._len; 
   _init_data(str._data); 
   std::cout << "Copy Constructor is called! source: " << str._data << std::endl; 
 } 
 
 MyString& operator=(const MyString& str) { 
   if (this != &str) { 
     _len = str._len; 
     _init_data(str._data); 
   } 
   std::cout << "Copy Assignment is called! source: " << str._data << std::endl; 
   return *this; 
 } 
 
 virtual ~MyString() { 
   if (_data) free(_data); 
 } 
}; 
 
int main() { 
 MyString a; 
 a = MyString("Hello"); 
 std::vector<MyString> vec; 
 vec.push_back(MyString("World")); 
}
```

运行结果：

```c++
Copy Assignment is called! source: Hello 
Copy Constructor is called! source: World
```

这个 string 类已经基本满足我们演示的需要。在 main 函数中，实现了调用拷贝构造函数的操作和拷贝赋值操作符的操作。MyString(“Hello”) 和 MyString(“World”) 都是临时对象，也就是右值。虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值，造成了没有意义的资源申请和释放的操作。如果能够直接使用临时对象已经申请的资源，既能节省资源，有能节省资源申请和释放的时间。这正是定义转移语义的目的。

我们先定义转移构造函数。

```c++
MyString(MyString&& str) { 
   std::cout << "Move Constructor is called! source: " << str._data << std::endl; 
   _len = str._len; 
   _data = str._data; 
   str._len = 0; 
   str._data = NULL; 
}
```

和拷贝构造函数类似，有几点需要注意：

1. 参数（右值）的符号必须是右值引用符号，即“&&”。
2. 参数（右值）不可以是常量，因为我们需要修改右值。
3. 参数（右值）的资源链接和标记必须修改。否则，右值的析构函数就会释放资源。转移到新对象的资源也就无效了。

现在我们定义转移赋值操作符。

```c++
MyString& operator=(MyString&& str) { 
   std::cout << "Move Assignment is called! source: " << str._data << std::endl; 
   if (this != &str) { 
     _len = str._len; 
     _data = str._data; 
     str._len = 0; 
     str._data = NULL; 
   } 
   return *this; 
}
```

这里需要注意的问题和转移构造函数是一样的。

增加了转移构造函数和转移复制操作符后，我们的程序运行结果为 :

```c++
Move Assignment is called! source: Hello 
Move Constructor is called! source: World
```

由此看出，编译器区分了左值和右值，对右值调用了转移构造函数和转移赋值操作符。节省了资源，提高了程序运行的效率。

有了右值引用和转移语义，我们在设计和实现类时，对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率。