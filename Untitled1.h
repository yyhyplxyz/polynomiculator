#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#define Ep 0.000001
extern int flag;
class Monomial
{
	/*
	* Monomial 单项式类
	*/
public:
	explicit Monomial(const double coefficient_ = 0, const double power_ = 0);
	explicit Monomial(const std::string& monoString);
	Monomial(const Monomial& oldMono);
	double getCoefficient() const;
	double getPower() const;
	bool isZero() const;

	void setCoefficient(const double coefficient_);
	void setPower(const double power_);

	/*
	* 重载赋值,调用运算符
	* 调用()运算符用来求值
	*/
	Monomial operator-() const;
	double operator()(double x)const;

	/*
	* 定义求导运算符!
	*/
	Monomial operator!()const;

	/*
	* 定义不定积分运算符~
	*/
	Monomial operator~()const;

	/*
	* 定义定积分运算符(),通过重载()的形式
	*/
	double operator()(const double lowerBound, const double upperBound)const;

	/*
	* 重载读入运算符, 主要通过std::string匹配实现
	*/
	friend bool operator>>(const std::string& inString, Monomial& mono);
	friend std::istream& operator>>(std::istream& in, Monomial& mono);
	friend std::ifstream& operator>>(std::ifstream& fin, Monomial& mono);

	/*
	* 重载输出运算符
	*/
	friend std::ostream& operator<<(std::ostream& out, Monomial& mono);
	friend std::ofstream& operator<<(std::ofstream& fout, Monomial& mono);

	/*
	* 重载算术,关系运算符,关系只是比较指数部分
	*/
	friend Monomial operator+(const Monomial& lhs, const Monomial& rhs);
	friend Monomial operator-(const Monomial& lhs, const Monomial& rhs);
	friend Monomial operator*(const Monomial& lhs, const Monomial& rhs);
	friend Monomial operator/(const Monomial& lhs, const Monomial& rhs);
	friend bool operator==(const Monomial& lhs, const Monomial& rhs);
	friend bool operator!=(const Monomial& lhs, const Monomial& rhs);
	friend bool operator<(const Monomial& lhs, const Monomial& rhs);
	friend bool operator<=(const Monomial& lhs, const Monomial& rhs);
	friend bool operator>(const Monomial& lhs, const Monomial& rhs);
	friend bool operator>=(const Monomial& lhs, const Monomial& rhs);
private:
	double __coefficient;
	double __power;
};
class Polynomial
{
	/*
	* Polynomial 多项式类
	* 多项式类由单项式的可变数组构成
	*/
public:
	explicit Polynomial(std::string polyString);
	explicit Polynomial();
	
	friend int operator>>(std::string& polynomialString, Polynomial& poly);
	std::vector<Monomial>& getPolynomial();

	Polynomial operator-() const;
	double operator()(double x) const;
	/*
	* 定义求导运算符!
	*/
	Polynomial operator!()const;

	/*
	* 定义不定积分运算符~
	*/
	Polynomial operator~()const;

	/*
	* 定义定积分运算符(),通过重载()的形式
	*/
	double operator()(const double lowerBound, const double upperBound);

	/*
	* 其他重载运算符
	*/

	friend std::istream& operator>>(std::istream& in, Polynomial& poly);

	friend std::ostream& operator<<(std::ostream& out, Polynomial& poly);
	friend std::ofstream& operator<<(std::ofstream& fout, Polynomial& poly);

	friend Polynomial operator+(Polynomial& lhs, Polynomial& rhs);
	friend Polynomial operator-(Polynomial& lhs, Polynomial& rhs);
	friend Polynomial operator*(Monomial& lhs, Polynomial& rhs);
	friend Polynomial operator*(Polynomial& lhs, Polynomial& rhs);

private:
	std::vector<Monomial> __polynomial;
	void sortByPowerDescend();
};
#include <map>
class PolyDictionary
{
	/*
	* Poly Dictionary 多项式字典类
	* 这个类是对键值对集合的封装
	*/
public:
	std::map<std::string, Polynomial>& getDictionary();
	double operator()(const std::string& key, double x) const;
	Polynomial& operator[](const std::string& key);

	/*
	* 运算符重载
	*/
	friend int operator>>(std::ifstream& fin, PolyDictionary& dictionary);

	friend std::ofstream& operator<<(std::ofstream& fout, PolyDictionary& poly);
	friend std::ostream& operator<<(std::ostream& out, PolyDictionary& poly);
	
private:
	std::map<std::string, Polynomial> __dictionary;
};


void clearSpace(std::string& str, char spaceChar);
#include <cstdlib>
#include <sstream>
#define WIDTH 70
class System :public PolyDictionary
{
public:
	/*
	* 构造, 析构函数
	*/
	System();
	~System();

	/* ==============================
	*           输入输出部分
	*  ==============================*/
	/*
	* Output:
	*              displayHead(...): 清屏, 并显示页面头部信息
	*       displayInstruction(...): 显示详细的命令语法
	* displaySimpleInstruction(...): 显示简单的命令语法
	*/
	void displayHead(const std::string message, bool showPoly = true, bool showLastLine = true, int width = WIDTH);
	static void displayInstruction(int width = WIDTH);
	static void displaySimpleInstruction(bool simplist = false, int width = WIDTH);

	/*
	* Input:
	*      inputOrder(...): 从一整行命令语句中读入指令和指令的内容
	*/
	bool inputOrder(const std::string& order, std::string& instruction, std::string& content) const;
	/*
	* 取名为switcher, 意思是这个函数的功能就是跳转到各个模块的函数
	* 跳转函数, 根据instruction的值来处理读入的内容并输出结果
	*/
	void switcher(const std::string& instruction, const std::string& content);



private:
	/*
	* Input:
	*      inputOrder(...): 从一整行命令语句中读入指令和指令的内容
	*    inputContent(...): 根据指令的内容读取相关信息, 有三个重载函数
	*              重载(1): 读取形式 {key}:{Polymial}, key可选
	*              重载(2): 读取形式 {key}
	*              重载(3): 读取形式 {key}:{Polymial}{Sign}{Polymial}, key可选
	*/
	bool inputContent(const std::string& content, std::string& key, Polynomial& poly, const char sign = '!', bool keyNeeded = true);
	bool inputContent(const std::string& content, std::string& key) const;
	bool inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign);

	/*
	* Output 内部使用函数
	*/
	static void printLine(char ch = '=', int width = WIDTH);
	//static void displayPicture(int width = WIDTH);

	/*
	* Input 内部使用函数
	*/
	bool stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly);
	static bool operationJudge(const std::string& content);
	static char getOperationSign(const std::string& content);

	/*
	* 处理用函数
	*/
	void save(const std::string& address = "file/data.txt");
	void reload(const std::string& address = "file/data.txt");
	void clear();
	void push(const std::string& content, std::string& key, Polynomial& result);
	void remove(const std::string& content, std::string& key);
	void show(bool operationType, const std::string& content, std::string& key, Polynomial& result);
	void get(const std::string& content, std::string& key);
};

