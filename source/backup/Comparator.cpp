#include <map>
#include <string>

using std::multimap;
using std::string;


struct Expression {
	string sign;
	string valueRight;
};
multimap<string, Expression> terms;

