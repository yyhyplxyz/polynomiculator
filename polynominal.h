#include<cmath>
#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include<map>
#include<set>
using namespace std;
polynominalstore* polynominalstore::instance = NULL;
class polynominal
{
public:
	polynominal();
	void read();
	int& calculate(int&);
	void setname(string&);
	polynominal& add(polynominal&);
	polynominal& subtract(polynominal&);
	polynominal& multiply(polynominal&);
	polynominal& deriviate();
	string& getname();
	vector<pair<int, int>>& getdata();
private:
	vector<pair<int, int>> data;
	string name;
	friend ostream&  operator << (ostream&, polynominal&);
};
class polynominalstore
{
public:
	void push(polynominal&, string&);
	polynominal& find(string&);
	static polynominalstore* getinstance();
	void instructions();
private:
	vector<polynominal> data_base;
	friend ostream&  operator << (ostream&, polynominalstore&);
	polynominalstore();
	static polynominalstore* instance;
};
void manual()
{
	cout << "Welcome to this polynominal calculator!" << endl;
	cout << "When entering 1, you can add 2 different expressions" << endl;
	cout << "When entering 2, you can subtract 2 different expressions" << endl;
	cout << "When entering 3, you can multiply 2 different expressions" << endl;
	cout << "When entering 4, you can get the value of this expression" << endl;
	cout << "When entering 5, you can show the existent expressions" << endl;
}
void polynominalstore:: instructions()
{
	string instruction;
	while (cin >> instruction && !is_exit(instruction) && is_manual(instruction))
	{
		switch (instruction[0])
		{
			case '1' :
				cout << "Enter two different expressions" << endl;
				string a;
				cin >> a;
				string temp1 = a.substr(0, a.find(" "));
				string temp2 = a.substr(a.find(" ") + 1, a.length());
				polynominal left = find(temp1);
				polynominal right = find(temp2);
				polynominal res;
				if (!(left.getname() == "NULL" && right.getname() == "NULL"))
					cout << "The polynominal expressions don't exist! Please enter instructions again!" << endl;
				else
				{
					res = left.add(right); 
					cout << res << endl;
				}
				break;
			case '2':
				cout << "Enter two different expressions" << endl;
				string a;
				cin >> a;
				string temp1 = a.substr(0, a.find(" "));
				string temp2 = a.substr(a.find(" ") + 1, a.length());
				polynominal left = find(temp1);
				polynominal right = find(temp2);
				polynominal res;
				if (!(left.getname() == "NULL" && right.getname() == "NULL"))
					cout << "The polynominal expressions don't exist! Please enter instructions again!" << endl;
				else
				{
					res = left.subtract(right);
					cout << res << endl;
				}
				break;
			case '3':
				cout << "Enter two different expressions" << endl;
				string a;
				cin >> a;
				string temp1 = a.substr(0, a.find(" "));
				string temp2 = a.substr(a.find(" ") + 1, a.length());
				polynominal left = find(temp1);
				polynominal right = find(temp2);
				polynominal res;
				if (!(left.getname() == "NULL" && right.getname() == "NULL"))
					cout << "The polynominal expressions don't exist! Please enter instructions again!" << endl;
				else
				{
					res = left.multiply(right);
					cout << res << endl;
				}
				break;
			case '4':
				int value;
				cin >> value;
				string a;
				cin >> a;
				polynominal temp = find(a);
				long long res = 0;
				vector<pair<int, int>> 
				for (int i = 0; i < temp.getdata().size(); i++)
				{
					long long t = pow(value, temp.getdata[i].second);
					res += t * temp.data[i].first;
				}
				cout << "The value is " << res << endl;
				break;
			case '5':
				cout << "The following are the existent expressions you've entered." << endl;
				for (int i = 0; i < data_base.size(); i++)
				{
					cout << data_base[i] << endl;
				}
				break;
		}
	}
	if (is_exit(instruction))
	{
		cout << "The program will soon exit" << endl;
		exit(1);
	}
	if (is_manual(instruction))
	{
		manual();
	}
	return;
}
bool is_manual(string& a)
{
	if (a == "man")
	{
		manual();
		return true;
	}
	else
		return false;
}
bool is_exit(string& a)
{
	if (a[0] == 'Q' && a.length() == 1)
		return true;
	return false;
}
bool is_save()
{
	cout << "Do you want to save this polynominal ?" << endl;
	cout << "If you want, please enter a character to name this expression." << endl;
	static string name;
	if (cin >> name)
	{
		if (is_manual(name))
		{
			while (1)
			{
				cin >> name;
				if (!is_manual(name))
					break;
			}
		}
		else
			return true;
	}
	else
		return false;
}
