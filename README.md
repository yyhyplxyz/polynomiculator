# 多项式计算器实验报告
## 目的
#### 做一个命令行形式的计算器，进行多项式的加减乘和求导求积分运算，自己希望可以通过该项目进一步掌握linux操作系统的使用方法，和面向对象思想的应用知识。
## 实验环境
#### 本实验基于_Ubuntu_操作系统，参考了主流代码规范。
### 编程语言和开发工具
#### 编程语言：_ANSI C/C++_
#### 开发工具： 利用_atom_编辑代码，_gnu_编译器进行编译，及_gdb_进行调试。
## 分析与设计
### 需求分析
#### 要对用户的输入字符串进行格式判定，并将其转换为储存在程序中的多项式，并进行数学运算，给出用户答案。本程序支持的数学运算有**+ - * 求导 求积分**,为了能够方便用户下次使用，添加了数据保存功能（即文件读写）。
### 类结构设计
#### 自定义了一个单项式的类，再用单项式的数组作为私有数据成员，定义了一个多项式的类，最后建了一个map，对应多项式名字与多项式本身，然后为了方便，再创建了一个大类Calculator，存储map以及对应的计算器各项功能。
### 设计细节
#### 1. 用户先输入1，再按空格，然后输入多项式操作，可以给出该运算的多项式结果，如输入**_(2,3)(3,2) * (2,2)_** ，**_!p_**(进行求导)， **_~p_**(求积分)注意：可以不按指数降序顺序输入，并且程序会询问是否需要命名，若命名(请直接输入需要命的名字)则自动保存到calculator类中的map里，若不需要，请输入**_n_**,若重名，程序会提醒是否覆盖。
#### 2. 用户先输入2，再按空格，然后输入求值的格式，如**_(2,3)[4]_""或**_p[4]_**(如果有命名p这个多项式的话)，如果输入形如**_p[2,4]_的式子可以对p这个式子进行从二到四的积分操作。
#### 3. 用户输入**_3 p_**可以删除目前计算器存储的p这个多项式。
#### 4.用户输入4，可以将现在计算器中有命名的多项式永久保存到文件中
#### 5.用户输入5， 可以讲文件中的多项式代替目前计算器map里存着的多项式
#### 6.用户输入6，可以查看用户手册
#### 7.用户输入7，可以退出程序。
### 代码
#### 整体架构
````c++
#include <iostream>
#include"Polynomial_calculator.h"
#include"Polynomial_calculator.cpp"
using namespace std;
int main()
{
	Calculator myCalculator;
	myCalculator.displayHead("Hello, my dump cousin!");
	myCalculator.displayInstruction();
	int flag = 1;
	string order;
	cout << ":: ";
	getline(cin, order, '\n'); //当指令是7时，退出程序
	while (order != "7")
	{
		string instruction, content;
		myCalculator.inputOrder(order, instruction, content);
		myCalculator.switcher(instruction, content);//根据不同指令转到不同函数
		cout << "::";
		getline(cin, order, '\n');
	}
cout << "Goodbye!" << endl;
cout << "Please finish the homework yourself next time!" << endl;
	return 0;
}

````
#### 关键部分(实现字符串到多项式运算的转变)
````c++
void Calculator::show(bool operationType, const std::string& content, std::string& key, Polynomial& result)
{
	if (operationType == true)
	{
		Polynomial lhs;
		Polynomial rhs;
		char sign = getOperationSign(content);
		if (inputContent(content, key, lhs, rhs, sign) == false)return;
		switch (sign)
		{
		case '+':result = lhs + rhs; break;
		case '-':result = lhs - rhs; break;
		case '*':result = lhs * rhs; break;
		}
	}
	else
	{
		Polynomial poly;
		char sign = getOperationSign(content);
		if(sign == '?')
		{
			stringToPolynomial(content,result);
		}
		if (inputContent(content, key, poly, sign, false) == false)return;
		switch (sign)
		{
		case '!':result = !poly; break;
		case '~':result = ~poly; break;
		}
	}
	if (!key.empty())
		this->getDictionary().emplace(key, result);
	else {
		cout << "Do you want to save this polynomial?" << endl;
		cout << "::";
		cin >> key;
		flag = 1;
		if (key != "n" && !key.empty() && key != " ")
		{
			if(this->getDictionary().find(key) != this->getDictionary().end())
			{
				cout << "The polynomial is already exist, do you want to replace it?" << " Please enter Y / N" << endl;
				char a;
				cin >> a;
				if(a == 'Y')
				{
					this->getDictionary().erase(key);
				}
				if(a != 'N' && a != 'Y')
				{
					cout << "You enter a wrong character, the new polynomial won't be saved" << endl;
				}
			}
		}
			this->getDictionary().emplace(key, result);
			 if( key.empty() || key == " ")
					cout << "You can't enter the wrong format!" << endl;
	}
	displayHead("");
	cout << "The result:\n" << string(5, ' ') << result << endl;
	//displaySimpleInstruction(true);
	cout << endl;
}

````
### 实验结果与测试改错
#### 最新修改，模拟智能识别简单错误，改stod函数为sscanf函数，忽略掉不合法的字符
![忽视a该字符，自动替换成0](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2017-02-21%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
#### 常规输入的实验结果
![用户指南](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2014-16-37%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
![数学计算](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2014-17-59%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
![map中存储了的多项式](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2014-18-29%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
![求值运算](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2014-19-43%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
![完全错误的输入](https://github.com/yyhyplxyz/polynomiculator/blob/pictures/2017-04-16%2014-24-52%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)
### 心得体会
#### 首先通过本题深刻理解了软件开发过程中，开发前的框架设计和数据结构的选取乃至算法的使用是非常重要的，这个能力应该也是在美国的STEM职业中分别程序员与软件开发工程师的重要标准
#### 其次自己通过实际动手练习，大大提高了对string类的了解，包括getline，stod，sscanf几个函数，熟悉了文件读写的操作。
#### 最后，自己认为收获最大的是提高了对linux系统的使用能力，补充了gdb几个不常用，但又很好用的如重定向，监视点，条件断点等知识点，通过自学……，修改了atom的软件设置，安装了中文输fa 入法，学会了git一些基本操作等……
