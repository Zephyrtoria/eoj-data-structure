#include <iostream>
#include <stack>
using namespace std;

int main()
{
    string str;
    stack<char> s = stack<char>();
    bool flag = true;
    while (cin >> str)
    {
        for (int i = 0, size = str.length(); flag && i < size; i++)
        {
            char c = str[i];
            if (i < size - 1 && c == '/' && str[i + 1] == '*')
                s.push('<');
            else if (c == '(')
                s.push('(');
            else if (c == '{')
                s.push('{');
            else if (c == '[')
                s.push('[');
            else if (i < size - 1 && c == '*' && str[i + 1] == '/')
            {
                if (s.empty() || s.top() != '<')
                    flag = false;
                s.pop();
            }
            else if (c == ')')
            {
                if (s.empty() || s.top() != '(')
                    flag = false;
                s.pop();
            }
            else if (c == '}')
            {
                if (s.empty() || s.top() != '{')
                    flag = false;
                s.pop();
            }
            else if (c == ']')
            {
                if (s.empty() || s.top() != '[')
                    flag = false;
                s.pop();
            }
        }
    }

    if (!s.empty())
        flag = false;

    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}