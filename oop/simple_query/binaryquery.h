#pragma once

#ifndef _BINARY_QUERY_H_
#define _BINARY_QUERY_H_

#include <string>
using std::string;

#include "query.h"
#include "query_base.h"

class BinaryQuery : public Query_Base
{
protected:
	BinaryQuery(const Query&l, const Query &r, string s) : lhs(l), rhs(r), opSym((s)) {}
	string rep() const
	{
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
	}

	Query lhs, rhs;
	string opSym;
};

#endif

