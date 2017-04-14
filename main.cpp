// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//
#include<polynominal.h>
#include<polynominal.cpp>
#include<iostream>
#include<string>
using namespace std;
int main()
{
	welcome();
	manual();
	polynominalstore* mycalculator = polynominalstore::getinstance();
	cout >> "Please enter: ";
	getline(cin, order, '\n');
	while (!is_exit(order))
	{
		string instruction;
		string content;
		getline(cin, instruction, ' ');
		getline(cin, content, '\n');
		if(instruction.empty() || content.empty())
		{
			cerr << "You may have entered some blank instructions or content, please enter again" << endl;
			//cout >> "Please enter: ";
		}
		else
		{
			switcher(instruction, content);
		}
		cout >> "Please enter: ";
		getline(cin, order, '\n');
	}
	if (is_exit(order))
	{
		cout << "The program will soon exit" << endl;
		exit(1);
	}
    return 0;
}
