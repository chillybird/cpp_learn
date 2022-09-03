#pragma once
#ifndef _OR_QUERY_H_
#define _OR_QUERY_H_

#include <memory>
using std::shared_ptr;

#include "query.h"
#include "binaryquery.h"

class QueryResult;
class TextQuery;

class OrQuery :public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|"){ }
	QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_Base>(new OrQuery(lhs, rhs));

}

#endif
