#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

extern const vector<string> properSection;
extern const vector<string> properSign;

struct Node;

extern struct Expression {
	string sign;
	string valueRight;
	Expression(string sign, string valueRight)
	{
		this->sign;
		this->valueRight;
	}
	Expression()
	{}
};

bool LikeSearch(string command, Node exemp, string RightValue);
bool CompareForEqual(string command, string ValueRight, Node exemp);
bool compareDate(date dataIzTroiki, string sign, date dataIzNode);
bool isProperSection(string nameOfSection);
bool isProperSign(string sign);