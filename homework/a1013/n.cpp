#include <iostream>
#include <map>
#include <string>
using namespace std;
const int N = 100010;

void splitString(string &s, string &a, string &b)
{
    int i = 0;
    for (i = 0; s[i] != ' '; i++)
        ;
    a = s.substr(0, i);
    b = s.substr(i + 1);
}

int main()
{
    map<string, string> m;
    string line;

    while (true)
    {
        getline(cin, line);
        if (line.length() == 0)
        {
            break;
        }
        string a, b;
        splitString(line, a, b);
        m[b] = a;
    }

    string query;
    while (cin >> query)
    {
        if (m.count(query))
        {
            cout << m[query] << endl;
        }
        else
        {
            cout << "eh" << endl;
        }
    }

    return 0;
}