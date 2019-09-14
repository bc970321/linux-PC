#include <iostream>
#include <string>
#include <list>
#include <cmath>
using namespace std;
string str;  
int i = 0;  
 
list<char> postFix;  
 
int T();  
int E1(int i);  
int T1();  
int T11(int i);  
int T2();  
int T22(int i);  
int T3();   
 
int E()
{  
	int t1_v = T1();  
	return E1(t1_v);  
}  
 
int E1(int ci)  
{  
	int e1_v = ci,
		e1_i = 0;
	if(i < str.size() && (str[i] == '+' || str[i] == '-'))  
	{  
		int ti = i;  
		i++;  
		int t1_v = T1();  
		
		if (str[ti] == '+')  
		{  
			e1_i = ci + t1_v;
			postFix.push_back('+');  
		}  
		else  
		{  
			e1_i = ci - t1_v;
			postFix.push_back('-');  
		}  
		e1_v = E1(e1_i);  
	}  
	return e1_v;
}  
 
int T1()  
{  
	int t2_v = T2();  
	int t11_v = T11(t2_v);  
	return t11_v;
}  
 
int T11(int ci)  
{  
	int sum = ci;
	if(i < str.size() && (str[i] == '*' || str[i] == '/'))  
	{  
		int ti = i;
		int t11_i;  
		i++;  
		
		int t2_v = T2();  
		if(str[ti] == '*')  
		{  
			postFix.push_back('*');  
			t11_i = ci * t2_v;
		}  
		else if(str[ti] == '/')  
		{  
			postFix.push_back('/');  
			t11_i = ci / t2_v;
		}  
		sum = T11(t11_i);  
		
	}  
	return sum;
}  
 
int T2()
{  
	int t3_v = T3();  
	return T22(t3_v);  
}  
 
int T22(int ci)  
{  
	int sum = ci;
	if (i < str.size() && str[i] == '^')  
	{  
		i++;  
		int t3_v = T3();  
		int t22_i = (int)pow(ci*1.0,t3_v*1.0);
		postFix.push_back('^'); 
		sum = T22(t22_i);  
	}  
	return sum;
}  
 
int T3() 
{  
	int t3_v = 0;
	while (i < str.size() && isalnum(str[i]))
	{
		t3_v = t3_v * 10 + str[i] - '0';
		i++;
	}
	if(i < str.size() && str[i] == '(')  
	{  
		i++;  
		t3_v = E();  
		if(str[i] == ')')
		{  
			i++;  
		}  
	}  
	return t3_v;
}  
 
int main()  
{  
	cin >> str;  
	int result = E();  
	cout << result;
	return 0;  
}  
