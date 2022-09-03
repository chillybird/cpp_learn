#include "query.h"

#include <iostream>
using std::ostream;

ostream& operator<<(ostream& os, const Query& query)
{
	return os << query.rep();
}