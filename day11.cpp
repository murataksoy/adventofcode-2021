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

using namespace std;
int nflashes =0;
void increment(vector<string>& octos)
{
    for (auto& line : octos)
    {
        for (auto &c : line)
        {
            c++;
        }
    }
}

bool flash(vector<string>& octos)
{
    bool changed= false;
    for (int i = 0; i< octos.size(); i++)
    {
        for (int j = 0; j < octos[i].size(); j++)
        {
            if (octos[i][j] > '9')
            {
                nflashes++;
                octos[i][j] = '0';
                for (int k =i-1; k<=i+1; k++)
                {
                    for (int l = j-1; l<=j+1; l++)
                    {
                        if (k < 0 or k >= octos.size() or l < 0 or l >= octos[0].size())
                        {
                            continue;
                        }
                        if (octos[k][l] != '0') octos[k][l]++;
                        changed = true;
                    }
                }
            }
        }
    }
    return changed;
}

bool check_all_zero(const vector<string>& octos)
{
    for (auto& line : octos)
    {
        for (auto &c : line)
        {
            if (c != '0') return false;
        }
    }
    return true;
}

int main()
{
    fstream f;
    f.open("input11.txt", ios::in);
    string str;
    vector<string> octos;
    while(getline(f, str))
    {
        octos.push_back(str);
    }


    // part 1
    // for (int i = 0; i< 100; i++)
    // {
    //     increment(octos);
    //     while(flash(octos)) {};
    // }
    // cout << nflashes << endl;

    // part 2
    int step = 0;
    while(1)
    {
        increment(octos);
        step++;
        while(flash(octos))
        {
            if (check_all_zero(octos))
            {
                cout << "all flashed together " << step << endl;
                return 0;
            }
        };
    }

}