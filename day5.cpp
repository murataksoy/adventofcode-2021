// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <array>
using namespace std;

array<array<int, 2>, 2> parse_coords(string str)
{
    string cur_num;
    int char_ind = 0;

    int x1, y1, x2, y2;

    while(str[char_ind] != ',')
    {
        cur_num.push_back(str[char_ind]);
        char_ind++;
    }
    x1 = stoi(cur_num);
    char_ind++;
    cur_num.clear();

    while(str[char_ind] != ' ')
    {
        cur_num.push_back(str[char_ind]);
        char_ind++;
    }
    y1 = stoi(cur_num);
    char_ind+=4;
    cur_num.clear();


    while(str[char_ind] != ',')
    {
        cur_num.push_back(str[char_ind]);
        char_ind++;
    }
    x2 = stoi(cur_num);
    cur_num.clear();
    char_ind++;

    while(char_ind < str.size())
    {
        cur_num.push_back(str[char_ind]);
        char_ind++;
    }
    y2 = stoi(cur_num);

    return array<array<int, 2>, 2> ({ array<int, 2>({x1, y1}), array<int, 2>({x2, y2}) });

}

int main()
{
    fstream f;
    f.open("input5.txt", ios::in);
    string str;
    vector<array<array<int, 2>, 2>> coords;

    while(getline(f, str))
    {
        coords.push_back(parse_coords(str));
    }

    int max_coord = 0;
    for (auto coord:coords)
    {
        max_coord = max(max_coord, coord[0][0]);
        max_coord = max(max_coord, coord[1][0]);
        max_coord = max(max_coord, coord[0][1]);
        max_coord = max(max_coord, coord[1][1]);
    }
    int n = max_coord+1;

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (auto coord:coords)
    {
        if (coord[0][0] == coord[1][0])
        {
            int lower = min(coord[0][1], coord[1][1]);
            int upper = max(coord[0][1], coord[1][1]);
            for (int i=lower; i <= upper;i++)
            {
                matrix[coord[0][0]][i]++;
            }
        }
        else if (coord[0][1] == coord[1][1])
        {
            int lower = min(coord[0][0], coord[1][0]);
            int upper = max(coord[0][0], coord[1][0]);
            for (int i=lower; i <= upper;i++)
            {
                matrix[i][coord[0][1]]++;
            }
        }

        // part 2
        else if (abs(coord[0][0] - coord[1][0]) == abs(coord[0][1] - coord[1][1]))
        {
            int inc_x, inc_y;
            if (coord[0][0] < coord[1][0]) inc_x = 1; else inc_x = -1;
            if (coord[0][1] < coord[1][1]) inc_y = 1; else inc_y = -1;

            int diff = abs(coord[0][0] - coord[1][0]);
            for (int i=0; i <= diff;i++)
            {
                matrix[coord[0][0]+inc_x * i][coord[0][1]+i * inc_y]++;
            }
        }

    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] >=2) count++;
        }
    }
    cout << count << endl;

}