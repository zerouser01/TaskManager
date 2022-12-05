#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Node.h"

using namespace std;
using namespace boost::gregorian;

extern struct Node;
static vector<string> properSection = { "name", "description", "date", "category", "status" };
static vector<string> properSign = { "<", ">", "=", "like" };


bool isProperSection(string nameOfSection)
{
	for (const string& elem : properSection)
		if (elem == nameOfSection) return true;
	return false;
}
bool isProperSign(string sign)
{
	for (const string& elem : properSign)
		if (elem == sign) return true;
	return false;
}
struct Expression {
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

bool LikeSearch(string command, Node exemp, string RightValue)
{
	//������������ "contains" ������, � ����
	if (command == "name")
		if (exemp.name.find(RightValue) != std::string::npos)
			return true; else return false;
	if (command == "description")
		if (exemp.deskription.find(RightValue) != std::string::npos)
			return true; else return false;
	if (command == "category")
		if (exemp.category.find(RightValue) != std::string::npos)
			return true; else return false;
	if (command == "date" || command == "status")
		throw "������ ��������� � ���� � ������� - ������!";
}

//������ �������: ���� ���� ��������� ����� ������ ����� ��������� � ������� � Node - ��� ������.
bool CompareForEqual(string command, string ValueRight, Node exemp)
{
	if (command == "date")
		if (from_uk_string(ValueRight) == exemp.data)
			return true; else return false;
	if (command == "name")
		if (ValueRight == exemp.name)
			return true; else return false;
	if (command == "description")
		if (ValueRight == exemp.deskription)
			return true; else return false;
	if (command == "category")
		if (ValueRight == exemp.category)
			return true; else return false;
	if (command == "status")
		if (ValueRight == "ok" || ValueRight == "done" || ValueRight == "yes" || ValueRight == "1")
			if (exemp.isComplete) return true;
			else return false;
}

//���������� true, ���� ���� � ���� ������, false ���� ������
bool compareDate(date dataIzTroiki, string sign, date dataIzNode)
{
	//���������, ���� ��������. sign ��������� �� ������� char � ������������ switch
	//�� �� ������� ���������� ������ ���� ��� like. �������, ��� ����� 4 ��������
	if (sign == "<" && dataIzNode > dataIzTroiki) return true;
	else if (sign == "<" && dataIzTroiki > dataIzNode) return false;
	if (sign == ">" && dataIzTroiki < dataIzNode) return true;
	else if (sign == ">" && dataIzNode < dataIzTroiki) return false;
}