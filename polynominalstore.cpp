#include<polynominal.h>
#include<polynominal.cpp>
using namespace std;
#include "polynominalstore.h"
#include<string>
using namespace std;
bool singleoperation(string& a)
{
  int number = strspn(a.c_str(), "~?");
  if(number == 1)
  return true;
  else
  return false;
}
bool doubleoperation(string& a, int& location)
{
  int number = strspn(s.c_str(), "+-*");
  if(number == 1)
  {
    int l = a.find("+");
    if(l != string::nops)
    l = a.find("-");
    if(l != string::nops)
    l = a.find("*");
    if(l != string:: nops)
    l = a.find("/");
    location = l;
    return true;
  }
    else
  return false;
}
void clearSpace(std::string& str, char spaceChar = " ")
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
int operator>>(ifstream& fin, polynominalstore& dictionary)
{
	int successInputNumber = 0;
	while (!fin.eof())
	{
		string key;
		string polyString;
		getline(fin, key, ':');
		clearSpace(key, ' ');
		clearSpace(key, '\n');
		getline(fin, polyString, ';');
		if (!key.empty() && !polyString.empty())
		{
			Polynomial pTemp(polyString);
			dictionary.getdata_base().emplace(key, pTemp);
			successInputNumber++;
		}
	}
	return successInputNumber;
}
ostream& operator<<(ostream& out, polynominalstore& poly)
{
	for (map<string, Polynomial>::iterator i = poly.getdata_base().begin();
	i != poly.getdata_base().end(); ++i)
	{
		out << i->first << "(x) =" << i->second << endl;
	}
	return out;
}
void polynominalstore:: displaySimpleInstruction()
{
  cout << *this;
}
ofstream& operator<<(ofstream& fout, polynominalstore& poly)
{
	for (map<string, Polynomial>::iterator i = poly.getdata_base().begin();
	i != poly.getdata_base().end(); ++i)
	{
		fout << i->first << ':';
		fout << i->second << ";\n";
	}
	fout << endl;
	return fout;
}
inline map<string, Polynomial>& polynominalstore::getdata_base()
{
	return __dictionary;
}

double polynominalstore::operator()(const string& key, double x) const
{
	return __dictionary.at(key)(x);
}
Polynomial& polynominalstore::operator[](const std::string& key)
{
	return __dictionary.at(key);
}
bool polynominalstore:: is_order( )
{
  istringstream other(order);
  clearSpace(other);
  getline(other, content, '\n');
  if(content == "reload" || content == "help" || content == "save" || content == "clear")
  {
    content_switcher();
  }
  is_content();
  if(!instruction.empty() && !contnet.empty())
  return true;
  else
  {
    cerr << "The instruction or the polynominal's contnet is empty!" << endl;
    return false;
  }
}
bool polynominalstore:: is_content()
{
    istringstream other(content);
    clearSpace(other);
    if(singleoperation(other))
    {
      instruction = other[0];
      string temp(other[1], other.end());
      if(is_exist(temp))
      {
        tempexpression = this->data_base.find(temp);
      }
      else
      temp >> tempexpression;
    }
    int location = 0;
    if(doubleoperation(other, location))
    {
      string temp(other[0], other[location]);
      string temp2(other[location + 1], other.end());
      instruction = other[location];
      if(is_exist(temp))
      tempexpression = data_base.find(temp);
      else
      temp >> tempexpression;
      if(is_exist(temp2)
    {
      tempexpression2 = data_base.find(temp2);
    }
    else
      temp2 >> tempexpression2;
    }
    else
    cerr << "You've entered wrong format!" << endl;
}
void polynominalstore:: content_switcher()
{
  switch(content)
  {
    case "reload":
    reload();
    display("You've suuceefully undo what you have done after you last save instruction!") ''
    displaySimpleInstruction();
    break;
    case "save":
    save();
    display("You've Successfully save this polynominal!") << endl;
    displaySimpleInstruction();
    break;
    case "help":
    manual();
    break;
    case"clear"
    clear();
    display("All the data have been cleared!") << endl;
    display("If you want to retrieve, please enter reload!") << endl;
    break;
  }
}
void polynominalstore:: instruction_switcher()
{
  switch(instruction)
  {
    case "+":
    tempexpression = tempexpression + tempexpression2;
    cout << tempexpression << endl;
    break;
    case "-":
    tempexpression = tempexpression - tempexpression2;
    cout << tempexpression << endl;
    break;
    case "*":
    tempexpression = tempexpression * tempexpression2;
    cout << tempexpression << endl;
    break;
    case "/":
    tempexpression = tempexpression / tempexpression2;
    cout << tempexpression << endl;
    break;
  }
  cout << "Do you want to save this polynominal ? " << endl;
  cout << "if you want, please enter the name, else enter space"  << string(' ', 7)  << ">>" << endl;
  string name;
  cin >> name;
  if(name != " "){
    push(name);
    display("You've successfully named this polynominal") << endl;
  }
cout << "Do you want to calculate?" << endl;
cout << "if you want, please enter the number, else enter space"  << string(' ', 7)  << ">>" << endl;
string number;
cin >> number;
if(name != "")
{
  int flag = name.find(",");
  if(flag == string:: nops)
  {
    double num = stod(number);
  double res =   tempexpression(num);
  cout << "This is the value:" << res <<  endl;
  }
  else{
    string a(number[0], number[flag]);
    string b(number[flag + 1], number[number.size() - 1]);
    int a_num = stod(a);
    int b_num = stod(b);
    cout << "This is the value:" << tempexpression(a_num, b_num) << endl;
  }
}

}
void polynominalstore::push(polynominal& poly, string& name)
{
  if(is_content(name))
  {
    this->data_base.emplace(name, poly);
    display("Successfully add this polynominal!");
  }
}
void polynominalstore::save(const std::string& address)
{
  ofstream fout;
  fout.open("file/data.txt");
  if(fout)
    fout << *this;
  else
    cerr << "Fail to open the file!" << endl;
    fout.close();
    return;
}
void polynominalstore::reload(const string&  add)
{
  ifstream fin(add);
  if(fin)
  {
    fin >> *this;
  }
  else
  {
    cerr << "Fail to backtrack to the former version!" << endl;
  }
  fin.colse();
}
void polynominalstore::clear()
{
  data_base.clear();
}
void polynominalstore::move(string& name)
{
  if(is_content(name))
  {
    if(data_base.erase(name) )
    {
      display("Successfully remove this polynominal");
    }
    else
    {
      cerr << "This remove fails" << endl;
    }
  }
}
void polynominalstore::show()
{

}
void show(string&);
polynominal& find(string&);
static polynominalstore* getinstance();
void instructions();
#include "PolyDictionary.h"
using namespace std;
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
	if (sscanf_s(expression.c_str(), "%lf,%lf)", &a, &b) != 2)
	{
		isValueOperation = true;
		sscanf_s(expression.c_str(), "%lf)", &a);
	}
	/*
	* ��������
	*/
	displayHead("");

	if (isValueOperation)
	{
		resultValue = poly(a);
		if (key.empty())
			cout << "�õ��Ľ���Ϊ:\n" << string(5, ' ') << polyString << "(" << a << ") = " << resultValue << endl;
		else
			cout << "�õ��Ľ���Ϊ:\n" << string(5, ' ') << key << "( " << a << " ) = " << resultValue << endl;
	}
	else
	{
		resultValue = poly(a, b);
		cout << "�õ��Ľ���Ϊ:\n" << string(5, ' ') << "��" << polyString << "(x)(" << a << "��" << b << ")" << key << " = " << resultValue << endl;
	}
	displaySimpleInstruction(true);
	cout << endl;
}

void System::printLine(char ch, int width)
{
	cout << string(width, ch) << "\n";
}
