#include <iostream>
using std::cout; using std::cin; using std::endl;

#include <fstream>
using std::ifstream;
using std::ostream;

#include "queryresult.h"
#include "textquery.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"
#include "notquery.h"

int main()
{
	ifstream fin("rsc/test.txt");
	TextQuery text(fin);

	auto res = text.query("her");
	print(cout, res);

	auto q = ~Query("Alice");

	auto result = q.eval(text);
	print(cout, result);
	cout << endl;
	print(cout, result, -3, 5);
	cout << endl;
	print(cout, result, 3, 5);
	cout << endl;
	print(cout, result, 3, 20);
	cout << endl;

	return 0;
}

