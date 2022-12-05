
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "Node.h"
#include "Comparator.h"
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::gregorian;
using namespace std;

extern struct Node;
extern struct Expression;

void tokenize(string const& str, const char delim,
	vector<string>& out);
void printAllTask(unordered_map<string, Node>& map);
void makeThreesome(vector<string> input, multimap<string, Expression>& out);
bool checkProper(string firstOne, vector<string> baseCommand);
void Compare(multimap<string, Expression>& inputTroika, unordered_map<string, Node>& oldList, unordered_map<string, Node>& newList);

//static vector<string> properSection = { "name", "description", "date", "category", "status" };
//static vector<string> properSign = { "<", ">", "=", "like" };

int main()
{
	setlocale(LC_ALL, "Russian");
	//����, ������� ��� �������, ��� ������ �������� ��� ����, � ��������� ��������� ����
	unordered_map<string, Node> ourList;
	string inputString; //������ ��� ������ �� �����
	vector<string> instanceCommand; //������ ��� ��������� ����
	multimap<string, Expression> troiki;
	unordered_map<string, Node> newList;

	while (true)
	{
		inputString.clear();
		instanceCommand.clear();
		cout << "Comand: ";
		getline(cin, inputString);
		tokenize(inputString, ' ', instanceCommand);

		//if (!checkProper(instanceCommand[0], basicComand))
		//	continue;

		if (instanceCommand[0] == "add" && instanceCommand.size() == 6) 
			addElem(instanceCommand, ourList);
		
		if (instanceCommand[0] == "done" && instanceCommand.size() == 2)
			markTaskDone(instanceCommand, ourList);

		if (instanceCommand[0] == "update" && instanceCommand.size() == 6)
			updateTask(instanceCommand, ourList);

		if (instanceCommand[0] == "delete" && instanceCommand.size() == 2)
			deleteTask(instanceCommand, ourList);
		
		if (instanceCommand[0] == "select")
		{
			makeThreesome(instanceCommand, troiki);
			Compare(troiki, ourList, newList);
			printAllTask(newList);
		}
			

		if (instanceCommand[0] == "show")
			printAllTask(ourList);

		//date first = from_uk_string(instanceCommand[0]);
		//date second = from_uk_string(instanceCommand[1]);
		//first < second ? cout << "\nsmaller\n" : cout << "\nbigger\n"; 
		
		

		
	}


	return false;
}

void printAllTask(unordered_map<string, Node> &map)
{
	int i = 1;
	
	for (auto iter : map)
	{
		cout << i << ". " << iter.second.name << " "
			<< iter.second.deskription << " "
			<< iter.second.data << " "
			<< iter.second.category << " "
			<< iter.second.isComplete;
		cout << endl;
			i++;
	}
}

bool checkProper(string firstOne, vector<string> baseCommand)
{
	for (const string& elem : baseCommand)
	{
		if (elem == firstOne) return true;
	}
	return false;
}

void tokenize(string const& str, const char delim,
	vector<string>& out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void Compare(multimap<string, Expression>& inputTroika, unordered_map<string, Node>& oldList, unordered_map<string, Node>& newList)
{
	if (inputTroika.size() == 0 || oldList.size() == 0) throw "�� ��������� ������ �������";
	if (newList.size() != 0) newList.clear(); // ����� �� �������� ������ �� ���������� �������� - ������� ����� ������ �������
	//�������� ������������ ����� �������. ������������ �������� ������ � ���������� �����. 
	for (auto condit : inputTroika)
		if (!isProperSection(condit.first) || !isProperSign(condit.second.sign)) return;
	bool isItNormal = true; //���������� ������ ��������� ���������� ���� �������. 
	for (auto elementList : oldList)
	{
		for (auto condition : inputTroika)
		{
			if (condition.second.sign == "<" || condition.second.sign == ">")
				if (condition.first == "date")
					compareDate(from_uk_string(condition.second.valueRight),
						condition.second.sign, elementList.second.data) ? isItNormal = true : isItNormal = false;
				else throw "�� ������� ������ ������ ����� ���� ������ ����!";
			if (condition.second.sign == "=")
				CompareForEqual(condition.first, condition.second.valueRight, elementList.second) ? isItNormal = true : isItNormal = false;
			if (condition.second.sign == "like")
				LikeSearch(condition.first, elementList.second, condition.second.valueRight) ? isItNormal = true : isItNormal = false;
		}
		if (isItNormal)  newList.insert({ elementList.first, elementList.second });
	}
}

/* ���� ���� select'a �������� �� ���� �� ������: 
1. ��� ����� ����� ��������� (�������, ��� ���� � ������� ����� ������)
2. ����, �� ����� ���� > < = � like
3. ������ �����, �� �����, ������� �� ����� ���������� � �����
������ makeThreesome ������� ����� ������. ����������� ��������� ����� and, ��� "���������" ������
�� ���� �� � ����� �������������. 
*/
void makeThreesome(vector<string> input, multimap<string, Expression>& out)
{
	if (out.size() != 0) out.clear(); //������� �� ����� ��� ��� ���� � ������, ����� �� ���� �������
	Expression exemp;
	//�� � ���� � ��������� ��� ����� and � ��� ����� ���� ���� �������, �� �� ����� ����������� ����� ���������
	if (!(std::find(input.begin(), input.end(), "and") != input.end()))
	{
		exemp.sign = input[2];
		exemp.valueRight = input[3];
		out.insert({ input[1], exemp });
		return;
	}
	vector<int> position_of_AND;
	
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == "and" || input[i] == "AND")
			position_of_AND.push_back(i);
	}
	
	for (auto i=position_of_AND.begin(); i != position_of_AND.end(); i++)
	{
		exemp.sign = input[*i - 2];
		exemp.valueRight = input[*i - 1];
		out.insert({ input[*i - 3], exemp });
	}
	//and the last one
	exemp.sign = input[position_of_AND.back() + 2];
	exemp.valueRight = input[position_of_AND.back() + 3];
	out.insert({ input[position_of_AND.back() + 1], exemp });
}