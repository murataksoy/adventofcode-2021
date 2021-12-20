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
#include <bitset>
#include <iostream>
#include <sstream>
#include <assert.h>

using namespace std;

#define REGULAR_NUMBER 0
#define PAIR 1
#define LEFT 0
#define RIGHT 1

typedef struct number
{
    int type;
    int value = -1;
    number* number1;
    number* number2;
    number * parent;
} number;

number * string_to_num(const string& str)
{
    // checking if this is a regular number or another pair
    if (str[0] != '[')
    {
        // this is a real number
        number * num = new number;
        num->type = REGULAR_NUMBER;
        num->value = str[0] - '0';
        return num;
    }

    // this is a pair
    // finding the comma seperator
    int brackets = 0;
    int comma_ind = -1;
    for (int i = 1; i < str.size() - 1; i++)
    {
        // comma seperator happens when the bracket numbers are balanced.
        if (str[i] == ',' and brackets == 0)
        {
            comma_ind = i;
            break;
        }
        if (str[i] == '[') brackets++;
        else if (str[i] == ']') brackets--;
    }

    assert(comma_ind != -1);

    number * num = new number;
    num->type = PAIR;
    num->number1 = string_to_num(str.substr(1, comma_ind-1));
    num->number1->parent = num;
    num->number2 = string_to_num(str.substr(comma_ind + 1, str.size() - comma_ind - 2));
    num->number2->parent = num;
    return num;
}

string num_to_string(number * num)
{
    string str;
    if (num->type == REGULAR_NUMBER)
    {
        str += to_string(num->value);
    }
    else
    {
        str += "[";
        str += num_to_string(num->number1);
        str += ",";
        str += num_to_string(num->number2);
        str +=  "]";
    }
    return str;
}

number * find_depth(number * num, int depth)
{
    if (num == NULL) return NULL;
    if (num->type == REGULAR_NUMBER)
    {
        // We don't want any regular number while searching for the >4 depth
        return NULL;
    }
    if (depth <= 0 and num->number1->type == REGULAR_NUMBER and num->number2->type == REGULAR_NUMBER)
    {
        // we found the first pair at depth 4 whose both components are regular numbers.
        return num;
    }

    // otherwise, keep searching through the components of the number
    number * res = find_depth(num->number1, depth-1);
    if (res == NULL) res = find_depth(num->number2, depth-1);
    return res;
}



void find_neigh_right(number * num, number * orig, bool& found, number *& res)
{
    if (res != NULL) return; // we have already found the neighbor
    if (num->type == REGULAR_NUMBER)
    {
        if (found and num != orig)
        {
            res = num; // found what we are looking for
        }
        if (num == orig)
        {
            assert(found == false);
            found = true;
        }
    }
    else
    {
        find_neigh_right(num->number1, orig, found, res);
        find_neigh_right(num->number2, orig, found, res);
    }
}

void find_neigh_left(number * num, number * orig, bool& found, number *& res)
{
    if (found) return; // we have already found the neighbor
    if (num->type == REGULAR_NUMBER)
    {
        if (num == orig)
        {
            assert(found == false); // found what we are looking for
            found = true;
        }

        if (not found and num != orig)
        {
            res = num;
        }

    }
    else
    {
        find_neigh_left(num->number1, orig, found, res);
        find_neigh_left(num->number2, orig, found, res);
    }
}

bool explode(number * num)
{
    bool num_changed = false;

    bool found = false;
    number * neigh = NULL;

    number * num_to_explode = find_depth(num, 4);
    if (num_to_explode == NULL) return false;
    //cout << "num_to_explode " << num_to_explode->number1->value << " " << num_to_explode->number2->value << endl;

    // looking at the right side of the second number
    found = false;
    neigh = NULL;
    find_neigh_right(num, num_to_explode->number2, found, neigh);
    if (neigh != NULL)
    {
        neigh->value += num_to_explode->number2->value;
        num_changed = true;
    }

    // looking at the left side of the first number
    found = false;
    neigh = NULL;
    find_neigh_left(num, num_to_explode->number1, found, neigh);
    if (neigh != NULL)
    {
        neigh->value += num_to_explode->number1->value;
        num_changed = true;
    }

    // replacing with 0
    num_to_explode->type = REGULAR_NUMBER;
    num_to_explode->value = 0;

    return num_changed;

}

void split(number * num, bool& found)
{
    if (found) return;

    if (num->type == REGULAR_NUMBER)
    {
        if (num->value >= 10)
        {
            found = true;
            num->type = PAIR;
            num->number1 = new number;
            num->number1->type = REGULAR_NUMBER;
            num->number1->value = (int)(num->value / 2.0);
            num->number2 = new number;
            num->number2->type = REGULAR_NUMBER;
            num->number2->value = (int)(num->value / 2.0 + 0.5);
        }
    }
    else
    {
        split(num->number1, found);
        split(num->number2, found);
    }
}

number * add(number* n1, number * n2)
{
    number * res = new number;
    res->type = PAIR;
    res->number1 = n1;
    res->number2 = n2;
    return res;
}

void explode_split(number * num)
{
    while(true)
    {
        //cout << num_to_string(num) << endl;
        while(explode(num))
        {
            //cout << num_to_string(num) << endl;
        }
        bool found = false;
        //cout << "splitting " << endl;
        split(num, found);
        //cout << num_to_string(num) << endl;
        if (found == false)
        {
            break;
        }
    }
}


int calc_mag(number * num)
{
    if (num->type == REGULAR_NUMBER) return num->value;
    return calc_mag(num->number1) * 3 + calc_mag(num->number2) * 2;
}

int main()
{
    fstream f;
    f.open("input.txt", ios::in);
    string str;
    vector<string> nums;
    while(getline(f, str))
    {
        nums.push_back(str);
    }

    number * sum = string_to_num(nums[0]);
    for (int i = 1; i < nums.size(); i++)
    {
        sum = add(sum, string_to_num(nums[i]));
        explode_split(sum);
        //cout << "after explode and split";
        //cout << num_to_string(sum) << endl;


    }
    cout << calc_mag(sum) << endl;

    // part 2
    int max_mag = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < nums.size(); j++)
        {
            if (i==j) continue;
            sum = add(string_to_num(nums[i]), string_to_num(nums[j]));
            explode_split(sum);
            max_mag = max(max_mag, calc_mag(sum));
        }
    }
    cout << max_mag << endl;




}