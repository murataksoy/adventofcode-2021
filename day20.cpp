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

vector<string> pad(const vector<string>& im, int npad)
{
    vector<string> im_padded;
    int n = im.size();

    for (int i = 0; i < npad; i++)
    {
        im_padded.push_back(string(n + 2 * npad, '.'));
    }

    for (int i = 0; i < im.size(); i++)
    {
        im_padded.push_back(string(npad, '.') + im[i] + string(npad, '.'));
    }

    for (int i = 0; i < npad; i++)
    {
        im_padded.push_back(string(n + 2 * npad, '.'));
    }
    return im_padded;
}

vector<string> crop(const vector<string> &im, int ncrop)
{
    vector<string> im_cropped;
    int n = im.size();

    for (int i = ncrop; i < n - ncrop; i++)
    {
        im_cropped.push_back(im[i].substr(ncrop, n - 2 * ncrop));
    }

    return im_cropped;
}

int str_to_dec(string str)
{
    int num = 0;
    int mul = 1;
    for (int i = str.size() -1; i >= 0; i--)
    {
        if (str[i] == '#') num += mul;
        mul *= 2;
    }
    return num;
}

vector<string> enhance(const vector<string>& im, const string& algo)
{
    int n = im.size();
    vector<string> im_enhanced(n, string(n, '.'));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            string im_sub;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k < 0 or k >= n or l < 0 or l >= n)
                        im_sub.push_back('.');
                    else
                        im_sub.push_back(im[k][l]);
                }
            }
            int num = str_to_dec(im_sub);
            im_enhanced[i][j] = algo[num];
        }
    }
    return im_enhanced;
}

void print_im(vector<string> im)
{
    for (auto& line: im)
    {
        cout << line << endl;
    }
}


int main()
{
    fstream f;
    f.open("input.txt", ios::in);
    string algo;
    getline(f, algo);
    assert(algo.size() == 512);
    string str;
    getline(f, str); // blank line
    vector<string> image;
    while(getline(f, str))
    {
        image.push_back(str);
    }

    int N = 50;
    image = pad(image, 2*N);

    for (int i = 0; i < N; i++)
    {
        image = enhance(image, algo);
    }
    image = crop(image, N);
    print_im(image);

    int count= 0;
    for (auto line:image)
    {
        for (auto c: line)
        {
            if (c=='#') count++;
        }
    }
    cout << count << endl;







}