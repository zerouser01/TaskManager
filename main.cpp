
#include <iostream>
#include <string>
#include <unordered_map>
#include "Node.h"
#include <vector>

using namespace std;

void tokenize(string const& str, const char delim,
	vector<string>& out);
void printAll(unordered_map<string, Node>& map);

bool checkProper(string firstOne, vector<string> baseCommand);

int main()
{
	
	setlocale(LC_ALL, "Russian");
	//»так, создаем хеш таблицу, где ключом €вл€етс€ им€ ноды, а значением экземпл€р ноды
	unordered_map<string, Node> ourList;
	string inputString; //храним всю строку из ввода
	vector<string> instanceCommand; //массив дл€ отдельных слов
	

	while (true)
	{
		inputString.clear();
		instanceCommand.clear();
		cout << "Comand: ";
		getline(cin, inputString);
		tokenize(inputString, ' ', instanceCommand);
		if (!checkProper(instanceCommand[0], basicComand))
			continue;

		if (instanceCommand[0] == "add" && instanceCommand.size() == 6) 
			addElem(instanceCommand, ourList);
		
		if (instanceCommand[0] == "done" && instanceCommand.size() == 2)
			markTaskDone(instanceCommand, ourList);

		if (instanceCommand[0] == "update" && instanceCommand.size() == 6)
			updateTask(instanceCommand, ourList);

		if (instanceCommand[0] == "delete" && instanceCommand.size() == 2)
			deleteTask(instanceCommand, ourList);

		printAll(ourList);
	}


	return false;
}

void printAll(unordered_map<string, Node> &map)
{
	unordered_map<string, Node>::iterator iter;  int i = 1;
	for (iter = map.begin(); iter != map.end(); iter++)
	{
		cout << i << ". " << iter->second.name << " "
			<< iter->second.deskription << " "
			<< iter->second.date << " "
			<< iter->second.category << " "
			<< iter->second.isComplete;
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

