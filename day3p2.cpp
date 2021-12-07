// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;

string find_most_common(const vector<string>& numbers)
{
    int n = numbers[0].size();
    vector<int> zeros(n);
    vector<int> ones(n);
    string most_common(n, 'a');
    for (auto num: numbers)
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == '0') zeros[i]++;
            else ones[i]++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (ones[i] >= zeros[i]) most_common[i] = '1';
        else most_common[i] = '0';
    }
    return most_common;
}

vector<string> eliminate_numbers(const vector<string>& numbers, string most_common, int bitn, string ogr_or_csr)
{
    vector<string> filtered_numbers;
    int n = numbers[0].size();
    for (auto num: numbers)
    {
        if (ogr_or_csr == "ogr" and num[bitn] == most_common[bitn] or ogr_or_csr == "csr" and num[bitn] != most_common[bitn])
        {
            filtered_numbers.push_back(num);
        }
    }
    return filtered_numbers;
}

int str2dec(string num)
{
    int mul = 1;
    int num_dec = 0;
    for (int i = num.size() - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            num_dec += mul;
        mul *= 2;
    }
    return num_dec;
}

int filter_and_convert(const vector<string>& numbers, string ogr_or_csr)
{
    vector<string> filtered_numbers = numbers;
    int bitn = 0;
    while(filtered_numbers.size() > 1)
    {
        string most_common = find_most_common(filtered_numbers);
        filtered_numbers = eliminate_numbers(filtered_numbers, most_common, bitn, ogr_or_csr);
        bitn++;
    }
    return str2dec(filtered_numbers[0]);
}

int main()
{
    fstream f;
    f.open("input3.txt", ios::in);
    string str;

    vector<string> numbers;

    while(getline(f, str))
    {
        numbers.push_back(str);
    }

    int ogr = filter_and_convert(numbers, "ogr");
    int csr = filter_and_convert(numbers, "csr");
    cout << ogr * csr << endl;

}