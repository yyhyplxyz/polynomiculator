#include <iostream>
#include"Untitled1.h" 
#include"Untitled2.cpp"
using namespace std; 
int main()
{
	System sys;
	sys.displayHead("Hello, my dump cousin!");
	sys.displaySimpleInstruction();
	int flag = 1;
	string order;
	cout << ">>> ";
	getline(cin, order, '\n');
	while (order != "quit")
	{
		string instruction, content;
		sys.inputOrder(order, instruction, content);
		//cout << instruction << endl;
		sys.switcher(instruction, content);	
		flag = 0; 	
		cout << ">>> ";
		getline(cin, order, '\n');
		cout << instruction;
	}
	sys.displayHead("Goodbye, please try your best to finish homework yourself next time!", false);
	return 0;
}
