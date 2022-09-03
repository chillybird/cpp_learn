#pragma once

#ifndef _AND_QUERY_H_
#define _AND_QUERY_H_

#include <memory>
using std::shared_ptr;

#include "query.h"
#include "binaryquery.h"

class QueryResult;
class TextQuery;

class AndQuery:public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	// 调用基类的构造函数进行初始化
	AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}
	QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query& lhs, const Query &rhs)
{
	return shared_ptr<Query_Base>(new AndQuery(lhs, rhs));
}

#endif
