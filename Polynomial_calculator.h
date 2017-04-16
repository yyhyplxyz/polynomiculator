#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#define Ep 0.000001
extern int flag;
//单项式的类， 有指数和系数两个部分
class Monomial
{
public:
	explicit Monomial(const double coefficient_ = 0, const double power_ = 0);
	explicit Monomial(const std::string& monoString);
	Monomial(const Monomial& oldMono);
	double getCoefficient() const;
	double getPower() const;
	bool isZero() const;
	void setCoefficient(const double coefficient_);
	void setPower(const double power_);
	Monomial operator-() const; // 求相反数的操作
	double operator()(double x)const;// 对单项式求值的操作
	Monomial operator!()const;//对单项式求导的操作
	Monomial operator~()const;//对单项式求积分的操作
	double operator()(const double lowerBound, const double upperBound)const; //对单项式求定积分的操作
	friend bool operator>>(const std::string& inString, Monomial& mono);// 将字符串转化为单项式
	friend std::istream& operator>>(std::istream& in, Monomial& mono);
	friend std::ifstream& operator>>(std::ifstream& fin, Monomial& mono);//文件读取操作
	friend std::ostream& operator<<(std::ostream& out, Monomial& mono);
	friend std::ofstream& operator<<(std::ofstream& fout, Monomial& mono);//文件读取操作
	friend Monomial operator+(const Monomial& lhs, const Monomial& rhs);//加法操作
	friend Monomial operator-(const Monomial& lhs, const Monomial& rhs);//减法操作
	friend Monomial operator*(const Monomial& lhs, const Monomial& rhs);//乘法操作
	friend Monomial operator/(const Monomial& lhs, const Monomial& rhs);//除法操作
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
//用向量存单项式的多项式的类, 各类运算操作同上
class Polynomial
{

public:
	explicit Polynomial(std::string polyString);
	explicit Polynomial();
	friend int operator>>(std::string& polynomialString, Polynomial& poly);
	std::vector<Monomial>& getPolynomial();
	Polynomial operator-() const;
	double operator()(double x) const;
	Polynomial operator!()const;
	Polynomial operator~()const;
double operator()(const double lowerBound, const double upperBound);
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
//用map来存多项式与他们的名字
class PolyDictionary
{
public:
	std::map<std::string, Polynomial>& getDictionary();
	double operator()(const std::string& key, double x) const;
	Polynomial& operator[](const std::string& key);
	friend int operator>>(std::ifstream& fin, PolyDictionary& dictionary);
	friend std::ofstream& operator<<(std::ofstream& fout, PolyDictionary& poly);
	friend std::ostream& operator<<(std::ostream& out, PolyDictionary& poly);
private:
	std::map<std::string, Polynomial> __dictionary;
};

//对输入字符串的空格进行清除
void clearSpace(std::string& str, char spaceChar);
#include <cstdlib>
#include <sstream>
#define WIDTH 70
//另一个封装的类用于操作计算器的一些函数
//包括运算，求值，保存，撤销操作，退出，显示帮助等功能
class Calculator :public PolyDictionary
{
public:
	Calculator();
	~Calculator();

void displayHead(const std::string message, bool showPoly = true, bool showLastLine = true, int width = WIDTH);
	static void displayInstruction(int width = WIDTH);
	//static void displaySimpleInstruction(bool simplist = false, int width = WIDTH);

	bool inputOrder(const std::string& order, std::string& instruction, std::string& content) const;
	void switcher(const std::string& instruction, const std::string& content);
private:
	bool inputContent(const std::string& content, std::string& key, Polynomial& poly, const char sign = '!', bool keyNeeded = true);
	bool inputContent(const std::string& content, std::string& key) const;
	bool inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign);
	static void printLine(char ch = '=', int width = WIDTH);
	bool stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly);
	static bool operationJudge(const std::string& content);
	static char getOperationSign(const std::string& content);
	void save(const std::string& address = "file/data.txt");
	void reload(const std::string& address = "file/data.txt");
	void clear();
	void push(const std::string& content, std::string& key, Polynomial& result);
	void remove(const std::string& content, std::string& key);
	void show(bool operationType, const std::string& content, std::string& key, Polynomial& result);
	void get(const std::string& content, std::string& key);
};
