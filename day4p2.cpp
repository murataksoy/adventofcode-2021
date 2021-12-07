// to compile - g++
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <numeric>
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

    vector<bool> board_is_winner(boards.size(), false);
    for (auto& drawn_num: drawn_numbers)
    {
        for (int board_ind = 0; board_ind < boards.size(); board_ind++)
        {
            mark_board(boards[board_ind], drawn_num);
            if (is_board_winner(boards[board_ind]))
            {
                board_is_winner[board_ind] = true;
                int count = accumulate(board_is_winner.begin(), board_is_winner.end(), 0);
                if (count == board_is_winner.size())
                {
                    cout << calculate_score(boards[board_ind], drawn_num) << endl;
                    return 1;
                }
            }

        }

    }




}