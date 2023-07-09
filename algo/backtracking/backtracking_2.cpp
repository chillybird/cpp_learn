// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
// 九宫格键盘数字映射
#include <iostream>
#include <vector>

using namespace std;

vector<string> corr = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string> result;
string path;

void backtracking(string& digits, int index) {
    if (digits.size() == index)
    {
        result.push_back(path);   
        return;
    }

    string letters = corr[digits[index] - '0' - 2];
    for (int i = 0; i < letters.size(); i++)
    {
        path.push_back(letters[i]);
        backtracking(digits, index + 1);
        path.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    backtracking(digits, 0);
    return result;
}

int main()
{
    string digits = "23";
    vector<string> res = letterCombinations(digits);
    for (size_t i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    
    return 0;
}