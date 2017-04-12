#include<iostream>
#include<string>
#include"polynominal.h"
using namespace std;
ostream& operator << (ostream& out, polynominalstore& temp)
{
	int cnt = 1;
	for (auto& i : temp.data_base)
	{
		out << cnt << "." << i << endl;
		cnt++;
	}
	return out;
}
ostream& operator << (ostream& out, polynominal& temp)
{
	int cnt = 0;//记录已输出多项式的项数，方便调整输出格式
	for (auto i : temp.data)
	{
		if (cnt == 0)
			out << i.first << "x^" << i.second << " ";
		else
		{
			if (i.first > 0)
			{
				out << "+ " << i.first << "x^" << i.second << " ";
			}
			else
			{
				out << "- " << i.first << "x^" << i.second << " ";
			}
		}
		return out;
	}
}
polynominal::polynominal()
{
	name = "NULL";
}
string& polynominal::getname()
{
	return name;
}
void polynominal::read()
{
	string temp;
	cout << "Please enter the polynominal" << endl;
	cin >> temp;
	int cnt = 0;
	bool flag = 0;
	int size = temp.length();
	int coefficient;
	int index;
	int judge = 0; //判断何时可以向vector中push一对系数与指数
	while (cnt != size)
	{
		if (temp[cnt] == '(' || temp[cnt] == ')')
			continue;
		if (temp[cnt] == ',')
			flag = 1;
		if (flag)

		{
			index = temp[cnt] - '0';
			judge++;

		}
		else
		{
			coefficient = temp[cnt] - '0';
			judge++;
		}
		if (judge == 2)
		{
			data.push_back(make_pair(coefficient, index));
			judge = 0;
		}
		cnt++;
	}

}
void polynominal::setname(string& temp)
{
	name = temp;
}
int& polynominal::calculate(int& num)
{
	int res = 0;
	for (auto i : data)
	{
		res += pow(num, i.second) * i.first;
	}
	return res;
}
polynominal& polynominal::add(polynominal& right)
{
	polynominal res;
	int i = 0;
	int j = 0;
	int size_l = data.size();
	int size_r = right.data.size();
	bool flag = 0; //判断两个多项式相加，哪个多项式的项数最大
	if (size_l > size_r)
		flag = 1;
	for (; i < size_l, j < size_r; )
	{
		if (data[i].second == right.data[j].second)
		{
			res.data.push_back(make_pair(data[i].first + right.data[j].first, right.data[j].second));
			i++;
			j++;
		}
		else if (data[i].second > right.data[j].second)
		{
			res.data.push_back(data[i]);
			i++;
		}
		else if (data[i].second < right.data[j].second)
		{
			res.data.push_back(right.data[j]);
			j++;
		}
	}
	if (flag)
	{
		for (; i < size_l; i++)
		{
			res.data.push_back(data[i]);
		}
	}
	else
	{
		for (; j < size_r; j++)
		{
			res.data.push_back(right.data[j]);
		}
	}
	return res;
}
polynominal& polynominal::subtract(polynominal& right)
{
	polynominal res;
	int i = 0;
	int j = 0;
	int size_l = data.size();
	int size_r = right.data.size();
	bool flag = 0; //判断两个多项式相减，哪个多项式的项数最大
	if (size_l > size_r)
		flag = 1;
	for (; i < size_l, j < size_r; )
	{
		if (data[i].second == right.data[j].second)
		{
			res.data.push_back(make_pair(data[i].first - right.data[j].first, right.data[j].second));
			i++;
			j++;
		}
		else if (data[i].second > right.data[j].second)
		{
			res.data.push_back(data[i]);
			i++;
		}
		else if (data[i].second < right.data[j].second)
		{
			res.data.push_back(make_pair(-right.data[j].first, data[j].second));
			j++;
		}
	}
	if (flag)
	{
		for (; i < size_l; i++)
		{
			res.data.push_back(data[i]);
		}
	}
	else
	{
		for (; j < size_r; j++)
		{
			res.data.push_back(make_pair(-right.data[j].first, data[j].second));
		}
	}
	return res;
}
polynominal& polynominal::multiply(polynominal& right)
{
	polynominal res;
	map<int, int> temp;
	int i = 0;
	int j = 0;
	int size_l = data.size();
	int size_r = right.data.size(); polynominal res;
	int i = 0;
	int j = 0;
	int size_l = data.size();
	int size_r = right.data.size();
	for (; i < size_l; i++)
	{
		for (; j < size_r; j++)
		{
			temp[data[i].second + right.data[j].second] += data[i].first * right.data[j].first;
		}
	}
	for (auto& k : temp)
	{
		res.data.push_back(k.second, k.first);
	}
}
polynominal& polynominal::deriviate()
{
	polynominal res;
	for (auto i : data)
	{
		res.data.push_back(make_pair(i.first * i.second, i.second - 1));
	}
	return res;
}
vector<pair<int, int>>& polynominal::getdata()
{
	return data;
}
polynominalstore* polynominalstore::getinstance()
{
	if (instance)
		return instance;
	else
	{
		instance = new polynominalstore();
		return instance;
	}
}
void polynominalstore::push(polynominal& temp, string& name)
{
	temp.setname(name);
	data_base.push_back(temp);
}
polynominal& polynominalstore::find(string& a)
{
	int size = data_base.size();
	polynominal res;
	for (int i = 0; i < size; i++)
	{
		if (data_base[i].getname() == a)
		{
			return data_base[i];
		}
	}
	return res;
}
