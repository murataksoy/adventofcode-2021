// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
using namespace std;


vector<int> parse_numbers(string str, char delim)
{
    vector<int> numbers;
    string cur_num;
    for (auto c:str)
    {
        if (c==delim)
        {
            if (cur_num.size() > 0)
            {
                numbers.push_back(stoi(cur_num));
                cur_num.clear();
            }
        }
        else
        {
            cur_num.push_back(c);
        }
    }
    if (cur_num.size() > 0)
    {
        numbers.push_back(stoi(cur_num));
    }
    return numbers;
}

bool is_board_winner(vector<vector<int>> board)
{
    int n = board[0].size();
    for (int i=0;i<n;i++)
    {
        bool is_winner = true;
        for (int j=0;j<n;j++)
        {
            if (board[i][j] != 'X')
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner) return true;
    }

    for (int i=0;i<n;i++)
    {
        bool is_winner = true;
        for (int j=0;j<n;j++)
        {
            if (board[j][i] != 'X')
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner) return true;
    }
    return false;

}

void mark_board(vector<vector<int>>& board, int drawn_num)
{
    int n = board[0].size();
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (board[i][j] == drawn_num) board[i][j] = 'X';
        }
    }
}

int calculate_score(vector<vector<int>>& board, int drawn_num)
{
    int n = board[0].size();
    int sum = 0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (board[i][j] != 'X')
            {
                sum += board[i][j];
            }
        }
    }
    return sum * drawn_num;
}

int main()
{
    fstream f;
    f.open("input4.txt", ios::in);
    string str;
    vector<int> drawn_numbers;

    // Getting the numbers drawn
    getline(f, str);
    drawn_numbers = parse_numbers(str, ',');
    int n = 5;
    // for (auto drawn_num: drawn_numbers)
    // {
    //     cout << drawn_num << " ";
    // }
    // cout << endl;

    // Getting all the boards
    vector<vector<vector<int>>> boards;
    vector<vector<int>> cur_board;
    while(getline(f, str))
    {
        if (str.size() == 0)
        {
            if (cur_board.size() > 0)
            {
                boards.push_back(cur_board);
                cur_board.clear();
            }
            continue;
        }
        auto line = parse_numbers(str, ' ');
        cur_board.push_back(line);
    }
    boards.push_back(cur_board);


    for (auto& drawn_num: drawn_numbers)
    {
        for (auto& board: boards)
        {
            mark_board(board, drawn_num);
            if (is_board_winner(board))
            {
                cout << calculate_score(board, drawn_num) << endl;
                return 0;
            }
        }
    }




}