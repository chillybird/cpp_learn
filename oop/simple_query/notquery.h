#pragma once
#ifndef _NOT_QUERY_H_
#define _NOT_QUERY_H_
#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "query.h"
#include "query_base.h"

// 提前声明类
class QueryResult;
class TextQuery;

class NotQuery:public Query_Base
{
	// NotQuery类的成员的访问方法都是private，只能通过友元来进行访问
	friend Query operator~(const Query&);
	NotQuery(const Query& q) : query(q) {}
	string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;
	Query query;
};

inline Query operator~(const Query& oprand)
{
	return shared_ptr<Query_Base>(new NotQuery(oprand));
}

#endif

