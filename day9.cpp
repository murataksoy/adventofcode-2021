// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
#include <set>
using namespace std;

void expand(vector<vector<int>>& basin, const vector<vector<int>>& heights, int i, int j)
{
    if (basin[i][j] == 0) return;
    if (i > 0 and heights[i-1][j] > heights[i][j] and basin[i-1][j] == 0 and heights[i-1][j] != 9)
    {
        basin[i-1][j] = 1;
        expand(basin, heights, i-1, j);
    }
    if (i < heights.size()-1 and heights[i+1][j] > heights[i][j] and basin[i+1][j] == 0 and heights[i+1][j] != 9)
    {
        basin[i+1][j] = 1;
        expand(basin, heights, i+1, j);
    }
    if (j > 0 and heights[i][j-1] > heights[i][j]  and basin[i][j-1] == 0 and heights[i][j-1] != 9)
    {
        basin[i][j-1] = 1;
        expand(basin, heights, i, j-1);
    }
    if (j < heights[0].size()-1 and heights[i][j+1] > heights[i][j] and basin[i][j+1] == 0 and heights[i][j+1] != 9)
    {
        basin[i][j+1] = 1;
        expand(basin, heights, i, j+1);
    }
}


int calc_basin_area(const vector<vector<int>>& heights, int i, int j)
{
    vector<vector<int>> basin(heights.size(), vector<int>(heights[0].size(), 0));
    basin[i][j] = 1;
    expand(basin, heights, i, j);
    int area = 0;
    for (int i = 0; i< heights.size(); i++)
    {
        for (int j = 0; j< heights[0].size(); j++)
        {
            area += basin[i][j];
        }
    }
    cout << "area " << area << endl;
    return area;
}


int main()
{
    fstream f;
    f.open("input9.txt", ios::in);
    string str;

    vector<vector<int>> heights;
    vector<int> height;
    while(getline(f, str))
    {
        height.resize(str.size(), 0);
        for (int i=0;i<str.size();i++)
        {
            height[i] = (int)(str[i] - '0');
        }
        heights.push_back(height);
    }
    int N = heights.size();
    int M = heights[0].size();
    int sum = 0;
    vector<array<int, 2>> coords;
    for (int i =0; i< N ; i++)
    {
        for (int j =0; j< M ; j++)
        {
            if ( (i == 0 or heights[i][j] < heights[i-1][j]) and
                 (i == N-1 or heights[i][j] < heights[i+1][j]) and
                 (j == 0 or heights[i][j] < heights[i][j-1]) and
                 (j == M-1 or heights[i][j] < heights[i][j+1]) )
            {
                coords.push_back({i, j});
                sum += (heights[i][j] + 1);
            }

        }
    }
    cout << sum << endl;

    // part 2 - for every low point, finding the basin size;
    vector<int> areas;
    for (auto coord : coords)
    {
        areas.push_back(calc_basin_area(heights, coord[0], coord[1]));
    }
    sort(areas.begin(), areas.end());
    int prod = 1;
    for (int i = 0; i< 3; i++) prod *= areas[areas.size() - i - 1];
    cout << prod << endl;
}