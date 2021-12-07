// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
using namespace std;

vector<int> parse_nums(string str)
{
    string cur_num;
    vector<int> nums;
    for (auto c: str)
    {
        if (c==',')
        {
            nums.push_back(stoi(cur_num));
            cur_num.clear();
        }
        else
        {
            cur_num.push_back(c);
        }
    }
    nums.push_back(stoi(cur_num));
    return nums;
}


int main()
{
    fstream f;
    f.open("input7.txt", ios::in);
    string str;

    getline(f, str);
    auto nums = parse_nums(str);
    sort(nums.begin(), nums.end());
    int median = nums[nums.size() / 2];
    //cout << median << endl;
    int sum = 0;
    for (auto n:nums)
    {
        sum += abs(n-median);
    }
    //cout << sum << endl;

    // p2
    sum = 0;
    for (auto n:nums)
    {
        sum += n;
    }
    float N = (float)(nums.size());
    // the following is calculated bywriting out the formula and calculating derivatives.
    int pos = (int)(0.5 + 1.0 / N * ((float)sum));

    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    for (auto n:nums)
    {
        sum1 += abs(n-pos)*(abs(n-pos) + 1) / 2;
        sum2 += abs(n-pos-1)*(abs(n-pos-1) + 1) / 2;
        sum3 += abs(n-pos+1)*(abs(n-pos+1) + 1) / 2;
    }
    cout << min(min(sum1, sum2), sum3) << endl;
}