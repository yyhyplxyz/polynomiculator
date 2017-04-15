#include"Untitled1.h"
using namespace std;
int flag;
/*
* coeff_ == 0  <=> abs(coeff_ - 0) < Ep
*/

Monomial::Monomial(const double coefficient_, const double power_)
{
	setCoefficient(coefficient_);
	setPower(power_);
}

/*
* 单项式可以通过一个括号形式输入的std::string初始化
*/
Monomial::Monomial(const std::string& monoString)
{
	monoString >> *this;
}

Monomial::Monomial(const Monomial& oldMono)
{
	setCoefficient(oldMono.getCoefficient());
	setPower(oldMono.getPower());
}

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

Monomial Monomial::operator-() const
{
	Monomial temp(-getCoefficient(), getPower());
	return temp;
}

double Monomial::operator()(double x) const
{
	double coeff_ = getCoefficient();
	if (abs(coeff_ - 0) < Ep)
		return 0;
	double power_ = getPower();
	return coeff_ * pow(x, power_);
}

Monomial Monomial::operator!() const
{
	Monomial temp(
		getCoefficient()*getPower(),
		getPower() - 1);
	return temp;
}

Monomial Monomial::operator~() const
{
	Monomial temp(
		getCoefficient() / (getPower() + 1),
		getPower() + 1);
	return temp;
}

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

istream& operator >> (istream& in, Monomial& mono)
{
	string monomialString;
	in >> monomialString;
	monomialString >> mono;
	return in;
}

/*
* istream ---> ifstream
* ifstream 是 istream 的派生类
* ifstream 可以当做 istream 来用
*/
ifstream& operator >> (ifstream& fin, Monomial& mono)
{
	istream& in = fin;
	in >> mono;
	return fin;

}

/*
* 通过std::string 读入单项式
* inString: 读入的串
*     mono: 要读入的单项式
*   return: 布尔值bool
*           读入成功: true
*           读入失败: false
*/
bool operator >> (const string& inString, Monomial& mono)
{
	double coefficient_ = 0, power_ = 0;
	int successInputNumber =
		sscanf(inString.c_str(), "(%lf,%lf)", &coefficient_, &power_);

	/*
	* 若读取失败, 输出失败提示
	*/
	/*if (successInputNumber != 2)
	cout << inString << " is failed to input." << endl;*/

	/*
	* 设置单项式的系数和指数, 默认为0
	*/
	mono.setCoefficient(coefficient_);
	mono.setPower(power_);
	if (successInputNumber == 2)return true;
	return false;
}


/*
* 向输出流以人类友好的形式输出单项式
*/
ostream& operator<<(ostream& out, Monomial& mono)
{
	double coeff_ = mono.getCoefficient();

	/*
	* 若系数为0, 则该单项式为0, 不用输出任何字符
	*/
	if (abs(coeff_ - 0) < Ep)return out;

	double power_ = mono.getPower();

	/*
	* 若系数为负值, 则输出一个负号, 取绝对值
	*/
	if (coeff_ < 0)
	{
		out << " - ";
		coeff_ = -coeff_;
	}

	/*
	* 若系数为1, 则系数本身不必输出
	*/
	if (abs(coeff_ - 1)>Ep)
		out << coeff_;

	/*
	* 若指数为1, 则指数部分不必输出
	*/
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

/*
* 以带括号的储存数据的形式输出到文件流
*/
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
		cerr << "指数不一样 无法操作";
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

/*
*        重载运算符: 通过std::string 读入多项式
* polynomialString: 读入的串
*             poly: 要读入的多项式
*           return: 整型int
*                   表示成功读入进该多项式的单项式个数
*/
int operator >> (string& polynomialString, Polynomial& poly)
{
	/*
	*  函数体内m开头变量代表与单项式monomial相关的
	*/
	int mNumber = 0;

	/*
	* 用mHead和mTail来匹配串中的单项式
	* mHead: 匹配到左括号(
	* mTail: 匹配到右括号(
	*/
	string::iterator mTail = polynomialString.begin();
	string::iterator mHead = mTail;
	while (mTail != polynomialString.end())
	{
		while (mTail != polynomialString.end() && *mTail != '(')
			++mTail;

		/*
		* mString: 匹配到的可以表示一个单项式的串
		*/
		string mString(mHead, mTail);
		if (!mString.empty())
		{
			/*
			* mTemp: 用串生成的临时单项式
			*        若这个单项式不为0, 则读入多项式中
			*/
			Monomial mTemp(mString);
			if (!mTemp.isZero())
			{
				poly.getPolynomial().push_back(mTemp);
				mNumber++;
			}
		}

		/*
		* 保证成功匹配到下一个单项式
		*/
		mHead = mTail;
		if (mHead != polynomialString.end())
			++mTail;
	}
	/*
	* 将输入进来的多项式按指数降序排序
	*/
	poly.sortByPowerDescend();
	return mNumber;
}

/*
*  重载<<运算符: 输出一个多项式到屏幕
*          out: 输出流
*         poly: 要输出的多项式
*       return: ostream& 保证链式调用
*         约定: 多项式由一个空格开始
*               每个符号间都有一个空格
*/
ostream& operator<<(ostream& out, Polynomial& poly)
{
	/*
	* 若多项式为空, 输出警告信息
	*/
	if (poly.getPolynomial().empty())
	{
		out << " [Empty Polynomial!]";
		return out;
	}

	/*
	* 保证第一项的系数是正数情况下, 多项式由空格开始
	*/
	if (poly.getPolynomial()[0].getCoefficient() >= 0)
		out << " ";
	out << poly.getPolynomial()[0];

	/*
	* 遍历每个单项式并输出
	*/
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

Polynomial::Polynomial(string polyString)
{
	polyString >> *this;
}

Polynomial::Polynomial()
{
}

/*
* 将该多项式中的单项式按指数由大到小排序
*/
void Polynomial::sortByPowerDescend()
{
	/*
	* std::sort() 需要 #include <algorithm>
	* 前两个参数是需要排序的范围
	* 第三个参数是一个lambda表达式
	* 这个lambda表达式表示排序靠前的指数要大于排序靠后的
	*/
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

double Polynomial::operator()(double x) const
{
	double sum = 0;
	for (size_t i = 0; i < __polynomial.size(); i++)
	{
		sum += __polynomial[i](x);
	}
	return sum;
}

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

/*
*   重载>>运算符: 通过文件读取到字典中
*           fin: 文件输入流
*    dictionary: 要读入的多项式字典
*        return: 整型int
*                表示成功读入进该字典的键值对个数
*/
int operator >> (ifstream& fin, PolyDictionary& dictionary)
{
	int successInputNumber = 0;
	/*
	* 遍历整个文件直到EOF
	*/
	while (!fin.eof())
	{
		/*
		*        key: 键(关键字)
		* polyString: 用于生成多项式的字符串
		*/
		string key;
		string polyString;
		/*
		* 从':'之前读取到key
		* 同时清除key串中开头多余空白字符
		*/
		getline(fin, key, ':');
		clearSpace(key, ' ');
		clearSpace(key, '\n');
		getline(fin, polyString, ';');
		if (!key.empty() && !polyString.empty())
		{
			/*  键值对:
			*     key: key
			*   value: pTemp
			*/
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

System::System()
	:PolyDictionary()
{
	reload();
}

System::~System()
{
	save();
}

void System::displayHead(const std::string message, bool showPoly, bool showLastLine, int width)
{
	system("cls");
	printLine();
	cout << "\n";
	cout << string(width / 4, ' ') << message << "\n";
	if (showPoly)
	{
		cout << string(width / 4, ' ') << "目前存储的多项式有:" << "\n\n";
		cout << *this << endl;
	}
	if (showLastLine)
		printLine();
}

void System::displayInstruction(int width)
{
	cout << ": ) 详细的输入语法如下: \n\n";
	cout << string(7, ' ') << "push 【多项式名】:【多项式】  ==>  添加多项式\n";
	cout << string(5, ' ') << "remove 【多项式名】  ==>  移除多项式\n";
	cout << string(7, ' ') << "show 【多项式】 + 【多项式】  ==>  多项式加法运算\n";
	cout << string(7, ' ') << "show 【多项式】 - 【多项式】  ==>  多项式减法运算\n";
	cout << string(7, ' ') << "show 【多项式】 * 【多项式】  ==>  多项式乘法运算\n";
	cout << string(7, ' ') << "show !【多项式】  ==>  多项式求导\n";
	cout << string(7, ' ') << "show ~【多项式】  ==>  多项式求不定积分\n";
	cout << string(8, ' ') << "get 【多项式】(【x的取值】)  ==>  求当 x =【x的取值】时, 多项式的值\n";
	cout << string(8, ' ') << "get 【多项式】(【下界】,【上界】)  ==>  求多项式从【下界】积到【上界】的定积分\n";
	cout << "\n";
	cout << string(5, ' ') << "温馨技巧提示: \n";
	cout << string(7, ' ') << "在show命令中, 在表达式前面加入前缀  \"【多项式名】:\"\n" << string(7, ' ') << "即可将该结果以【多项式名】存入系统中\n";
}

void System::displaySimpleInstruction(bool simplist, int width)
{
	cout << "现在可以输入命令如下: \n";
	if (simplist)
	{
		cout << string(5, ' ') << "【push】,【remove】,【show】,【get】" << endl;
		cout << string(5, ' ') << "【save】,【clear】,【reload】,【help】,【quit】" << endl;
	}
	else
	{
		cout << string(7, ' ') << "【 push 】添加多项式" << string(9, ' ') << "【remove】移除多项式\n" << string(7, ' ') << "【 show 】多项式运算" << string(9, ' ') << "【  get 】多项式求值与积分运算\n" << string(7, ' ') << "【 help 】查看详细帮助" << string(7, ' ') << "【 save 】快速保存\n" << string(7, ' ') << "【 clear】清除所有数据" << string(7, ' ') << "【reload】重新加载数据\n" << string(7, ' ') << "【 quit 】保存并退出" << endl;
	}
}

bool System::inputOrder(const std::string& order, std::string& instruction, std::string& content) const
{
	istringstream orderFlow(order);
	getline(orderFlow, instruction, ' ');
	getline(orderFlow, content, '\n');
	if (flag)
	{
		flag = 0;
		return true;
	}
	if (!instruction.empty() && content.empty())return true;
	if (instruction.empty() || content.empty())
	{
		cerr << "命令或者内容为空" << endl;
		return false;
	}
	return true;
}

bool System::inputContent(const std::string& content, string& key, Polynomial& poly, const char sign, bool keyNeeded)
{
	istringstream contentFlow(content);
	if (keyNeeded)
	{
		getline(contentFlow, key, ':');
		string polyString;
		getline(contentFlow, polyString, '\n');
		if (polyString.empty())
		{
			cerr << "多项式内容为空, 请重新输入" << endl;
			return false;
		}
		poly = Polynomial(polyString);
		return true;
	}
	else
	{
		/*
		* 读取key, 若没有key, 则为空
		*/
		bool keyFound = content.find(':') != content.npos;
		if (keyFound)
			getline(contentFlow, key, ':');
		/*
		* 获取运算表达式
		*/
		string expression;
		getline(contentFlow, expression, '\n');
		string::iterator i = expression.begin();
		while (*i == sign)++i;
		string polyStringOrKey(i, expression.end());
		if (stringToPolynomial(polyStringOrKey, poly))return true;
		return false;
	}
}

bool System::inputContent(const std::string& order, std::string& key) const
{
	istringstream orderFlow(order);
	getline(orderFlow, key, '\n');
	if (key.empty())
	{
		cerr << "key内容为空, 请重新输入" << endl;
		return false;
	}
	return true;
}

bool System::inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign)
{
	istringstream contentFlow(content);
	/*
	* 读取key, 若没有key, 则为空
	*/
	bool keyFound = content.find(':') != content.npos;
	if (keyFound)
		getline(contentFlow, key, ':');
	/*
	* 读入二元运算对象的构造字符串
	*/
	string lhsStr, rhsStr;
	getline(contentFlow, lhsStr, sign);
	getline(contentFlow, rhsStr, '\n');
	if (lhsStr.empty() || rhsStr.empty())
	{
		cerr << "其中一项多项式为空, 请重新输入" << endl;
		return false;
	}
	bool successLhs = stringToPolynomial(lhsStr, lhs);
	bool successRhs = stringToPolynomial(rhsStr, rhs);
	if (successLhs&&successRhs)return true;
	return false;
}

/*
* switche(...): 这是一个重要的跳转函数, 在main中被调用
*            功能: 根据命令instruction, 跳转到不同的模块
*    instruction: 接受到的指令
*                  单指令: help, clear, reload, save
*                 一定要接着内容的指令: push, remove, show, get
*        content: 接受到的内容, 对于单指令来说, 内容是无所谓的, 因为用不到
*/
void System::switcher(const std::string& instruction, const std::string& content)
{
	/* =====================================
	*      单命令(就是只有一个单词的命令)部分
	*  =====================================*/
	/*
	* 如果指令是help(帮助)
	* 调用显示详细的命令语法函数displayInstruction()
	*/
	if (flag)
		return;
	if (instruction == "help")
	{
		displayHead("");
		displayInstruction();
		return;
	}

	/*
	* 如果指令是reload(重新加载)
	*/
	if (instruction == "reload")
	{
		reload();
		displayHead("");
		cout << "重新加载完成" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/*
	* 如果指令是save(保存)
	*/
	if (instruction == "save")
	{
		save();
		cout << "成功保存" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/*
	* 如果指令是clear(清除数据)
	*/
	if (instruction == "clear")
	{
		clear();
		displayHead("成功清除了所有数据");
		cout << "想补救? 试试输入【reload】" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/* =====================================
	*             命令 + 内容形式
	*  =====================================*/
	/*
	*       key: 保存处理后的多项式的名字
	*    result: 保存处理后的多项式
	*/
	string key;
	Polynomial result;

	/*
	* push: 添加多项式指令
	*/
	if (instruction == "push")
	{
		push(content, key, result);
		return;
	}

	/*
	* remove: 移除多项式指令
	*/
	if (instruction == "remove")
	{
		remove(content, key);
		return;
	}

	/*
	* show: 展现运算指令
	*/
	if (instruction == "show")
	{
		/*
		* 其中根据operationJudge(content)指内容判断是二元运算还是一元运算
		*/
		show(operationJudge(content), content, key, result);
		return;
	}

	/*
	* get: 求值, 求定积分指令
	*/
	if (instruction == "get")
	{
		get(content, key);
		return;
	}

	/*
	* 如果所有指令都不匹配, 则说明输入指令错误
	*/
	if (flag)
		cerr << "指令输入有误, 请重新输入" << endl;
}


/*
* 用可能是key或者是括号形式的字符串转换成多项式
*   polyString: 字符串, 可能是key, 也可能是有括号的多项式字符
*         poly: 用来保存结果的多项式
*       return: 布尔值
*               true: poly成功得到赋值
*              false: poly赋值失败原因为key对应的多项式找不到
*/
bool System::stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly)
{
	/*
	* 判断polyString 是否是一个标识符key
	*/
	bool polyStringIsKey = polyStringOrKey.find('(') == polyStringOrKey.npos;
	if (polyStringIsKey)
	{
		string key = polyStringOrKey;
		clearSpace(key, ' ');
		bool keyIsFound = this->getDictionary().find(key) != this->getDictionary().end();
		/*
		* 若找到key, 则poly赋值为key所对应的多项式
		*/
		if (keyIsFound)
		{
			poly = this->getDictionary().at(key);
			return true;
		}
		cerr << "有一项多项式找不到: " << key << " ,请重新输入指令" << endl;
		return false;
	}
	/*
	* 若polyString是带括号的多项式字符串
	* 则直接赋给poly
	*/
	poly = Polynomial(polyStringOrKey);
	return true;
}

/*
* 判断内容是二元运算还是一元运算
*  true: 二元
* false: 一元
*/
bool System::operationJudge(const std::string& content)
{
	bool findBinarySign = content.find('+') != string::npos
		|| content.find('-') != string::npos
		|| content.find('*') != string::npos;
	if (findBinarySign)return true;
	return false;
}

char System::getOperationSign(const std::string& content)
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
	return '+';
}

void System::save(const std::string& address)
{
	ofstream fout("data.txt");
	if (fout)
		fout << *this;
	else
		cerr << "Fail to appendid new data" << endl;
	fout.close();
}

void System::reload(const std::string& address)
{
	ifstream fin("data.txt");
	if (fin)
		fin >> *this;
	else
		cerr << "Fail to init dictionary!" << endl;
	fin.close();
}

void System::clear()
{
	this->getDictionary().clear();
}

void System::push(const std::string& content, std::string& key, Polynomial& result)
{
	Polynomial poly;
	if (inputContent(content, key, poly) == false)
		return;
	this->getDictionary().emplace(key, poly);
	displayHead("成功添加该多项式");
}

void System::remove(const std::string& content, std::string& key)
{
	if (inputContent(content, key) == false)
		return;
	if (this->getDictionary().erase(key) != 0)
		displayHead("成功移除该多项式");
	else
	{
		cerr << "key值对应的多项式找不到" << endl;
	}
}

void System::show(bool operationType, const std::string& content, std::string& key, Polynomial& result)
{
	if (operationType == true)
	{
		/*
		* 二元运算情况
		*/

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
		/*
		* 一元运算情况
		*/
		Polynomial poly;
		char sign = getOperationSign(content);
		if (inputContent(content, key, poly, sign, false) == false)return;
		switch (sign)
		{
		case '!':result = !poly; break;
		case '~':result = ~poly; break;
		}
	}
	/*
	* 如果有key, 则存入字典中
	*/
	if (!key.empty())
		this->getDictionary().emplace(key, result);
	else {
		cout << "Do you want to save this polynomial?" << endl;
		cout << ">>";
		cin >> key;
		flag = 1;
		if (key != "n" && !key.empty())
			this->getDictionary().emplace(key, result);
		if(key == " ")
		cout << "You can't enter the space!" << endl;
	}
	/*
	* 输出结果
	*/
	displayHead("");
	cout << "得到的结果为:\n" << string(5, ' ') << (key.empty() ? "结果 =" : string(key + "(x) =")) << result << endl;
	displaySimpleInstruction(true);
	cout << endl;
}

void System::get(const std::string& content, std::string& key)
{
	Polynomial poly;
	istringstream contentFlow(content);
	double resultValue;
	string polyString;
	getline(contentFlow, polyString, '(');
	if (stringToPolynomial(polyString, poly) == false)
		return;
	string expression;
	getline(contentFlow, expression, '\n');
	double a = 0.0, b = 0.0;
	bool isValueOperation = false;
	if (sscanf(expression.c_str(), "%lf,%lf)", &a, &b) != 2)
	{
		isValueOperation = true;
		sscanf(expression.c_str(), "%lf)", &a);
	}
	/*
	* 输出结果
	*/
	displayHead("");

	if (isValueOperation)
	{
		resultValue = poly(a);
		if (key.empty())
			cout << "得到的结果为:\n" << string(5, ' ') << polyString << "(" << a << ") = " << resultValue << endl;
		else
			cout << "得到的结果为:\n" << string(5, ' ') << key << "( " << a << " ) = " << resultValue << endl;
	}
	else
	{
		resultValue = poly(a, b);
		cout << "得到的结果为:\n" << string(5, ' ') << "∫" << polyString << "(x)(" << a << "→" << b << ")" << key << " = " << resultValue << endl;
	}
	displaySimpleInstruction(true);
	cout << endl;
}

void System::printLine(char ch, int width)
{
	cout << string(width, ch) << "\n";
}
