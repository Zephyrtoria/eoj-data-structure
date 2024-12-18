#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

vector<string> split(string infix)
{
    vector<string> result;

    int count = 0;
    int size = infix.size();
    for (int i = 0; i < size; i++)
    {
        if ('0' <= infix[i] && infix[i] <= '9')
        {
            count = count * 10 + infix[i] - '0';
        }
        else
        {
            if (count != 0)
            {
                result.push_back(to_string(count));
                count = 0;
            }
            string temp;
            temp = infix[i];
            result.push_back(temp);
            if (i == 0 && infix[i] == '-' || infix[i] == '(' && infix[i + 1] == '-')
            {
                result.push_back("0");
            }
        }
    }
    // the end may be 0 (but should deal with "10")
    if (count > 0 || (infix[size - 1] == '0' && !('0' <= infix[size - 2] && infix[size - 2] <= '9')))
        result.push_back(to_string(count));

    return result;
}

int getPriority(string s)
{
    switch (s[0])
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return 0;
}

vector<string> infixToPostfix(vector<string> &infix)
{
    vector<string> result;
    stack<string> manifact;

    for (auto each : infix)
    {
        if ('0' <= each[0] && each[0] <= '9')
        {
            result.push_back(each);
        }
        else
        {
            if (each[0] == '(')
            {
                manifact.push("(");
            }
            else if (each[0] == ')')
            {
                while (manifact.top() != "(")
                {
                    result.push_back(manifact.top());
                    manifact.pop();
                }
                manifact.pop();
            }
            else
            {
                int priority = getPriority(each);
                if (manifact.empty() || manifact.top()[0] == '(' || priority > getPriority(manifact.top()))
                {
                    manifact.push(each);
                }
                else
                {
                    while (!manifact.empty() && manifact.top()[0] != '(' && priority <= getPriority(manifact.top()))
                    {
                        result.push_back(manifact.top());
                        manifact.pop();
                    }
                    manifact.push(each);
                }
            }
        }
    }

    while (!manifact.empty())
    {
        if (manifact.top() != "(")
            result.push_back(manifact.top());
        manifact.pop();
    }

    return result;
}

int doMath(vector<string> &postfix)
{
    stack<int> numbers;

    for (string each : postfix)
    {
        if ('0' <= each[0] && each[0] <= '9')
            numbers.push(stod(each));
        else
        {
            switch (each[0])
            {
            case '+':
            {
                int a = numbers.top();
                numbers.pop();
                int b = numbers.top();
                numbers.pop();
                numbers.push(b + a);
                break;
            }
            case '-':
            {
                int a = numbers.top();
                numbers.pop();
                int b = numbers.top();
                numbers.pop();
                numbers.push(b - a);
                break;
            }
            case '*':
            {
                int a = numbers.top();
                numbers.pop();
                int b = numbers.top();
                numbers.pop();
                numbers.push(b * a);
                break;
            }
            case '/':
            {
                int a = numbers.top();
                numbers.pop();
                int b = numbers.top();
                numbers.pop();
                numbers.push(b / a);
                break;
            }
            }
        }
    }
    return numbers.top();
}

int main(void)
{
    string infix;
    cin >> infix;

    auto splittedInfix = split(infix);

    auto postfix = infixToPostfix(splittedInfix);

    cout << doMath(postfix) << endl;
    return 0;
}