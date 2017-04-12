// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//
#include<polynominal.h>
#include<polynominal.cpp>
using namespace std;
int main()
{
	manual();
	polynominalstore* mycalculator = polynominalstore::getinstance();
	string input;
	while (cin >> input)
	{
		if (is_exit(input))
		{
			cout << "The program will soon exit" << endl;
			exit(1);
		}
		if (is_manual(input))
		{
			manual();
		}
		cout << "Please enter a polynominal expression" << endl;
		polynominal mypolynominal;
		mypolynominal.read();
		if (_issave())
		{
			mycaculator.push(mypolynominal, name);
		}
		cout << "What do you want to do next?" << endl;
		instructions();
	}
    return 0;
}

