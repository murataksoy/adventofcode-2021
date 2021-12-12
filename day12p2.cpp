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
#include <map>

using namespace std;

int npaths = 0;


array<string, 2> split_dash(string str)
{
    string str1;
    string str2;
    bool first_or_second = 0;
    for (auto c:str)
    {
        if (c == '-')
        {
            first_or_second = 1;
            continue;
        }
        if (first_or_second == 0) str1.push_back(c); else str2.push_back(c);
    }
    return {str1, str2};
}

void traverse(map<string, pair<vector<string>, int> > cave_map, string cur, bool small_visited_twice)
{
    // TODO is it possible to writ ethis function using a reference and backtracking?
    if (cur == "end")
    {
        npaths++;
        return;
    }
    // cannot visit start and end more than once
    if ((cur == "start" or cur == "end") and cave_map[cur].second == 1) return;
    // cannot visit any small cave more than twice
    if (cur[0] >= 'a' and cur[0] <= 'z' and cave_map[cur].second == 2 ) return;
    // can only visit a small cave twice only once
    if (cur[0] >= 'a' and cur[0] <= 'z' and cave_map[cur].second == 1 and small_visited_twice) return;
    if (cur[0] >= 'a' and cur[0] <= 'z' and cave_map[cur].second == 1) small_visited_twice = true;
    cave_map[cur].second++;

    for (auto next_cave: cave_map[cur].first)
    {
        traverse(cave_map, next_cave, small_visited_twice);
    }
}

int main()
{
    map<string, pair<vector<string>, int> > cave_map;
    fstream f;
    f.open("input12.txt", ios::in);
    string str;
    string name1, name2;
    while(getline(f, str))
    {
        tie(name1, name2) = split_dash(str);
        if (cave_map.find(name1) == cave_map.end()) cave_map[name1] = {vector<string>(), 0};
        if (cave_map.find(name2) == cave_map.end()) cave_map[name2] = {vector<string>(), 0};
        cave_map[name1].first.push_back(name2);
        cave_map[name2].first.push_back(name1);
    }
    traverse(cave_map, "start", false);
    cout << npaths << endl;
}