#include<cmath>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<string.h>
using namespace std;
extern string order, instruction, content;
//bool is_exit(string&);
class monomial
{
public:
	 monomial(const double& coefficient = 0, const double& power = 1);
 monomial(const string& );
	 monomial(const monomial&);
	double getpower() const;
	double getcoefficient() const;
	void setpower(const double&);
	void setcoefficient(const double&);
	bool is_empty();
	 monomial& operator -( ) ;
	double& operator()(double) ;
	double& operator()(double&, double&);
	monomial& operator ~() const;
	monomial& operator !() const;
operator()(double&, double&);
	friend istream& operator >>(istream&, monomial&);
	friend ifstream& operator >>(ifstream&, monomial&);
	friend ostream& operator <<(ostream&, monomial&);
	friend ofstream& operator << (ofstream&, monomial&);
	friend int compare_power(monomial&);
	friend monomial& operator +(monomial&, monomial&);
	friend monomial& operator -(monomial&, monomial&);
	friend monomial& operator *(monomial&, monomial&);
	friend monomial& operator /(monomial&, monomial&);
private:
	double  coefficient;
	double power;
};
class polynominal
{
public:
	explicit polynominal(string&);
	polynominal();
	vector<monomial>& getpolynominal();
	friend int operator >> (string&, polynominal&);
	friend istream& operator >> (istream&, polynominal&);
	friend ostream& operator << (ostream&, polynominal&);
	friend ofstream& operator << (oftream&, polynominal&);
	friend polynominal& operator +(polynominal&, polynominal&);
	friend polynominal& operator -(polynominal&, polynominal&);
	friend polynominal& operator *(polynominal&, polynominal&);
	friend polynominal& operator /(polynominal&, polynominal&);
	 polynominal& operator ~();
	 polynominal& operator !();
	 polynominal& operator -();
	 double& operator()(double x);
	double operator ()(const int&, const int&);
	void setname(string&);
	string& getname();
	void sort();
	void push(monomial&);
private:
	vector<monomial> data;
	string name;
};
class polynominalstore
{
public:
	map<string, polynominal>& getdata_base();
	friend int operator >> (ifstream&, polynominalstore&);
	friend ostream& operator << (ostream&, polynominalstore&);
	friend ofstream& operator << (ofstream&, polynominalstore&);
	void push(polynominal&, string&);
	void save(const std::string& address = "file/data.txt");
	void reload(const string& address = "file/data.txt");
	void clear();
	void remove(string&);
	void show();
	void show(string&);
	polynominal& find(string&);
	static polynominalstore* getinstance();
	void instructions();
private:
	map<string, polynominal> data_base;
	friend ostream&  operator << (ostream&, polynominalstore&);
	polynominalstore();
	static polynominalstore* instance;
};
void manual()
{
	cout << "Do you have any trouble!" << endl;
	cout << "When entering 1, you can add 2 different expressions" << endl;
	cout << "When entering 2, you can subtract 2 different expressions" << endl;
	cout << "When entering 3, you can multiply 2 different expressions" << endl;
	cout << "When entering 4, you can get the value of this expression" << endl;
	cout << "When entering 5, you can show the existent expressions" << endl;
}
bool is_exit(string& a)
{
	if (a[0] == 'Q' && a.length() == 1)
		return true;
	return false;
}
extern polynominal tempexpression, tempexpression2;
polynominalstore* polynominalstore::instance = NULL;
