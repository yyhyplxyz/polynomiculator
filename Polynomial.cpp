#include "Polynomial.h"
#include<iostream>
using namespace std;
#include<string>
using namespace std;
bool is_exit(string& a)
{
	if(a == "Q")
	return true;
}
bool is_number(string& a)
{
	int size = a.size();
	if(a[size - 1] == '.' || a[0] == '.')
	return false;
	if(a.find('-') != 0 || a.find('-') == string::nops );
	return false;
	if(!(strspn(a.c_str(), ".") == 0 || strspn(a.c_str(), ".") == 1))
	return false;
	if(strspn(a.c_str(), ".-123456789") == size)
	return true;
}
monomial:: monomial(const double c, const double p)
{
	setcoefficient(c);
	setpower(p);
}
monomial :: monomial(string& mymonomial)
{
	mymonomial >> *this;
}
monomial:: monomial(const monomial& other)
{
	setcoefficient(other.getcoefficient());
	setpower(other.getpower());
}
inline double monomial:: getcoefficient() const
{
	return coefficient;
}
inline double monomial:: getpower() const
{
	return power;
}
inline void monomial:: setcoefficient(const double c)
{
	coefficient = c;
}
inline void monomial:: setpower(const double p)
{
	power = p;
}
monomial monomial:: operator - ()
{
	monomial res(-this->getcoefficient(), this->getpower());
	return res;
}
#include<cmath>
double monomial:: operator()(double v)
{
	double c = getcoefficient();
	double p = getpower();
	return c * pow(v, p);
}
monomial monomial:: operator~()
{
	monomial res(getcoefficient() * getpower(), getpower() - 1);
	return res;
}
monomial monomial:: operator ? ()
{
	monomial res(getcoefficient() / (getpower() + 1), getpower() + 1);
	return res;
}
double monomial:: operator() (const double lower, const double upper)
{
	double big = (?*this)(lower);
	double small = (?*this)(upper);
	return big - small;
}
bool monomial:: is_empty() const
{
	return (getcoefficient() == 0);
}
istream& operator >>(istream& in, monomial& mymonomial)
{
	string temp;
	in >> temp;
	temp >> mymonomial;
	return in;
}
ifstream& operator >>(ifstream& fin, monomial& mymonomial)
{
	istream temp >> mypolynominal;
	fin = temp;
	return fin;
}
bool operator >> (const string& input, monomial& mymonomial)
{
	double c = 0;
	double p = 0;
	string temp1(input[1], input.find(','));
	string temp2(input.find(',') + 1, input.find(')'));
	if(is_number(temp1) && is_number(temp2))
	{
		mymonomial.setcoefficient(stod(temp1));
		mypolynominal.setpower(stod(temp2));
		return true;
	}
	else
	{
		cout << "What you enter is in incorrect format!" << endl;
		cout << "This monomial will be discarded!" << endl;
		return false;
	}
}
ostream& operator<<(ostream& out, monomial& mymonomial)
{
	double c = mypolynominal.getcoefficient();
	double p = mypolynominal.getpower();
	if(c != 1)
	out << c;
	if(p == 1)
	{
		out << "x";
	}
	else
	{
		out << "x^" << p;
	}
	return out;
}
ofstream& operator<<(ofstream& fout, monomial& mymonomial)
{
	fout << "(" << mymonomial.getcoefficient() << "," << mymonomial.getpower() << ")";
	return fout ;
}
monomial:: operator+(cosnt monomial& lhs,const monomial& rhs )
{
	monomial temp;
	if(lhs.getpower() != rhs.getpower())
	{
		cerr << "The index is different!" << endl;
		cout << "This calculation will be discarded" << endl;
		return temp;
	}
	temp.setcoefficient(lhs.getcoefficient() + rhs.getcoefficient());
	temp.setpower(lhs.getpower());
	return temp;
}
monomial:: operator- (const monomial& lhs, const monomial& rhs)
{
	monomial temp = lhs + (-rhs);
	return temp;
}
monomial:: operator -(const monomial& lhs, const monomial& rhs)
{
	monomial temp(lhs.getcoefficient() * rhs.getcoefficient(), lhs.getpower() + rhs.getpower());
	return temp;
}
monomial:: operator/ (const monomial& lhs, const monomial& rhs)
{
	monomial temp(lhs.getcoefficient() / rhs.getcoefficient(), lhs.getpower() - rhs.getpower());
	return temp;
}
polynominal:: polynominal()
{

};
istream& operator>>(isstream& in, polynominal& mypolynominal)
{
	string poly;
	in >> poly;
	poly >> mypolynominal;
	return in;
}
void polynominal:: push(monomial& a)
{
	data.push(a);
}
int operator>>(string& polynominalString, polynominal& poly)
{
	int cnt = 0;
	auto head = polynominalString.begin();
	auto tail = head;
	while(tail != polynominalString.end())
	{
		while(*tail != '(')
		{
			tail++;
		}
		string temp(head, tail);
		if(temp.size())
		{
			monomial mon(temp);
			if(!mon.is_empty())
			{
				poly.push(mon);
				cnt++;
			}
		}
		head = tail;
		if(head != polynominalString.end())
		tail++;
	}
	poly.sort();
	return cnt;
}
ostream& operator << (ostream& out, polynominal& mypolynominal)
{
	if(mypolynominal.getpolynominal().is_empty())
	{
		out << " This polynominal is empty!" << endl;
		return out;
	}
	if(mypolynominal.getpolynominal()[0].getcoefficient() >= 0)
	{
		out <<" ";
		out << mypolynominal.getpolynominal()[0];
	}
	for(auto i = mypolynominal.getpolynominal()[1]; i != mypolynominal.getpolynominal().end(); i++)
	{
		if(i.getcoefficient() > 0)
		out << "+" << *i;
		else
		out << *i;
	}
	return out;
}
ofstream& operator<<(ofstream& fout, polynominal& mypolynominal)
{
	for(auto i = mypolynominal.begin(); i != mypolynominal.end(); i++ )
	{
		fout << *i;
	}
	return fout;
}
polynominal:: polynominal(string poly)
{
	poly >> *this;
}
struct cmp
{
	inline bool operator() (const polynominal& a, const polynominal& b)
	{
		return a.getpower() > b.getpower();
	}
};
void polynominal:: sort()
{
	std::sort(data.begin(), data.end(), cmp());
}

inline vector<monomial>& polynominal::getpolynominal()
{
	return data;
}

polynominal& polynominal::operator-() const
{
	polynominal temp = *this;
	for (auto i = temp.getpolynominal().begin();i != temp.getpolynominal().end();++i)
	{
		*i = -*i;
	}
	return temp;
}

double polynominal::operator()(double x) const
{
	double sum = 0;
	for (int i = 0; i < data.size(); i++)
	{
		sum += data[i](x);
	}
	return sum;
}

polynominal polynominal::operator~() const
{
	polynominal temp = *this;
	for (auto i = temp.getpolynominal().begin();	i != temp.getpolynominal().end(); ++i)
	{
		*i = ~*i;
	}
	return temp;
}
polynominal polynominal::operator!() const
{
	polynominal temp = *this;
	for (auto i = temp.getpolynominal().begin();i != temp.getpolynominal().end(); ++i)
	{
		*i = !*i;
	}
	return temp;
}
double polynominal::operator()(const double lowerBound, const double upperBound)
{
	double res = 0;
	for (auto i = data.begin();i != data.end(); ++i)
	{
		res= (*i)(lowerBound, upperBound);
	}
	return res;
}
polynominal& operator +(polynominal& lhs, polynominal& rhs)
{
	polynominal temp;
	auto ltemp = lhs.data.begin();
	auto rtemp = rhs.data.begin();
	while(ltemp != lhs.data.end() && rtemp != rhs.data.end())
	{
		if(ltemp.getpower() == rtemp.getpower())
		{
			monomial i = *ltemp + *rtemp;
			temp.push(i);
			ltemp++;
			rtemp++;
		}
		if(ltemp.getpower() < rtemp.getpower())
		{
			temp.push(*rtemp);
			rtemp++;
		}
		else{
			temp.push(*ltemp);
			ltemp++;
		}
	}
	while(ltemp != lhs.data.end())
	{
		temp.push(*ltemp);
		ltemp++;
	}
	while(rtemp != rhs.data.end())
	{
		temp.push(*rtemp);
		rtemp++;
	}
	return temp;
}
polynominal operator -(polynominal& lhs, polynominal& rhs)
{
	polynominal temp = -rhs;
	return lhs + temp;
}
polynominal operator *(polynominal& lhs,polynominal& rhs )
{
	polynominal res;
	polynominal ptemp;
	for(auto i = lhs.getpolynominal.begin(); i != lhs.getpolynominal().end(); i++)
	{
		for(auto j = rhs.getpolynominal.begin(); j != rhs.getpolynominal.end(); j++)
		{
			monomial mtemp = (*i) * (*j);
			ptemp.push(mtemp);
		}
		ptemp.sort();
		res = res + ptemp;
	}
	return res;
}
