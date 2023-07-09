#include <iostream>
#include <vector>

using namespace std;

// https://www.programmercarl.com/0027.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0.html

int removeElement(vector<int> &nums, int val)
{
    int slowIndex = 0;
    for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++)
    {
        if (val != nums[fastIndex])
        {
            nums[slowIndex++] = nums[fastIndex];
        }
    }
    return slowIndex;
}

void print_nums(vector<int> &nums)
{
    for (int num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    print_nums(nums);
    removeElement(nums, 3);
    print_nums(nums);
    return 0;
}