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


int calc_risk(const vector<vector<int>>& risk_map, vector<vector<int>>& total_risk, int x, int y)
{
    if (x == risk_map.size()-1 and y == risk_map[0].size()-1) return total_risk[x][y];

    int min_risk = 1000000;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 and dy != 0 or dx == 0 and dy == 0) continue;
            int x2 = x + dx;
            int y2 = y + dy;
            if (x2 < 0 or x2 >= risk_map.size() or y2 < 0 or y2 >= risk_map[0].size()) continue;
            if (total_risk[x2][y2] == -1 or total_risk[x][y] + risk_map[x2][y2] < total_risk[x2][y2])
            {
                total_risk[x2][y2] = total_risk[x][y] + risk_map[x2][y2];
                min_risk = min(calc_risk(risk_map, total_risk, x2, y2), min_risk);
            }
        }
    }
    return min_risk;
}

int main()
{
    fstream f;
    f.open("input15.txt", ios::in);
    string str;
    vector<vector<int>> risk_map;
    while(getline(f, str))
    {
        vector<int> line;
        for (auto c:str) line.push_back(c-'0');
        risk_map.push_back(line);
    }


    // replicating risk_map for part 2
    int N = 1;
    vector<vector<int>> risk_map_expanded(risk_map.size() * N, vector<int>(risk_map[0].size() * N));
    for (int x = 0 ; x < risk_map.size(); x ++)
    {
        for (int y = 0 ; y < risk_map[0].size(); y++)
        {
            for (int i=0; i<N; i++)
            {
                for (int j=0; j<N; j++)
                {
                    int x2 = x + i * risk_map.size();
                    int y2 = y + j * risk_map[0].size();
                    risk_map_expanded[x2][y2] = (risk_map[x][y] + i + j - 1) % 9 + 1;
                }
            }
        }
    }

    vector<vector<int>> total_risk(
        risk_map_expanded.size(), vector<int>(risk_map_expanded[0].size(), -1));
    total_risk[0][0] = 0;

    cout << calc_risk(risk_map_expanded, total_risk, 0, 0) << endl;
}