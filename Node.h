
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::gregorian;
using namespace std;

extern struct Node {
	string name;
	string deskription;
	date data;
	string category;
	bool isComplete;


	Node(string name,
		string deskription,
		date date,
		string category,
		bool isComplete)
	{
		this->name = name;
		this->deskription = deskription;
		this->data = data;
		this->category = category;
		this->isComplete = isComplete;
	}
	Node() {};

};

extern const vector<string> basicComand;
extern const string errorNumberWord;
extern const string errorMissingTask;

void addElem(vector<string> instanceComand, unordered_map<string, Node>& ourList);
void deleteTask(vector<string> instanceComand, unordered_map<string, Node>& ourList);
void updateTask(vector<string> instanceComand, unordered_map<string, Node>& ourList);
void markTaskDone(vector<string> instanceComand, unordered_map<string, Node>& ourList);