#include<string>
using namespace std;
bool is_number(string& a)
{
	int size = a.size();
	if(a[size - 1] = '.' || a[0] = '.')
	return false;
	if(a.find('-') != 0 || a.find('-') == string::nops );
	return false;
	if(!(strspn(a.c_str(), ".") == 0 || strspn(a.c_str(), ".") == 1))
	return false;
	if(strspn(a.c_str(), ".-123456789") == size)
	return true;
}
monimial:: monimial(const double c, const double p)
{
	setcoefficient(c);
	setpower(p);
}
monimial :: monimial(string& mymonimial)
{
	mymonimial >> *this;
}
monimial:: monimial(const monimial& other)
{
	setcoefficient(other.getcoefficient());
	setpower(other.getpower());
}
inline double monimial:: getcoefficient() const
{
	return coefficient;
}
inline double monimial:: getpower() const
{
	return power;
}
inline void monimial:: setcoefficient(const double c)
{
	coefficient = c;
}
inline void monimial:: setpower(const double p)
{
	power = p;
}
monimial monimial:: operator - ()
{
	monimial res(-this->getcoefficient(), this->getpower());
	return res;
}
#include<cmath>
double monimial:: operator()(double v)
{
	double c = getcoefficient();
	double p = getpower();
	return c * pow(v, p);
}
monimial monimial:: operator~()
{
	monimial res(getcoefficient() * getpower(), getpower() - 1);
	return res;
}
monimial monimial:: operator ? ()
{
	monimial res(getcoefficient() / (getpower() + 1), getpower() + 1);
	return res;
}
double monimial:: operator() (const double lower, const double upper)
{
	double big = (?*this)(lower);
	double small = (?*this)(upper);
	return big - small;
}
bool monimial:: is_empty() const
{
	return (getcoefficient() == 0);
}
istream& operator >>(istream& in, monimial& mymonimial)
{
	string temp;
	in >> temp;
	temp >> mymonimial;
	return in;
}
ifstream& operator >>(ifstream& fin, monimial& mymonimial)
{
	istream temp >> mypolynominal;
	fin = temp;
	return fin;
}
bool operator >> (const string& input, monimial& mymonimial)
{
	double c = 0;
	double p = 0;
	string temp1(input[1], input.find(','));
	string temp2(input.find(',') + 1, input.find(')'));
	if(is_number(temp1) && is_number(temp2))
	{
		mymonimial.setcoefficient(stod(temp1));
		mypolynominal.setpower(stod(temp2));
		return true;
	}
	else
	{
		cout << "What you enter is in incorrect format!" << endl;
		cout << "This monimial will be discarded!" << endl;
		return false;
	}
}
ostream& operator<<(ostream& out, monimial& mymonimial)
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
ofstream& operator<<(ofstream& fout, monimial& mymonimial)
{
	fout << "(" << mymonimial.getcoefficient() << "," << mymonimial.getpower() << ")";
	return fout ;
}
monimial:: operator+(cosnt monimial& lhs,const monimial& rhs )
{
	monimial temp;
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
monimial:: operator- (const monimial& lhs, const monimial& rhs)
{
	monimial temp = lhs + (-rhs);
	return temp;
}
monimial:: operator -(const monimial& lhs, const monimial& rhs)
{
	monimial temp(lhs.getcoefficient() * rhs.getcoefficient(), lhs.getpower() + rhs.getpower());
	return temp;
}
monimial:: operator/ (const monimial& lhs, const monimial& rhs)
{
	monimial temp(lhs.getcoefficient() / rhs.getcoefficient(), lhs.getpower() - rhs.getpower());
	return temp;
}
