#include <iostream>
#include"Polynomial_calculator.h"
#include"Polynomial_calculator.cpp"
using namespace std;
int main()
{
	Calculator sys;
	sys.displayHead("Hello, my dump cousin!");
	sys.displayInstruction();
	int flag = 1;
	string order;
	cout << ":: ";
	getline(cin, order, '\n'); //当指令是7时，退出程序
	while (order != "7")
	{
		string instruction, content;
		sys.inputOrder(order, instruction, content);
		sys.switcher(instruction, content);//根据不同指令转到不同函数
		cout << "::";
		getline(cin, order, '\n');
	}
cout << "Goodbye!" << endl;
cout << "Please finish the homework yourself next time!" << endl;
	return 0;
}
