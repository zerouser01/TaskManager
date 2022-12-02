#pragma once
#include <string>
using namespace std;

vector<string> basicComand = { "add", "done", "update", "delete", "select" };
string errorNumberWord = "некорректное количество слов после введенной Вами команды\n";
string errorMissingTask = "не смогли найти такую запись";

struct Node {
	string name;
	string deskription;
	string date;
	string category;
	bool isComplete;


	Node(string name,
		string deskription,
		string date,
		string category,
		bool isComplete)
	{
		this->name = name;
		this->deskription = deskription;
		this->date = date;
		this->category = category;
		this->isComplete = isComplete;
	}
	Node(){};

};



void addElem(vector<string> instanceComand, unordered_map<string, Node>& ourList)
{
	if (instanceComand.size() != 6)
	{
		cout << errorNumberWord;
		return;
	}
	Node instanceNode;
	instanceNode.name = instanceComand[1];
	instanceNode.deskription = instanceComand[2];
	instanceNode.date = instanceComand[3];
	instanceNode.category = instanceComand[4];
	instanceComand[5] == "yes" ? instanceNode.isComplete = true : instanceNode.isComplete = false;
	ourList.insert({ instanceComand[1], instanceNode });
}

void markTaskDone(vector<string> instanceComand, unordered_map<string, Node>& ourList)
{
	unordered_map<string, Node>::iterator iter;

	if (instanceComand.size() != 2)
	{
		cout << errorNumberWord;
		return;
	}
	
	iter =  ourList.find(instanceComand[1]);
	if (iter != ourList.end())
	{
		iter->second.isComplete = true;
	}
	cout << " " << "done\n";
}

void updateTask(vector<string> instanceComand, unordered_map<string, Node>& ourList)
{
	unordered_map<string, Node>::iterator iter;
	if (instanceComand.size() != 6)
	{
		cout << errorNumberWord;
		return;
	}
	iter = ourList.find(instanceComand[1]);
	if (iter != ourList.end())
	{
		iter->second.deskription = instanceComand[2];
		iter->second.date = instanceComand[3];
		iter->second.category = instanceComand[4];
		instanceComand[5] == "yes" ? iter->second.isComplete = true : iter->second.isComplete = false;
	}
	else cout << errorMissingTask;
}

void deleteTask(vector<string> instanceComand, unordered_map<string, Node>& ourList)
{
	unordered_map<string, Node>::iterator iter;
	if (instanceComand.size() != 2)
	{
		cout << errorNumberWord;
		return;
	}
	iter = ourList.find(instanceComand[1]);
	if (iter != ourList.end())
	{
		ourList.erase(iter);
	}
	else cout << errorMissingTask;
}