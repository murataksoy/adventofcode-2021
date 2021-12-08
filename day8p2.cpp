// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
#include <set>
#include <numeric>
#include <algorithm>
using namespace std;


array<vector<string>, 2> parse_single_line(string str)
{
    int ind = 0;
    bool before_delim = true;
    vector<string> nums_before_delim;
    vector<string> nums_after_delim;
    string cur_num;
    while(ind < str.size())
    {
        if (str[ind] == '|' )
        {
            ind += 2;
            before_delim = false;
            continue;
        }
        if (str[ind] == ' ' )
        {
            if (before_delim) nums_before_delim.push_back(cur_num);
            else nums_after_delim.push_back(cur_num);
            cur_num.clear();
            ind++;
            continue;
        }
        cur_num.push_back(str[ind]);
        ind++;
    }
    nums_after_delim.push_back(cur_num);
    return {nums_before_delim, nums_after_delim };
}


int find_number(string str, vector<int> mapping)
{
    vector<bool> num(7, false);
    for (auto c:str)
    {
        num[mapping[c-'a']] = true;
    }

    if ( num[0] and  num[1] and  num[2] and !num[3] and  num[4] and  num[5] and  num[6]) return 0;
    if (!num[0] and !num[1] and  num[2] and !num[3] and !num[4] and  num[5] and !num[6]) return 1;
    if ( num[0] and !num[1] and  num[2] and  num[3] and  num[4] and !num[5] and  num[6]) return 2;
    if ( num[0] and !num[1] and  num[2] and  num[3] and !num[4] and  num[5] and  num[6]) return 3;
    if (!num[0] and  num[1] and  num[2] and  num[3] and !num[4] and  num[5] and !num[6]) return 4;
    if ( num[0] and  num[1] and !num[2] and  num[3] and !num[4] and  num[5] and  num[6]) return 5;
    if ( num[0] and  num[1] and !num[2] and  num[3] and  num[4] and  num[5] and  num[6]) return 6;
    if ( num[0] and !num[1] and  num[2] and !num[3] and !num[4] and  num[5] and !num[6]) return 7;
    if ( num[0] and  num[1] and  num[2] and  num[3] and  num[4] and  num[5] and  num[6]) return 8;
    if ( num[0] and  num[1] and  num[2] and  num[3] and !num[4] and  num[5] and  num[6]) return 9;
    return -1;

}

int main()
{
    fstream f;
    f.open("input8.txt", ios::in);
    string str;

    vector<array<vector<string>, 2>> nums;
    while(getline(f, str)) nums.push_back(parse_single_line(str));
    int sum = 0;


    for (auto entry:nums)
    {

        int n_mappings = 0;
        vector<int> mapping = {0,1,2,3,4,5,6};
        do
        {
            bool found = true;
            for (auto n:entry[0])
            {
                if (find_number(n, mapping)==-1)
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                int mul = 1000;
                for (auto n:entry[1])
                {
                    sum += find_number(n, mapping) * mul;
                    mul /= 10;
                }
                break;
            }
        }
        while(std::next_permutation(mapping.begin(), mapping.end()));
    }
    cout << sum << endl;
}