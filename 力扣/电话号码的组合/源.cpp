#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
string DIGITS = "";
unordered_map<char, string> phoneMap{
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
};
void process(string str, vector<string>& res)
{
    int len = str.length();
    if (len == DIGITS.size())
    {
        res.push_back(str);
        return;
    }
    for (auto& pm : phoneMap[DIGITS[len]])
    {
        string tmp = str;
        tmp.push_back(pm);
        process(tmp, res);
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> res;
    if (digits.empty()) {
        return res;
    }
    DIGITS = digits;
    process("", res);
    return res;
}

void nextPermutation(vector<int>& nums) {
    int len = nums.size();
    int last = len - 1;
    for (int i = len - 1; i > 0; --i)
    {
        if (nums[i] < nums[last])
        {
            int temp = nums[i];
            nums[i] = nums[last];
            nums[last] = temp;
        }
    }
}

int main()
{
    //auto rs = letterCombinations("23");
    vector<int> nums{ 1,2,3 };
    nextPermutation(nums);
	return 0;
}