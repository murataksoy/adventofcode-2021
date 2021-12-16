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

struct packet
{
    long long version;
    long long type_id;
    long long value;
    vector<packet*> packets;
};

map<char, string> get_conversion_map()
{
    map<char, string> conversion_map;
    conversion_map['0'] = "0000";
    conversion_map['1'] = "0001";
    conversion_map['2'] = "0010";
    conversion_map['3'] = "0011";
    conversion_map['4'] = "0100";
    conversion_map['5'] = "0101";
    conversion_map['6'] = "0110";
    conversion_map['7'] = "0111";
    conversion_map['8'] = "1000";
    conversion_map['9'] = "1001";
    conversion_map['A'] = "1010";
    conversion_map['B'] = "1011";
    conversion_map['C'] = "1100";
    conversion_map['D'] = "1101";
    conversion_map['E'] = "1110";
    conversion_map['F'] = "1111";
    return conversion_map;
}

long long bin2dec(string str)
{
    long long num=0;
    long long mul = 1;
    for (long long i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] == '1') num += mul;
        mul *= 2;
    }
    return num;
}

array<long long, 2> get_version(string str, long long ind)
{
    return {bin2dec(str.substr(ind, 3)), ind + 3};
}

array<long long, 2> get_type_id(string str, long long ind)
{
    return {bin2dec(str.substr(ind, 3)), ind + 3};
}

array<long long, 2> get_literal(string str, long long ind)
{
    string num;
    while(1)
    {
        num += str.substr(ind+1, 4);
        if (str[ind] == '0') break;
        ind += 5;
    }
    return {bin2dec(num), ind + 5};
}

array<long long, 2> get_length_type_id(string str, long long ind)
{
    return {str[ind] - '0', ind + 1};
}

array<long long, 2> get_total_length(string str, long long ind)
{
    return {bin2dec(str.substr(ind, 15)), ind + 15};
}

array<long long, 2> get_number_of_sub_packets(string str, long long ind)
{
    return {bin2dec(str.substr(ind, 11)), ind + 11};
}

void print_packet(packet * p)
{
    cout << "version " << p->version << " type_id " << p->type_id;
    if (p->type_id == 4) cout << " value " << p->value;
    cout << endl;
}

void parse_packet(packet* head, string str, long long& ind)
{
    long long version;
    tie(version, ind) = get_version(str, ind);
    head->version = version;
    long long type_id;
    tie(type_id, ind) = get_type_id(str, ind);
    head->type_id = type_id;
    if (type_id == 4)
    {
        long long value;
        tie(value, ind) = get_literal(str, ind);
        head->value = value;
        print_packet(head);
    }
    else
    {
        long long length_type_id;
        tie(length_type_id, ind) = get_length_type_id(str, ind);
        print_packet(head);
        if (length_type_id == 0)
        {
            long long total_length;
            tie(total_length, ind) = get_total_length(str, ind);
            long long ind2 = ind;
            while(ind2-ind < total_length)
            {
                packet * new_packet = new packet;
                head->packets.push_back(new_packet);
                parse_packet(new_packet, str, ind2);
            }
            ind+=total_length;
        }
        else
        {
            long long number_of_sub_packets;
            tie(number_of_sub_packets, ind) = get_number_of_sub_packets(str, ind);
            long long n_packets = 0;
            while(n_packets < number_of_sub_packets)
            {
                packet * new_packet = new packet;
                head->packets.push_back(new_packet);
                parse_packet(new_packet, str, ind);
                n_packets++;
            }
        }
    }
}

long long version_sum(packet *head)
{
    if (head->type_id ==4) return head->version;
    long long sum = head->version;
    for (auto p:head->packets)
    {
        sum += version_sum(p);
    }
    return sum;
}

long long evaluate(packet * head)
{
    if (head->type_id ==4) return head->value;
    long long value;
    if (head->type_id == 0)
    {
        value = 0;
        for (auto p:head->packets)
        {
            value += evaluate(p);
        }
    }
    if (head->type_id == 1)
    {
        value = 1;
        for (auto p:head->packets)
        {
            value *= evaluate(p);
        }
    }
    if (head->type_id == 2)
    {
        value = INT_MAX;
        for (auto p:head->packets)
        {
            value = min(value, evaluate(p));
        }
    }
    if (head->type_id == 3)
    {
        value = 0;
        for (auto p:head->packets)
        {
            value = max(value, evaluate(p));
        }
    }

    if (head->type_id == 5)
    {
        value = (evaluate(head->packets[0]) > evaluate(head->packets[1]));
    }

    if (head->type_id == 6)
    {
        value = (evaluate(head->packets[0]) < evaluate(head->packets[1]));
    }

    if (head->type_id == 7)
    {
        value = (evaluate(head->packets[0]) == evaluate(head->packets[1]));
    }

    cout << "returned value " << value << endl;
    return value;

}

int main()
{
    auto conversion_map = get_conversion_map();

    fstream f;
    f.open("input.txt", ios::in);
    string str;
    getline(f, str);

    string strbin;
    for (auto c:str)
    {
        strbin += conversion_map[c];
    }

    long long ind = 0;
    packet * head = new packet;
    parse_packet(head, strbin, ind);

    cout << version_sum(head) << endl;
    cout << evaluate(head) << endl;

}