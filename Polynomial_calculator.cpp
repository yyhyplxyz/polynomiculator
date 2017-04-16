#include"Polynomial_calculator.h"
#include<stdio.h>
using namespace std;
int flag;
// 单项式的类的多个构造函数
Monomial::Monomial(const double coefficient_, const double power_)
{
	setCoefficient(coefficient_);
	setPower(power_);
}
Monomial::Monomial(const std::string& monoString)
{
	monoString >> *this;
}
Monomial::Monomial(const Monomial& oldMono)
{
	setCoefficient(oldMono.getCoefficient());
	setPower(oldMono.getPower());
}
//对私有数据的相关操作
inline double Monomial::getCoefficient() const
{
	return __coefficient;
}
inline double Monomial::getPower() const
{
	return __power;
}
inline void Monomial::setCoefficient(const double coefficient_)
{
	__coefficient = coefficient_;
}
inline void Monomial::setPower(const double power_)
{
	__power = power_;
}
//用 inline可以提高速度
Monomial Monomial::operator-() const
{
	Monomial temp(-getCoefficient(), getPower());
	return temp;
}
//重载运算符， 进行求值操作
double Monomial::operator()(double x) const
{
	double coeff_ = getCoefficient();
	if (abs(coeff_ - 0) < Ep)
		return 0;
	double power_ = getPower();
	return coeff_ * pow(x, power_);
}
//求导操作
Monomial Monomial::operator!() const
{
	Monomial temp(
		getCoefficient()*getPower(),
		getPower() - 1);
	return temp;
}
//求不定积分
Monomial Monomial::operator~() const
{
	Monomial temp(
		getCoefficient() / (getPower() + 1),
		getPower() + 1);
	return temp;
}
//求定积分
double Monomial::operator()(const double lowerBound, const double upperBound) const
{
	double fUpper = (~*this)(upperBound);
	double fLower = (~*this)(lowerBound);
	return fUpper - fLower;
}

bool Monomial::isZero() const
{
	if (getCoefficient() == 0)return true;
	return false;
}
//为了以后用getline函数，需要得到istream
istream& operator >> (istream& in, Monomial& mono)
{
	string monomialString;
	in >> monomialString;
	monomialString >> mono;
	return in;
}
// ifstream 是 istream 的派生类
ifstream& operator >> (ifstream& fin, Monomial& mono)
{
	istream& in = fin;
	in >> mono;
	return fin;

}
#include<string.h>
bool operator >> (const string& inString, Monomial& mono)
{
	double coefficient_ = 0, power_ = 0;
	char t[] = "1234567890.";
	int successInputNumber =
		sscanf(inString.c_str(), "(%lf,%lf)", &coefficient_, &power_);
		if(strspn(inString.c_str(), t) != (inString.size() -3 ) && strspn(inString.c_str(), "[]") != 0)
		cerr  <<"The format is incorrect, but I can ignore your wrong input" << endl;
		//f(*inString.begin() != '(' || *inString.end() != ')')
		//cerr <<" The format is incorrect, but I can ignore your wrong input" << endl;
		//if(inString.find("..") != string::npos)
		//cerr << "The format is incorrect" << endl;
		//if(inString.find(",,") != string::npos)
		//cerr << "The format is incorrect" << endl;
	mono.setCoefficient(coefficient_);
	mono.setPower(power_);
	if (successInputNumber == 2)return true;
	return false;
}
ostream& operator<<(ostream& out, Monomial& mono)
{
	double coeff_ = mono.getCoefficient();
	if (abs(coeff_ - 0) < Ep)return out;
	double power_ = mono.getPower();
	//定义Ep比较浮点数的相等与否
	if (coeff_ < 0)
	{
		out << " - ";
		coeff_ = -coeff_;
	}
	if (abs(coeff_ - 1)>Ep)
		out << coeff_;
	if (abs(power_ - 0) > Ep)
	{
		if (abs(power_ - 1) < Ep)
		{
			out << "x";
		}
		else
		{
			out << "x^" << power_;
		}
	}
	return out;
}
//以人类友好的方式输出表达式
ofstream& operator<<(ofstream& fout, Monomial& mono)
{
	fout << "(" << mono.getCoefficient() << "," << mono.getPower() << ")";
	return fout;
}

Monomial operator+(const Monomial& lhs, const Monomial& rhs)
{
	Monomial temp(0, lhs.getPower());
	if (abs(lhs.getPower() - rhs.getPower()) > Ep)
	{
		cerr << "The power numbers are different!";
		return temp;
	}
	temp.setCoefficient(lhs.getCoefficient() + rhs.getCoefficient());
	return temp;
}

Monomial operator-(const Monomial& lhs, const Monomial& rhs)
{
	return lhs + (-rhs);
}

Monomial operator*(const Monomial& lhs, const Monomial& rhs)
{
	Monomial temp(
		lhs.getCoefficient()*rhs.getCoefficient(),
		lhs.getPower() + rhs.getPower());
	return temp;
}

Monomial operator/(const Monomial& lhs, const Monomial& rhs)
{
	Monomial temp(
		lhs.getCoefficient() / rhs.getCoefficient(),
		lhs.getPower() - rhs.getPower());
	return temp;
}

bool operator==(const Monomial& lhs, const Monomial& rhs)
{
	if (abs(lhs.getPower() - rhs.getPower()) < Ep)
		return true;
	return false;
}

bool operator!=(const Monomial& lhs, const Monomial& rhs)
{
	return !(lhs == rhs);
}
//对指数进行比较
bool operator<(const Monomial& lhs, const Monomial& rhs)
{
	if (lhs.getPower() < rhs.getPower()
		&& abs(lhs.getPower() - rhs.getPower()) > Ep)
		return true;
	return false;
}

bool operator<=(const Monomial& lhs, const Monomial& rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator>(const Monomial& lhs, const Monomial& rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(const Monomial& lhs, const Monomial& rhs)
{
	return !(lhs < rhs);
}
using namespace std;
istream& operator >> (istream& in, Polynomial& poly)
{
	string polynomialString;
	in >> polynomialString;
	polynomialString >> poly;
	return in;
}
int operator >> (string& polynomialString, Polynomial& poly)
{
	int mNumber = 0;
	string::iterator mTail = polynomialString.begin();
	string::iterator mHead = mTail;
	while (mTail != polynomialString.end())
	{
		while (mTail != polynomialString.end() && *mTail != '(')
			++mTail;
		string mString(mHead, mTail);
		if (!mString.empty())
		{
			Monomial mTemp(mString);
			if (!mTemp.isZero())
			{
				poly.getPolynomial().push_back(mTemp);
				mNumber++;
			}
		}

		mHead = mTail;
		if (mHead != polynomialString.end())
			++mTail;
	}
	poly.sortByPowerDescend();
	return mNumber;
}
ostream& operator<<(ostream& out, Polynomial& poly)
{
	if (poly.getPolynomial().empty())
	{
		out << " [Empty Polynomial!]";
		return out;
	}
	if (poly.getPolynomial()[0].getCoefficient() >= 0)
		out << " ";
	out << poly.getPolynomial()[0];
	for (size_t i = 1; i < poly.getPolynomial().size(); i++)
	{
		if (poly.getPolynomial()[i].getCoefficient() >= 0)
			out << " + ";
		out << poly.getPolynomial()[i];
	}
	return out;
}

ofstream& operator<<(ofstream& fout, Polynomial& poly)
{
	for (size_t i = 0; i < poly.getPolynomial().size(); i++)
	{
		fout << poly.getPolynomial()[i];
	}
	return fout;
}
//多项式类的几个构造函数
Polynomial::Polynomial(string polyString)
{
	polyString >> *this;
}

Polynomial::Polynomial()
{
}

void Polynomial::sortByPowerDescend()
{
	std::sort(__polynomial.begin(), __polynomial.end(), [](const Monomial& lhs, const Monomial& rhs)
	{
		return lhs.getPower() > rhs.getPower();
	});
}

inline vector<Monomial>& Polynomial::getPolynomial()
{
	return __polynomial;
}

Polynomial Polynomial::operator-() const
{
	Polynomial temp = *this;
	for (vector<Monomial>::iterator i = temp.getPolynomial().begin();
		i != temp.getPolynomial().end(); ++i)
	{
		*i = -*i;
	}
	return temp;
}
//求值
double Polynomial::operator()(double x) const
{
	double sum = 0;
	for (size_t i = 0; i < __polynomial.size(); i++)
	{
		sum += __polynomial[i](x);
	}
	return sum;
}
//求导
Polynomial Polynomial::operator!() const
{
	Polynomial temp = *this;
	for (vector<Monomial>::iterator i = temp.getPolynomial().begin();
		i != temp.getPolynomial().end(); ++i)
	{
		*i = !*i;
	}
	return temp;
}
//求不定积分
Polynomial Polynomial::operator~() const
{
	Polynomial temp = *this;
	for (vector<Monomial>::iterator i = temp.getPolynomial().begin();
		i != temp.getPolynomial().end(); ++i)
	{
		*i = ~*i;
	}
	return temp;
}
//求定积分
double Polynomial::operator()(const double lowerBound, const double upperBound)
{
	double resultSum = 0;
	for (vector<Monomial>::iterator i = __polynomial.begin();
		i != __polynomial.end(); ++i)
	{
		resultSum += (*i)(lowerBound, upperBound);
	}
	return resultSum;
}
Polynomial operator+(Polynomial& lhs, Polynomial& rhs)
{
	Polynomial temp;
	vector<Monomial>::iterator lhsPoint = lhs.getPolynomial().begin();
	vector<Monomial>::iterator rhsPoint = rhs.getPolynomial().begin();
	while (lhsPoint != lhs.getPolynomial().end()
		&& rhsPoint != rhs.getPolynomial().end())
	{
		if (*lhsPoint == *rhsPoint)
		{
			Monomial result = *lhsPoint + *rhsPoint;
			if (abs(result.getCoefficient()) > Ep)
				temp.getPolynomial().push_back(result);
			++lhsPoint;
			++rhsPoint;
		}
		else
		{
			if (*lhsPoint > *rhsPoint)
			{
				temp.getPolynomial().push_back(*lhsPoint);
				++lhsPoint;
			}
			else
			{
				temp.getPolynomial().push_back(*rhsPoint);
				++rhsPoint;
			}
		}
	}
	while (lhsPoint != lhs.getPolynomial().end())
	{
		temp.getPolynomial().push_back(*lhsPoint);
		++lhsPoint;
	}
	while (rhsPoint != rhs.getPolynomial().end())
	{
		temp.getPolynomial().push_back(*rhsPoint);
		++rhsPoint;
	}
	return temp;
}

Polynomial operator-(Polynomial& lhs, Polynomial& rhs)
{
	Polynomial reverseRhs = -rhs;
	return lhs + reverseRhs;
}

Polynomial operator*(Monomial& lhs, Polynomial& rhs)
{
	Polynomial temp = rhs;
	for (vector<Monomial>::iterator i = temp.getPolynomial().begin();
		i != temp.getPolynomial().end(); ++i)
	{
		*i = lhs * (*i);
	}
	return temp;
}

Polynomial operator*(Polynomial& lhs, Polynomial& rhs)
{
	Polynomial resultPoly;
	Polynomial lhsTemp = lhs;
	for (vector<Monomial>::iterator lhsItemPoint = lhsTemp.getPolynomial().begin();
		lhsItemPoint != lhsTemp.getPolynomial().end(); ++lhsItemPoint)
	{
		Polynomial monoMultiPoly = (*lhsItemPoint) * rhs;
		resultPoly = resultPoly + monoMultiPoly;
	}
	return resultPoly;
}
using namespace std;

void clearSpace(std::string& str, char spaceChar)
{
	size_t spaceBegin = str.npos;
	size_t spaceEnd = str.npos;
	spaceBegin = str.find_first_of(spaceChar);
	spaceEnd = str.find_first_not_of(spaceChar);
	if (spaceBegin != str.npos&&spaceEnd != str.npos)
		str.replace(spaceBegin, spaceEnd, "");
	spaceBegin = str.find_first_of(spaceChar);
	spaceEnd = str.find_last_of(spaceChar);
	if (spaceBegin != str.npos&&spaceEnd != str.npos)
		str.replace(spaceBegin, spaceEnd, "");
}
//将输入的字符串转化为多项式
int operator >> (ifstream& fin, PolyDictionary& dictionary)
{
	int successInputNumber = 0;
	while (!fin.eof())
	{
		string key;
		string polyString;
		getline(fin, key, ':');
		clearSpace(key, ' ');
		clearSpace(key, '\n');
		getline(fin, polyString, ';');
		if (!key.empty() && !polyString.empty())
		{
			Polynomial pTemp(polyString);
			dictionary.getDictionary().emplace(key, pTemp);
			successInputNumber++;
		}
	}
	return successInputNumber;
}
ostream& operator<<(ostream& out, PolyDictionary& poly)
{
	for (map<string, Polynomial>::iterator i = poly.getDictionary().begin();
		i != poly.getDictionary().end(); ++i)
	{
		out << i->first << "(x) =" << i->second << endl;
	}
	return out;
}
ofstream& operator<<(ofstream& fout, PolyDictionary& poly)
{
	for (map<string, Polynomial>::iterator i = poly.getDictionary().begin();
		i != poly.getDictionary().end(); ++i)
	{
		fout << i->first << ':';
		fout << i->second << ";\n";
	}
	fout << endl;
	return fout;
}
inline map<string, Polynomial>& PolyDictionary::getDictionary()
{
	return __dictionary;
}
double PolyDictionary::operator()(const string& key, double x) const
{
	return __dictionary.at(key)(x);
}

Polynomial& PolyDictionary::operator[](const std::string& key)
{
	return __dictionary.at(key);
}
using namespace std;

Calculator::Calculator()
	:PolyDictionary()
{
	reload();
}

Calculator::~Calculator()
{
	save();
}
//展示现在以命名的多项式
void Calculator::displayHead(const std::string message, bool showPoly, bool showLastLine, int width)
{
//	Calculator("cls");
	printLine();
	cout << "\n";
	cout << string(width / 4, ' ') << message << "\n";
	if (showPoly)
	{
		cout << string(width / 4, ' ') << "Now we have polynomial:" << "\n\n";
		cout << *this << endl;
	}
	if (showLastLine)
		printLine();
}
//展示指令
void Calculator::displayInstruction(int width)
{
	cout << ": ) The following are the user manual: \n\n";
		cout << string(5, ' ') << "\"1\" a polynomial  +(-,*!~)  another polynomial , implies you can do the corresponding calculation\n";
	//cout << string(5,' ') << "You can also use this format to directly name the result \"the name: te expression" << endl;
	cout << string(5, ' ') << "\"2\" a polynomial [the value of x] , implies you can get  the polynomial value?\n";
	cout << string(5, ' ') << "\"2\"  a polynomial[the lowerbound, the upperbound] implies you can intergral the polynomial. \n";
	cout << string(5, ' ') << "\"3 \"\"name of a polynomial expression\" , implies the current Calculator will delete this polynomial?\n";
	cout << string(5, ' ') << "\"4 \"you can save the polynomial stored in current Calculator into the file\n";
	cout << string(5, ' ') << "\"5 \"you can reload the polynomial saved in the file and thus your current polynomial may be lost\n";
	cout << string(5, ' ') << "\"6 \" you can see the user manual\n";
	cout << string(5, ' ') << "\"7 \"you can exit the program\n";
	cout << string(5,' ') << "After any instruction, you must enter a space" << endl;
	cout << endl;
}
//对输入的命令进行预处理
bool Calculator::inputOrder(const std::string& order, std::string& instruction, std::string& content) const
{
	istringstream orderFlow(order);
	getline(orderFlow, instruction, ' ');
	getline(orderFlow, content, '\n');
	if (flag)
	{
		//flag = 0;
		return true;
	}
	if (!instruction.empty() && content.empty())return true;
	if (instruction.empty() || content.empty())
	{
		cerr << "You've entered some empty content" << endl;
		return false;
	}
	return true;
}

bool Calculator::inputContent(const std::string& content, string& key, Polynomial& poly, const char sign, bool keyNeeded)
{
	istringstream contentFlow(content);
	if (keyNeeded)
	{
		getline(contentFlow, key, ':');
		string polyString;
		getline(contentFlow, polyString, '\n');
		if (polyString.empty())
		{
			cerr << "The content is empty, please enter again" << endl;
			return false;
		}
		poly = Polynomial(polyString);
		return true;
	}
	else
	{
		bool keyFound = content.find(':') != content.npos;
		if (keyFound)
			getline(contentFlow, key, ':');
		string expression;
		getline(contentFlow, expression, '\n');
		string::iterator i = expression.begin();
		while (*i == sign)++i;
		string polyStringOrKey(i, expression.end());
		if (stringToPolynomial(polyStringOrKey, poly))return true;
		return false;
	}
}

bool Calculator::inputContent(const std::string& order, std::string& key) const
{
	istringstream orderFlow(order);
	getline(orderFlow, key, '\n');
	if (key.empty())
	{
		cerr << "The content is empty, please enter again" << endl;
		return false;
	}
	return true;
}

bool Calculator::inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign)
{
	istringstream contentFlow(content);
	bool keyFound = content.find(':') != content.npos;
	if (keyFound)
		getline(contentFlow, key, ':');
	string lhsStr, rhsStr;
	getline(contentFlow, lhsStr, sign);
	getline(contentFlow, rhsStr, '\n');
	if (lhsStr.empty() || rhsStr.empty())
	{
		cerr << "The content is empty, please enter again" << endl;
		return false;
	}
	bool successLhs = stringToPolynomial(lhsStr, lhs);
	bool successRhs = stringToPolynomial(rhsStr, rhs);
	if (successLhs&&successRhs)return true;
	return false;
}
//根据不同指令转到不同函数
void Calculator::switcher(const std::string& instruction, const std::string& content)
{
	if (flag)
	{
		flag = 0;
		return;
	}
		string key;
		Polynomial result;

	if (instruction == "6")
	{
		//displayHead("");
		displayInstruction();
		return;
	}
	else if (instruction == "5")
	{
		clear();
		reload();
		displayHead("");
		cout << "reload successfull" << endl;
		cout << endl;
		return;
	}
	else if (instruction == "4")
		{
		save();
		cout << "Save successfully" << endl;
//		displaySimpleInstruction(true);
		cout << endl;
		return;
	}
	/*if (instruction == "clear")
	{
		clear();
		displayHead("?????????????????");
		cout << "????? ????????reload??" << endl;
			cout << endl;
		return;
	}*/

	/*if (instruction == "push")
	{
		push(content, key, result);
		return;
	}*/

	else if (instruction == "3")
	{
		remove(content, key);
		return;
	}

	else if (instruction == "1")
	{
		show(operationJudge(content), content, key, result);
		return;
	}
	else if (instruction == "2")
	{
		get(content, key);
		return;
	}
	if(instruction != "1" && instruction != "2" && instruction != "3" && instruction != "4" && instruction != "5" && instruction != "6" && instruction != "7")
		cerr << "The instruction is incorrect, please enter again" << endl;
}
bool Calculator::stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly)
{
	bool polyStringIsKey = polyStringOrKey.find('(') == polyStringOrKey.npos;
	if (polyStringIsKey)
	{
		string key = polyStringOrKey;
		clearSpace(key, ' ');
		bool keyIsFound = this->getDictionary().find(key) != this->getDictionary().end();
		if (keyIsFound)
		{
			poly = this->getDictionary().at(key);
			return true;
		}
		cerr << "Can't find a polynomial "<< " .Please enter again" << endl;
		return false;
	}
	poly = Polynomial(polyStringOrKey);
	return true;
}
bool Calculator::operationJudge(const std::string& content)
{
	bool findBinarySign = content.find('+') != string::npos
		|| content.find('-') != string::npos
		|| content.find('*') != string::npos;
	if (findBinarySign)return true;
	return false;
}
char Calculator::getOperationSign(const std::string& content)
{
	if (content.find('+') != string::npos)
		return '+';
	if (content.find('-') != string::npos)
		return '-';
	if (content.find('*') != string::npos)
		return '*';
	if (content.find('!') != string::npos)
		return '!';
	if (content.find('~') != string::npos)
		return '~';
	return '?';
}
//将数据存到文件中去
void Calculator::save(const std::string& address)
{
	ofstream fout("data.txt");
	if (fout)
		fout << *this;
	else
		cerr << "Fail to append new data" << endl;
	fout.close();
}
//重新加载文件中数据
void Calculator::reload(const std::string& address)
{
	ifstream fin("data.txt");
	if (fin)
		fin >> *this;
	else
		cerr << "Fail to init dictionary!" << endl;
	fin.close();
}
void Calculator::clear()
{
	this->getDictionary().clear();
}

/*void Calculator::push(const std::string& content, std::string& key, Polynomial& result)
{
	Polynomial poly;
	if (inputContent(content, key, poly) == false)
		return;
	this->getDictionary().emplace(key, poly);
	displayHead("????????????");
}*/

void Calculator::remove(const std::string& content, std::string& key)
{
	if (inputContent(content, key) == false)
		return;
	if (this->getDictionary().erase(key) != 0)
		displayHead("successfully remove it");
	else
	{
		cerr << "can't find a Polynomial" << endl;
	}
}

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
void Calculator::get(const std::string& content, std::string& key)
{
	Polynomial poly;
	istringstream contentFlow(content);
	double resultValue;
	int t = content.find_last_of('[');
	if(t == string::npos)
	cout << "The format is incorrect!" << endl;
	int s = t;
	string polyString (content, 0, s) ;
	//getline(contentFlow, polyString, '(');
	if (stringToPolynomial(polyString, poly) == false)
		return;
	string expression(content, s, content.length());
	//getline(contentFlow, expression, '\n');
	double a = 0.0, b = 0.0;
	bool isValueOperation = false;
	int g = expression.find_last_of(']');
	if(g != expression.length() - 1)
	cout << "The format is incorrect" << endl;
	t = expression.find_first_of('[');
	int flag = 0;
	if(expression.find(',') == string::npos)
	{
		string yyh(expression, t + 1, g - t - 1);
		a = stod(yyh);
		flag = 1;
	}
	else
	{
		int h = expression.find(',');
		string yyha(expression, t +1, h - t - 1);
		string yyhb(expression, h + 1, g - h -1);
		a = stod(yyha);
		b = stod(yyhb);
	}
/*	if (sscanf(expression.c_str(), "%lf,%lf", &a, &b) != 2)
	{
		isValueOperation = true;
		sscanf(expression.c_str(), "%lf", &a);
	}*/
	//displayHead("");
	if (flag)
	{
		resultValue = poly(a);
		if (key.empty())
			cout << "The result:\n" << string(5, ' ') << resultValue << endl;
		else
			cout << "The result:\n" << string(5, ' ')<< resultValue << endl;
	}
	else
	{
		resultValue = poly(a, b);
		cout << "The result:\n" << resultValue << endl;
	}

	cout << endl;
}
void Calculator::printLine(char ch, int width)
{
	cout << string(width, ch) << "\n";
}
