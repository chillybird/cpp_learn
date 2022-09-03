#pragma once
#ifndef _QUERY_H_
#define _QUERY_H_

#include <ostream>
using std::ostream;

#include <memory>
using std::shared_ptr;

#include <string>
using std::string;

#include "query_base.h"
#include "queryresult.h"
#include "wordquery.h"

class TextQuery;

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const string&);
	// 虚调用
	QueryResult eval(const TextQuery& t) const { return q->eval(t); }
	string rep() const { return q->rep(); }
private:
	Query(shared_ptr<Query_Base> query) : q(query) {}
	shared_ptr<Query_Base> q;
};

// 使用inline避免了在链接时发生冲突
inline Query::Query(const string& s) : q(new WordQuery(s)) { }


#endif
