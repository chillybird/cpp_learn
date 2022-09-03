#pragma once
#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_

#include <fstream>
using std::ifstream;

#include <memory>
using std::shared_ptr;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <map>
using std::map;

#include <set>
using std::set;

class QueryResult;

class TextQuery
{
public:
	typedef vector<string>::size_type line_no;	// size_type 是vector的size()返回值的类型

	TextQuery(ifstream&);
	QueryResult query(const string&) const;

private:
	shared_ptr<vector<string>> file;	// 按行记录文件的内容
	map<string, shared_ptr<set<line_no>>> wm;	// 记录单词和标点符号出现的行号

	shared_ptr<vector<string>> handlePunct(const string&);
};

#endif
