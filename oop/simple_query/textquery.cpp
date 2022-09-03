#include "textquery.h"

#include <sstream>

#include "queryresult.h"
using std::istringstream;

using std::make_shared;

// 将每个单个和标点符号的值和出现的行号记录在map中
TextQuery::TextQuery(ifstream& is) : file(new vector<string>)
{
	using std::getline;

	string text;
	while(getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;

		istringstream line(text);	// 输入字符串流会遇到空格会终止
		string word;
		while(line >> word)
		{
			auto p = handlePunct(word);
			for(auto w : *p)	// 解shared_ptr，得到vector
			{
				auto& lines = wm[w];	// 将string存放到set之中，并且引用值
				if (!lines)
					lines.reset(new set<line_no>);
				lines->insert(n);	// 插入行号
			}
		}
	}
}


// 查找单词出现或标点符号出现的位置
QueryResult TextQuery::query(const string& sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end()) // 没有查找到
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file); // second得到键值对的值
}


// 拆分单词和标点符号
shared_ptr<vector<string>> TextQuery::handlePunct(const string& s)
{
	shared_ptr<vector<string>> p = make_shared<vector<string>>();

	// 这里借用了快慢指针的思想，正常情况下index等于first，当遇到标点符号之后，index比first大1
	size_t first = 0, index = 0;
	while(index != s.size())
	{
		if (ispunct(s[index]))	// 是否是标点符号
		{
			string word = s.substr(first, index - first);
			if (!word.empty())
				p->push_back(word);
			p->push_back(s.substr(index, 1));
			++index;
			first = index;
		}
		else
		{
			++index;
		}
	}

	string trail = s.substr(first);		// 截取所有剩余的字符
	if (!trail.empty())
		p->push_back(trail);

	return p;
}

