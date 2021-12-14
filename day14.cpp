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

string pair_insertion(string polymer, map<string, char> rules)
{
    int n = polymer.size();
    string polymer_inserted;
    for (int i = 0; i< n-1;i++)
    {

        polymer_inserted.push_back(polymer[i]);
        string rule_key = polymer.substr(i, 2);
        polymer_inserted.push_back(rules[rule_key]);

    }
    polymer_inserted.push_back(polymer[n-1]);
    return polymer_inserted;
}

vector<int> find_occurrence(string str)
{
    vector<int> occurrences(26, 0);
    for (auto c: str)
    {
        occurrences[c-'A']++;
    }
    return occurrences;

}

int main()
{
    fstream f;
    f.open("input14.txt", ios::in);
    string str;
    string polymer;
    getline(f, polymer);
    getline(f, str);
    map<string, char> rules;
    while(getline(f, str))
    {
        rules[str.substr(0, 2)] = str[6];
    }

    for (int i=0;i<10;i++)
    {
        cout << i << endl;
        polymer = pair_insertion(polymer, rules);
        //cout << polymer << endl;
    }

    auto occurrences = find_occurrence(polymer);
    sort(occurrences.begin(), occurrences.end());
    int ind = 0;
    while(occurrences[ind] == 0) ind++;
    cout << occurrences[occurrences.size()-1] - occurrences[ind] << endl;




}