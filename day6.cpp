// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
using namespace std;

vector<int> parse_fish(string str)
{
    string cur_fish;
    vector<int> fishes;
    for (auto c: str)
    {
        if (c==',')
        {
            fishes.push_back(stoi(cur_fish));
            cur_fish.clear();
        }
        else
        {
            cur_fish.push_back(c);
        }
    }
    fishes.push_back(stoi(cur_fish));
    return fishes;
}

vector<int> grow(vector<int>& fishes)
{
    vector<int> new_fishes;
    for (auto & fish: fishes)
    {
        if (fish == 0)
        {
            new_fishes.push_back(6);
            new_fishes.push_back(8);
        }
        else
        {
            new_fishes.push_back(fish-1);
        }
    }
    return new_fishes;
}

int main()
{
    fstream f;
    f.open("input6.txt", ios::in);
    string str;

    getline(f, str);
    vector<int> fishes = parse_fish(str);
    for (auto fish:fishes) cout << fish << " ";
    for (int i=0;i<80;i++)
    {
        fishes = grow(fishes);
    }
    cout << fishes.size() << endl;



}