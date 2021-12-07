// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
using namespace std;
int main()
{
    fstream f;
    f.open("input1.txt", ios::in);
    string str;
    int count = 0;
    deque<int> depths;
    // get the first 4 depths
    for (int i = 0; i < 3; i++)
    {
        getline(f, str);
        depths.push_back(stoi(str));
    }
    while(getline(f, str))
    {
        depths.push_back(stoi(str));
        if (depths.back() > depths.front()) count++;
        depths.pop_front();
    }
    cout << count << endl;
}