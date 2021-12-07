// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
#include <numeric>
using namespace std;

vector<long long> parse_fish(string str)
{
    string cur_fish;
    vector<long long> fishes;
    vector<long long> fish_map(9, 0);
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
    for (auto fish:fishes)
    {
        fish_map[fish]++;
    }

    return fish_map;
}

//vector<long long> grow(vector<long long>& fish_map)
vector<long long> grow(vector<long long>& fish_map)
{
    vector<long long> fish_map_new(9, 0);
    fish_map_new[8] = fish_map[0];
    fish_map_new[7] = fish_map[8];
    fish_map_new[6] = fish_map[0] + fish_map[7];
    fish_map_new[5] = fish_map[6];
    fish_map_new[4] = fish_map[5];
    fish_map_new[3] = fish_map[4];
    fish_map_new[2] = fish_map[3];
    fish_map_new[1] = fish_map[2];
    fish_map_new[0] = fish_map[1];
    return fish_map_new;
}

int main()
{
    fstream f;
    f.open("input6.txt", ios::in);
    string str;

    getline(f, str);
    vector<long long> fishes = parse_fish(str);
    for (auto fish:fishes) cout << fish << " ";
    for (int i=0;i<256;i++)
    {
        fishes = grow(fishes);
    }
    cout << accumulate(fishes.begin(), fishes.end(), (long long)0) << endl;;



}