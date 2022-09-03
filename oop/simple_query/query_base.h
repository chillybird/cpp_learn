#pragma once
#ifndef _QUERY_BASE_H_
#define _QUERY_BASE_H_

#include <string>
using std::string;

#include "textquery.h"

class Query_Base
{
	// 使用Query类对query的方法进行隐藏
	friend class Query;
protected:
	// 供派生类进行调用
	using line_no = TextQuery::line_no;
	virtual ~Query_Base() = default;
private:
	// 供Query类进行调用
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;
};



#endif
