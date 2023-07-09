#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> result;
vector<int> path;
vector<bool> used;

void backtracking(int index, int n)
{
    if (index > n)
    {
        result.push_back(path);
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            used[i] = true;
            path.push_back(i);
            backtracking(index + 1, n);
            path.pop_back();
            used[i] = false;
        }

    }
}

vector<vector<int>> generatePermutations(int n)
{
    used = vector<bool>(n + 1, false);
    backtracking(1, n);

    return result;
}

void traverseVector(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    traverseVector(generatePermutations(4));
    return 0;
}