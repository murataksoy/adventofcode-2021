// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
using namespace std;

int find_space(string str)
{
    int pos=0;
    while (str[pos] != ' ')
    {
        pos++;
    }
    return pos;
}

int main()
{
    // part 1
    // fstream f;
    // f.open("input2.txt", ios::in);
    // string str;
    // int hor_pos = 0;
    // int depth = 0;
    // while(getline(f, str))
    // {
    //     int str_pos = find_space(str);
    //     string command = str.substr(0, str_pos);
    //     int num = stoi(str.substr(str_pos+1));
    //     if (command == "forward") hor_pos += num;
    //     else if (command == "down") depth += num;
    //     else if (command == "up") depth -= num;
    // }
    // cout << depth * hor_pos << endl;

    // part 2
    fstream f;
    f.open("input2.txt", ios::in);
    string str;
    int hor_pos = 0;
    int aim = 0;
    int depth = 0;
    while(getline(f, str))
    {
        int str_pos = find_space(str);
        string command = str.substr(0, str_pos);
        int num = stoi(str.substr(str_pos+1));
        if (command == "forward")
        {
            hor_pos += num;
            depth += aim * num;
        }
        else if (command == "down") aim += num;
        else if (command == "up") aim -= num;
    }
    cout << depth * hor_pos << endl;


}