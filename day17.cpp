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

using namespace std;

bool y_target_ok(int vy, array<int, 2> yt)
{
    int y = 0;
    while ( y >= yt[0])
    {
        if (y < yt[0] and vy <=0) return false;
        y += vy;
        vy--;
        if (y >= yt[0] and y <= yt[1]) return true;
    }
    return false;
}

bool x_target_ok(int vx, array<int, 2> xt)
{
    int x = 0;
    while ( x <= xt[1])
    {
        if (x < xt[0] and vx <=0) return false;
        x += vx;
        if (vx > 0) vx--;
        else if (vx < 0) vx++;
        if (x >= xt[0] and x <= xt[1]) return true;
    }
    return false;
}

int target_ok(int vx, int vy, array<int, 2> xt, array<int, 2> yt)
{
    int x = 0;
    int y = 0;
    int y_max = 0;
    while ( y >= yt[0] and x <= xt[1])
    {
        if (y < yt[0] and vy <=0 or x > xt[1] and vx >= 0) return -1;
        y += vy;
        vy--;
        y_max = max(y, y_max);
        x += vx;
        if (vx > 0) vx--;
        else if (vx < 0) vx++;
        if (y >= yt[0] and y <= yt[1] and x >= xt[0] and x <= xt[1]) return y_max;
    }
    return -1;
}


int main()
{
    fstream f;
    array<int, 2> xt{34, 67};
    array<int, 2> yt{-215, -186};

    int vy_min = 0;
    while(not y_target_ok(vy_min, yt)){vy_min++;}
    int vy_max = vy_min;
    while(y_target_ok(vy_max, yt)) {vy_max++;}

    int vx_min = 1;
    while(not x_target_ok(vx_min, xt)) {vx_min++;}
    int vx_max = vx_min;
    while(x_target_ok(vx_max, xt)) {vx_max++;}

    int y_max = -1;
    int vxp = 0;
    int vyp = 0;
    for (int vx = vx_min; vx <= 100*vx_max; vx++)
    {
        for (int vy = vy_min; vy <= 100*vy_max; vy++)
        {
            int y = target_ok(vx, vy, xt, yt);
            if (y > y_max)
            {
                y_max = y;
                vxp = vx;
                vyp = vy;
            }
        }
    }
    cout << y_max << " " << vxp << " " << vyp << endl;

}