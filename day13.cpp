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

vector<string> fold(vector<string> paper, char fold_axis, int fold_coord)
{
    int nx = paper[0].size();
    int ny = paper.size();
    if (fold_axis == 'x')
    {
        vector<string> paper_folded(ny, string(fold_coord, '.'));
        for (int y = 0; y < ny; y++)
        {
            // coping the same locations
            for (int x = 0; x < fold_coord; x++)
            {
                paper_folded[y][x] = paper[y][x];
            }
            // folding
            for (int x = fold_coord + 1; x < nx; x++)
            {
                if (paper[y][x] == '#')
                {
                    paper_folded[y][2 * fold_coord-x] = '#';
                }
            }
        }
        return paper_folded;
    }

    if (fold_axis == 'y')
    {
        vector<string> paper_folded(fold_coord, string(nx, '.'));
        for (int x = 0; x < nx; x++)
        {
            // coping the same locations
            for (int y = 0; y < fold_coord; y++)
            {
                paper_folded[y][x] = paper[y][x];
            }
            // folding
            for (int y = fold_coord + 1; y < ny; y++)
            {
                if (paper[y][x] == '#')
                {
                    paper_folded[2 * fold_coord-y][x] = '#';
                }
            }
        }
        return paper_folded;
    }

    // ERROR
    cout << "ERROR - unknown axis" << endl;
    return vector<string>(ny, string(nx, '.'));

}


int main()
{
    fstream f;
    f.open("input13.txt", ios::in);
    string str;

    char fold_axis;
    int fold_coord;
    vector<array<int, 2>> points;
    while(getline(f, str))
    {
        if (str.size() == 0)
        {
            getline(f, str);
            fold_axis = str[string("fold along ").size()];
            fold_coord = stoi(str.substr(string("fold along ").size() + 2, str.size()));
            cout << "fold along " << fold_axis << " by " << fold_coord << endl;
            break;
        }

        int comma_ind = str.find(",");
        int x = stoi(str.substr(0, comma_ind));
        int y = stoi(str.substr(comma_ind+1, str.size()));
        points.push_back({x, y});
    }

    int maxx = 0;
    int maxy = 0;
    for (auto point: points)
    {
        maxx = max(maxx, point[0]+1);
        maxy = max(maxy, point[1]+1);
    }
    cout << maxx << " " <<maxy << endl;

    vector<string> paper(maxy, string(maxx, '.'));

    for (auto point: points)
    {
        paper[point[1]][point[0]] = '#';
    }


    auto paper_folded = fold(paper, fold_axis, fold_coord);

    int count=0;
    for (auto line:paper_folded)
    {
        for (auto c:line)
        {
            if (c == '#') count++;
        }
    }
    cout << count << endl;




}