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
    int n = risk_map.size();
    if (x == n-1 and y == n-1) return total_risk[x][y];
    if (total_risk[n-1][n-1] != -1 and total_risk[x][y] >= total_risk[n-1][n-1]) return INT_MAX;

    int min_risk = INT_MAX;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 and dy != 0 or dx == 0 and dy == 0 ) continue;
            int x2 = x + dx;
            int y2 = y + dy;
            if (x2 < 0 or x2 >= n or y2 < 0 or y2 >= n) continue;
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
    int N = 5;
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

    // calculating the risk on a staircase
    int sum = 0;
    int n = risk_map_expanded.size();
    for (int i = 0; i < n; i++)
    {
        sum += risk_map_expanded[i][i];

        if (i+1 < risk_map_expanded.size()-1)
            sum += risk_map_expanded[i][i+1];
    }
    total_risk[n-1][n-1] = sum;


    cout << calc_risk(risk_map_expanded, total_risk, 0, 0) << endl;
}