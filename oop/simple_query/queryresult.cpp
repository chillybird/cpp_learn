#include "queryresult.h"

#include <iostream>
using std::ostream;

// 输出查询的结果
ostream& print(ostream& os, const QueryResult& qr)
{
	os << "The result of query '" << qr.sought << "' is:" << std::endl;
	// 查询结果为行号的set的共享指针
	for (const auto& index : *qr.lines)
		os << "\t(line " << index + 1 << " )" << *(qr.file->begin() + index) << std::endl;
	return os;
}

ostream& print(ostream& os, const QueryResult& qr, size_t head, size_t trail)
{
	if (head > trail)
	{
		os << "illegal range!" << std::endl;
		return os;
	}
	else
	{
		os << "The result of query '" << qr.sought << "' is:" << std::endl;
		for (const auto& index : *qr.lines)
			if (index + 1 >= head && index + 1 <= trail)
				os << "\t(line " << index + 1 << " )" << *(qr.file->begin() + index) << std::endl;
		return os;
	}
}
