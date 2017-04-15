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
	* Monomial ����ʽ��
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
	* ���ظ�ֵ,���������
	* ����()�����������ֵ
	*/
	Monomial operator-() const;
	double operator()(double x)const;

	/*
	* �����������!
	*/
	Monomial operator!()const;

	/*
	* ���岻�����������~
	*/
	Monomial operator~()const;

	/*
	* ���嶨���������(),ͨ������()����ʽ
	*/
	double operator()(const double lowerBound, const double upperBound)const;

	/*
	* ���ض��������, ��Ҫͨ��std::stringƥ��ʵ��
	*/
	friend bool operator>>(const std::string& inString, Monomial& mono);
	friend std::istream& operator>>(std::istream& in, Monomial& mono);
	friend std::ifstream& operator>>(std::ifstream& fin, Monomial& mono);

	/*
	* ������������
	*/
	friend std::ostream& operator<<(std::ostream& out, Monomial& mono);
	friend std::ofstream& operator<<(std::ofstream& fout, Monomial& mono);

	/*
	* ��������,��ϵ�����,��ϵֻ�ǱȽ�ָ������
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
	* Polynomial ����ʽ��
	* ����ʽ���ɵ���ʽ�Ŀɱ����鹹��
	*/
public:
	explicit Polynomial(std::string polyString);
	explicit Polynomial();
	
	friend int operator>>(std::string& polynomialString, Polynomial& poly);
	std::vector<Monomial>& getPolynomial();

	Polynomial operator-() const;
	double operator()(double x) const;
	/*
	* �����������!
	*/
	Polynomial operator!()const;

	/*
	* ���岻�����������~
	*/
	Polynomial operator~()const;

	/*
	* ���嶨���������(),ͨ������()����ʽ
	*/
	double operator()(const double lowerBound, const double upperBound);

	/*
	* �������������
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
	* Poly Dictionary ����ʽ�ֵ���
	* ������ǶԼ�ֵ�Լ��ϵķ�װ
	*/
public:
	std::map<std::string, Polynomial>& getDictionary();
	double operator()(const std::string& key, double x) const;
	Polynomial& operator[](const std::string& key);

	/*
	* ���������
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
	* ����, ��������
	*/
	System();
	~System();

	/* ==============================
	*           �����������
	*  ==============================*/
	/*
	* Output:
	*              displayHead(...): ����, ����ʾҳ��ͷ����Ϣ
	*       displayInstruction(...): ��ʾ��ϸ�������﷨
	* displaySimpleInstruction(...): ��ʾ�򵥵������﷨
	*/
	void displayHead(const std::string message, bool showPoly = true, bool showLastLine = true, int width = WIDTH);
	static void displayInstruction(int width = WIDTH);
	static void displaySimpleInstruction(bool simplist = false, int width = WIDTH);

	/*
	* Input:
	*      inputOrder(...): ��һ������������ж���ָ���ָ�������
	*/
	bool inputOrder(const std::string& order, std::string& instruction, std::string& content) const;
	/*
	* ȡ��Ϊswitcher, ��˼����������Ĺ��ܾ�����ת������ģ��ĺ���
	* ��ת����, ����instruction��ֵ�������������ݲ�������
	*/
	void switcher(const std::string& instruction, const std::string& content);



private:
	/*
	* Input:
	*      inputOrder(...): ��һ������������ж���ָ���ָ�������
	*    inputContent(...): ����ָ������ݶ�ȡ�����Ϣ, ���������غ���
	*              ����(1): ��ȡ��ʽ {key}:{Polymial}, key��ѡ
	*              ����(2): ��ȡ��ʽ {key}
	*              ����(3): ��ȡ��ʽ {key}:{Polymial}{Sign}{Polymial}, key��ѡ
	*/
	bool inputContent(const std::string& content, std::string& key, Polynomial& poly, const char sign = '!', bool keyNeeded = true);
	bool inputContent(const std::string& content, std::string& key) const;
	bool inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign);

	/*
	* Output �ڲ�ʹ�ú���
	*/
	static void printLine(char ch = '=', int width = WIDTH);
	//static void displayPicture(int width = WIDTH);

	/*
	* Input �ڲ�ʹ�ú���
	*/
	bool stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly);
	static bool operationJudge(const std::string& content);
	static char getOperationSign(const std::string& content);

	/*
	* �����ú���
	*/
	void save(const std::string& address = "file/data.txt");
	void reload(const std::string& address = "file/data.txt");
	void clear();
	void push(const std::string& content, std::string& key, Polynomial& result);
	void remove(const std::string& content, std::string& key);
	void show(bool operationType, const std::string& content, std::string& key, Polynomial& result);
	void get(const std::string& content, std::string& key);
};

