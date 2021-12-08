// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
#include <set>
using namespace std;


int main()
{
    fstream f;
    f.open("input8.txt", ios::in);
    string str;

    vector<string> nums;
    while(getline(f, str))
    {
        int ind = 0;
        while (str[ind] != '|') ind ++;
        ind+=2;
        string cur_num;
        while(ind < str.size())
        {
            if (str[ind] == ' ')
            {
                nums.push_back(cur_num);
                cur_num.clear();
                ind++;
            }
            else
            {
                cur_num.push_back(str[ind]);
                ind++;
            }
        }
        nums.push_back(cur_num);
    }

    int count = 0;
    for (auto n:nums)
    {
        set<char> n_set;
        for (auto c:n) n_set.insert(c);
        if (n_set.size() == 2 or n_set.size() == 4 or n_set.size() == 3 or n_set.size() == 7)
        {
            count++;
        }

    }
    cout << count << endl;



}