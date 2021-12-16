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

map<string, long long> split(map<string, long long>& tuple_freqs, map<string, char>& rules)
{
    map<string, long long> tuple_freqs_new;
    for (auto const & it: tuple_freqs)
    {
        if (it.second == 0) continue;
        char new_char = rules[it.first];
        string str;
        str.push_back(it.first[0]);
        str.push_back(new_char);
        if (tuple_freqs_new.find(str) == tuple_freqs_new.end()) tuple_freqs_new[str] = 0;
        tuple_freqs_new[str]+=it.second;
        str.clear();
        str.push_back(new_char);
        str.push_back(it.first[1]);
        if (tuple_freqs_new.find(str) == tuple_freqs_new.end()) tuple_freqs_new[str] = 0;
        tuple_freqs_new[str] += it.second;
    }
    return tuple_freqs_new;
}

int main()
{
    fstream f;
    f.open("input14.txt", ios::in);
    string str;
    string polymer;
    getline(f, polymer);
    map<string, long long> tuple_freqs;
    for (int i = 0; i < polymer.size()-1; i++)
    {
        auto str_tuple = polymer.substr(i, 2);
        if (tuple_freqs.find(str_tuple) == tuple_freqs.end())
        {
            tuple_freqs[str_tuple] = 1;
        }
        else
        {
            tuple_freqs[str_tuple]++;
        }
    }

    getline(f, str); // blank

    // getting the rules
    map<string, char> rules;
    while(getline(f, str))
    {
        rules[str.substr(0, 2)] = str[6];
    }

    int N = 40;
    for (int i = 0; i< N; i++)
    {
        tuple_freqs = split(tuple_freqs, rules);
    }

    vector<long long> freqs(26, 0);
    freqs[polymer[0]-'A']++;
    freqs[polymer[polymer.size()-1]-'A']++;
    // finding frequencies
    for (auto const & it: tuple_freqs)
    {
        freqs[it.first[0]-'A']+=it.second;
        freqs[it.first[1]-'A']+=it.second;
    }

    sort(freqs.begin(), freqs.end());
    int ind = 0;
    while (freqs[ind] == 0) ind++;
    cout << (freqs[freqs.size()-1] - freqs[ind]) / 2 << endl;






}