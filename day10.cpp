// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
#include <set>
#include <stack>
#include <utility>

using namespace std;


pair<int, stack<char>> find_first_illegal(string str)
{
    stack<char> chars;
    for (int i =0; i< str.size(); i++)
    {
        auto c = str[i];
        if (c == ')' and chars.top() != '(') return {i, chars};
        if (c == '}' and chars.top() != '{') return {i, chars};
        if (c == ']' and chars.top() != '[') return {i, chars};
        if (c == '>' and chars.top() != '<') return {i, chars};
        if (c == ')' or c == '}' or c == ']' or c == '>') chars.pop();
        else chars.push(c);
    }
    return {-1, chars};
}




int main()
{
    fstream f;
    f.open("input10.txt", ios::in);
    string str;

    int sum = 0;
    vector<long long> sump2;
    while(getline(f, str))
    {
        auto res = find_first_illegal(str);
        auto ind = res.first;
        auto chars = res.second;
        if (ind == -1)
        {
            long long sump2_line = 0;
            while (not chars.empty())
            {
                sump2_line *= 5;
                if (chars.top() == '(') sump2_line+= 1;
                if (chars.top() == '[') sump2_line+= 2;
                if (chars.top() == '{') sump2_line+= 3;
                if (chars.top() == '<') sump2_line+= 4;
                chars.pop();

            }
            sump2.push_back(sump2_line);
            continue;
        }
        if (str[ind] == ')') sum += 3;
        if (str[ind] == '}') sum += 1197;
        if (str[ind] == ']') sum += 57;
        if (str[ind] == '>') sum += 25137;
    }
    cout << sum << endl;
    sort(sump2.begin(), sump2.end());
    cout << sump2[sump2.size()/2] << endl;

}