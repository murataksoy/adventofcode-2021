// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;

int main()
{
    fstream f;
    f.open("input3.txt", ios::in);
    string str;
    // manually entering the number of digits
    int n = 12;
    vector<int> ones(n);
    vector<int> zeros(n);
    while(getline(f, str))
    {
        for (int i = 0; i < n; i++)
        {
            if (str[i] == '0') zeros[i]++;
            else ones[i]++;
        }
    }

    int gamma = 0;
    int epsilon = 0;
    int mul = 1;
    for (int i = n-1; i >= 0; i--)
    {
        if (ones[i] > zeros[i])
        {
            epsilon += mul;
        }
        else if (ones[i] < zeros[i])
        {
            gamma += mul;
        }
        mul *= 2;
    }
    cout << gamma * epsilon << endl;
}