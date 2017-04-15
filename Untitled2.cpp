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
* ����ʽ����ͨ��һ��������ʽ�����std::string��ʼ��
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
* ifstream �� istream ��������
* ifstream ���Ե��� istream ����
*/
ifstream& operator >> (ifstream& fin, Monomial& mono)
{
	istream& in = fin;
	in >> mono;
	return fin;

}

/*
* ͨ��std::string ���뵥��ʽ
* inString: ����Ĵ�
*     mono: Ҫ����ĵ���ʽ
*   return: ����ֵbool
*           ����ɹ�: true
*           ����ʧ��: false
*/
bool operator >> (const string& inString, Monomial& mono)
{
	double coefficient_ = 0, power_ = 0;
	int successInputNumber =
		sscanf(inString.c_str(), "(%lf,%lf)", &coefficient_, &power_);

	/*
	* ����ȡʧ��, ���ʧ����ʾ
	*/
	/*if (successInputNumber != 2)
	cout << inString << " is failed to input." << endl;*/

	/*
	* ���õ���ʽ��ϵ����ָ��, Ĭ��Ϊ0
	*/
	mono.setCoefficient(coefficient_);
	mono.setPower(power_);
	if (successInputNumber == 2)return true;
	return false;
}


/*
* ��������������Ѻõ���ʽ�������ʽ
*/
ostream& operator<<(ostream& out, Monomial& mono)
{
	double coeff_ = mono.getCoefficient();

	/*
	* ��ϵ��Ϊ0, ��õ���ʽΪ0, ��������κ��ַ�
	*/
	if (abs(coeff_ - 0) < Ep)return out;

	double power_ = mono.getPower();

	/*
	* ��ϵ��Ϊ��ֵ, �����һ������, ȡ����ֵ
	*/
	if (coeff_ < 0)
	{
		out << " - ";
		coeff_ = -coeff_;
	}

	/*
	* ��ϵ��Ϊ1, ��ϵ�����������
	*/
	if (abs(coeff_ - 1)>Ep)
		out << coeff_;

	/*
	* ��ָ��Ϊ1, ��ָ�����ֲ������
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
* �Դ����ŵĴ������ݵ���ʽ������ļ���
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
		cerr << "ָ����һ�� �޷�����";
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
*        ���������: ͨ��std::string �������ʽ
* polynomialString: ����Ĵ�
*             poly: Ҫ����Ķ���ʽ
*           return: ����int
*                   ��ʾ�ɹ�������ö���ʽ�ĵ���ʽ����
*/
int operator >> (string& polynomialString, Polynomial& poly)
{
	/*
	*  ��������m��ͷ���������뵥��ʽmonomial��ص�
	*/
	int mNumber = 0;

	/*
	* ��mHead��mTail��ƥ�䴮�еĵ���ʽ
	* mHead: ƥ�䵽������(
	* mTail: ƥ�䵽������(
	*/
	string::iterator mTail = polynomialString.begin();
	string::iterator mHead = mTail;
	while (mTail != polynomialString.end())
	{
		while (mTail != polynomialString.end() && *mTail != '(')
			++mTail;

		/*
		* mString: ƥ�䵽�Ŀ��Ա�ʾһ������ʽ�Ĵ�
		*/
		string mString(mHead, mTail);
		if (!mString.empty())
		{
			/*
			* mTemp: �ô����ɵ���ʱ����ʽ
			*        ���������ʽ��Ϊ0, ��������ʽ��
			*/
			Monomial mTemp(mString);
			if (!mTemp.isZero())
			{
				poly.getPolynomial().push_back(mTemp);
				mNumber++;
			}
		}

		/*
		* ��֤�ɹ�ƥ�䵽��һ������ʽ
		*/
		mHead = mTail;
		if (mHead != polynomialString.end())
			++mTail;
	}
	/*
	* ����������Ķ���ʽ��ָ����������
	*/
	poly.sortByPowerDescend();
	return mNumber;
}

/*
*  ����<<�����: ���һ������ʽ����Ļ
*          out: �����
*         poly: Ҫ����Ķ���ʽ
*       return: ostream& ��֤��ʽ����
*         Լ��: ����ʽ��һ���ո�ʼ
*               ÿ�����ż䶼��һ���ո�
*/
ostream& operator<<(ostream& out, Polynomial& poly)
{
	/*
	* ������ʽΪ��, ���������Ϣ
	*/
	if (poly.getPolynomial().empty())
	{
		out << " [Empty Polynomial!]";
		return out;
	}

	/*
	* ��֤��һ���ϵ�������������, ����ʽ�ɿո�ʼ
	*/
	if (poly.getPolynomial()[0].getCoefficient() >= 0)
		out << " ";
	out << poly.getPolynomial()[0];

	/*
	* ����ÿ������ʽ�����
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
* ���ö���ʽ�еĵ���ʽ��ָ���ɴ�С����
*/
void Polynomial::sortByPowerDescend()
{
	/*
	* std::sort() ��Ҫ #include <algorithm>
	* ǰ������������Ҫ����ķ�Χ
	* ������������һ��lambda���ʽ
	* ���lambda���ʽ��ʾ����ǰ��ָ��Ҫ�������򿿺��
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
*   ����>>�����: ͨ���ļ���ȡ���ֵ���
*           fin: �ļ�������
*    dictionary: Ҫ����Ķ���ʽ�ֵ�
*        return: ����int
*                ��ʾ�ɹ���������ֵ�ļ�ֵ�Ը���
*/
int operator >> (ifstream& fin, PolyDictionary& dictionary)
{
	int successInputNumber = 0;
	/*
	* ���������ļ�ֱ��EOF
	*/
	while (!fin.eof())
	{
		/*
		*        key: ��(�ؼ���)
		* polyString: �������ɶ���ʽ���ַ���
		*/
		string key;
		string polyString;
		/*
		* ��':'֮ǰ��ȡ��key
		* ͬʱ���key���п�ͷ����հ��ַ�
		*/
		getline(fin, key, ':');
		clearSpace(key, ' ');
		clearSpace(key, '\n');
		getline(fin, polyString, ';');
		if (!key.empty() && !polyString.empty())
		{
			/*  ��ֵ��:
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
		cout << string(width / 4, ' ') << "Ŀǰ�洢�Ķ���ʽ��:" << "\n\n";
		cout << *this << endl;
	}
	if (showLastLine)
		printLine();
}

void System::displayInstruction(int width)
{
	cout << ": ) ��ϸ�������﷨����: \n\n";
	cout << string(7, ' ') << "push ������ʽ����:������ʽ��  ==>  ��Ӷ���ʽ\n";
	cout << string(5, ' ') << "remove ������ʽ����  ==>  �Ƴ�����ʽ\n";
	cout << string(7, ' ') << "show ������ʽ�� + ������ʽ��  ==>  ����ʽ�ӷ�����\n";
	cout << string(7, ' ') << "show ������ʽ�� - ������ʽ��  ==>  ����ʽ��������\n";
	cout << string(7, ' ') << "show ������ʽ�� * ������ʽ��  ==>  ����ʽ�˷�����\n";
	cout << string(7, ' ') << "show !������ʽ��  ==>  ����ʽ��\n";
	cout << string(7, ' ') << "show ~������ʽ��  ==>  ����ʽ�󲻶�����\n";
	cout << string(8, ' ') << "get ������ʽ��(��x��ȡֵ��)  ==>  �� x =��x��ȡֵ��ʱ, ����ʽ��ֵ\n";
	cout << string(8, ' ') << "get ������ʽ��(���½硿,���Ͻ硿)  ==>  �����ʽ�ӡ��½硿�������Ͻ硿�Ķ�����\n";
	cout << "\n";
	cout << string(5, ' ') << "��ܰ������ʾ: \n";
	cout << string(7, ' ') << "��show������, �ڱ��ʽǰ�����ǰ׺  \"������ʽ����:\"\n" << string(7, ' ') << "���ɽ��ý���ԡ�����ʽ��������ϵͳ��\n";
}

void System::displaySimpleInstruction(bool simplist, int width)
{
	cout << "���ڿ���������������: \n";
	if (simplist)
	{
		cout << string(5, ' ') << "��push��,��remove��,��show��,��get��" << endl;
		cout << string(5, ' ') << "��save��,��clear��,��reload��,��help��,��quit��" << endl;
	}
	else
	{
		cout << string(7, ' ') << "�� push ����Ӷ���ʽ" << string(9, ' ') << "��remove���Ƴ�����ʽ\n" << string(7, ' ') << "�� show ������ʽ����" << string(9, ' ') << "��  get ������ʽ��ֵ���������\n" << string(7, ' ') << "�� help ���鿴��ϸ����" << string(7, ' ') << "�� save �����ٱ���\n" << string(7, ' ') << "�� clear�������������" << string(7, ' ') << "��reload�����¼�������\n" << string(7, ' ') << "�� quit �����沢�˳�" << endl;
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
		cerr << "�����������Ϊ��" << endl;
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
			cerr << "����ʽ����Ϊ��, ����������" << endl;
			return false;
		}
		poly = Polynomial(polyString);
		return true;
	}
	else
	{
		/*
		* ��ȡkey, ��û��key, ��Ϊ��
		*/
		bool keyFound = content.find(':') != content.npos;
		if (keyFound)
			getline(contentFlow, key, ':');
		/*
		* ��ȡ������ʽ
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
		cerr << "key����Ϊ��, ����������" << endl;
		return false;
	}
	return true;
}

bool System::inputContent(const std::string& content, std::string& key, Polynomial& lhs, Polynomial& rhs, const char sign)
{
	istringstream contentFlow(content);
	/*
	* ��ȡkey, ��û��key, ��Ϊ��
	*/
	bool keyFound = content.find(':') != content.npos;
	if (keyFound)
		getline(contentFlow, key, ':');
	/*
	* �����Ԫ�������Ĺ����ַ���
	*/
	string lhsStr, rhsStr;
	getline(contentFlow, lhsStr, sign);
	getline(contentFlow, rhsStr, '\n');
	if (lhsStr.empty() || rhsStr.empty())
	{
		cerr << "����һ�����ʽΪ��, ����������" << endl;
		return false;
	}
	bool successLhs = stringToPolynomial(lhsStr, lhs);
	bool successRhs = stringToPolynomial(rhsStr, rhs);
	if (successLhs&&successRhs)return true;
	return false;
}

/*
* switche(...): ����һ����Ҫ����ת����, ��main�б�����
*            ����: ��������instruction, ��ת����ͬ��ģ��
*    instruction: ���ܵ���ָ��
*                  ��ָ��: help, clear, reload, save
*                 һ��Ҫ�������ݵ�ָ��: push, remove, show, get
*        content: ���ܵ�������, ���ڵ�ָ����˵, ����������ν��, ��Ϊ�ò���
*/
void System::switcher(const std::string& instruction, const std::string& content)
{
	/* =====================================
	*      ������(����ֻ��һ�����ʵ�����)����
	*  =====================================*/
	/*
	* ���ָ����help(����)
	* ������ʾ��ϸ�������﷨����displayInstruction()
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
	* ���ָ����reload(���¼���)
	*/
	if (instruction == "reload")
	{
		reload();
		displayHead("");
		cout << "���¼������" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/*
	* ���ָ����save(����)
	*/
	if (instruction == "save")
	{
		save();
		cout << "�ɹ�����" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/*
	* ���ָ����clear(�������)
	*/
	if (instruction == "clear")
	{
		clear();
		displayHead("�ɹ��������������");
		cout << "�벹��? �������롾reload��" << endl;
		displaySimpleInstruction(true);
		cout << endl;
		return;
	}

	/* =====================================
	*             ���� + ������ʽ
	*  =====================================*/
	/*
	*       key: ���洦���Ķ���ʽ������
	*    result: ���洦���Ķ���ʽ
	*/
	string key;
	Polynomial result;

	/*
	* push: ��Ӷ���ʽָ��
	*/
	if (instruction == "push")
	{
		push(content, key, result);
		return;
	}

	/*
	* remove: �Ƴ�����ʽָ��
	*/
	if (instruction == "remove")
	{
		remove(content, key);
		return;
	}

	/*
	* show: չ������ָ��
	*/
	if (instruction == "show")
	{
		/*
		* ���и���operationJudge(content)ָ�����ж��Ƕ�Ԫ���㻹��һԪ����
		*/
		show(operationJudge(content), content, key, result);
		return;
	}

	/*
	* get: ��ֵ, �󶨻���ָ��
	*/
	if (instruction == "get")
	{
		get(content, key);
		return;
	}

	/*
	* �������ָ���ƥ��, ��˵������ָ�����
	*/
	if (flag)
		cerr << "ָ����������, ����������" << endl;
}


/*
* �ÿ�����key������������ʽ���ַ���ת���ɶ���ʽ
*   polyString: �ַ���, ������key, Ҳ�����������ŵĶ���ʽ�ַ�
*         poly: �����������Ķ���ʽ
*       return: ����ֵ
*               true: poly�ɹ��õ���ֵ
*              false: poly��ֵʧ��ԭ��Ϊkey��Ӧ�Ķ���ʽ�Ҳ���
*/
bool System::stringToPolynomial(const std::string& polyStringOrKey, Polynomial& poly)
{
	/*
	* �ж�polyString �Ƿ���һ����ʶ��key
	*/
	bool polyStringIsKey = polyStringOrKey.find('(') == polyStringOrKey.npos;
	if (polyStringIsKey)
	{
		string key = polyStringOrKey;
		clearSpace(key, ' ');
		bool keyIsFound = this->getDictionary().find(key) != this->getDictionary().end();
		/*
		* ���ҵ�key, ��poly��ֵΪkey����Ӧ�Ķ���ʽ
		*/
		if (keyIsFound)
		{
			poly = this->getDictionary().at(key);
			return true;
		}
		cerr << "��һ�����ʽ�Ҳ���: " << key << " ,����������ָ��" << endl;
		return false;
	}
	/*
	* ��polyString�Ǵ����ŵĶ���ʽ�ַ���
	* ��ֱ�Ӹ���poly
	*/
	poly = Polynomial(polyStringOrKey);
	return true;
}

/*
* �ж������Ƕ�Ԫ���㻹��һԪ����
*  true: ��Ԫ
* false: һԪ
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
	displayHead("�ɹ���Ӹö���ʽ");
}

void System::remove(const std::string& content, std::string& key)
{
	if (inputContent(content, key) == false)
		return;
	if (this->getDictionary().erase(key) != 0)
		displayHead("�ɹ��Ƴ��ö���ʽ");
	else
	{
		cerr << "keyֵ��Ӧ�Ķ���ʽ�Ҳ���" << endl;
	}
}

void System::show(bool operationType, const std::string& content, std::string& key, Polynomial& result)
{
	if (operationType == true)
	{
		/*
		* ��Ԫ�������
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
		* һԪ�������
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
	* �����key, ������ֵ���
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
	* ������
	*/
	displayHead("");
	cout << "�õ��Ľ��Ϊ:\n" << string(5, ' ') << (key.empty() ? "��� =" : string(key + "(x) =")) << result << endl;
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
	* ������
	*/
	displayHead("");

	if (isValueOperation)
	{
		resultValue = poly(a);
		if (key.empty())
			cout << "�õ��Ľ��Ϊ:\n" << string(5, ' ') << polyString << "(" << a << ") = " << resultValue << endl;
		else
			cout << "�õ��Ľ��Ϊ:\n" << string(5, ' ') << key << "( " << a << " ) = " << resultValue << endl;
	}
	else
	{
		resultValue = poly(a, b);
		cout << "�õ��Ľ��Ϊ:\n" << string(5, ' ') << "��" << polyString << "(x)(" << a << "��" << b << ")" << key << " = " << resultValue << endl;
	}
	displaySimpleInstruction(true);
	cout << endl;
}

void System::printLine(char ch, int width)
{
	cout << string(width, ch) << "\n";
}
