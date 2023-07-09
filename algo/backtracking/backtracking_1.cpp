// 找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
// 说明：
// 所有数字都是正整数。
// 解集不能包含重复的组合。
// 示例 1: 输入: k = 3, n = 7 输出: [[1,2,4]]
// 示例 2: 输入: k = 3, n = 9 输出: [[1,2,6], [1,3,5], [2,3,4]]

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> result;
vector<int> path;

int count = 0;

void backtracking(int targetSum, int k, int sum, int startIndex) {
    if (sum > targetSum)
        return;
    if (path.size() == k)
    {
        if(sum == targetSum)
            result.push_back(path);
        return;
    }
    for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++)
    {
        path.push_back(i);
        sum += i;
        backtracking(targetSum, k, sum, i + 1);
        sum -= i;
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int k)
{
    backtracking(n, k, 0, 1);
    return result;
}

int main()
{
    combine(5, 2);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
        
    }
    return 0;
}