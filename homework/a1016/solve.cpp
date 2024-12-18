#include <iostream>
#include <stack>
#include <string>
using namespace std;
const int N = 110;

double doMath(char c, double a, double b)
{
    switch (c)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

double cal(char **arr, int count)
{
    stack<double> s;
    for (int i = count - 1; i >= 0; i--)
    {
        if (isdigit(arr[i][0]))
        {
            s.push(atof(arr[i]));
        }
        else
        {
            double a = s.top(); // left
            s.pop();
            double b = s.top(); // right
            s.pop();
            s.push(doMath(arr[i][0], a, b));
        }
    }
    return s.top();
}



int main(void)
{
    char **arr = new char *[N];
    char *temp = new char[12];
    int count = 0;

    while (cin >> temp)
    {
        arr[count++] = temp;
        temp = new char[12];
    }
    delete temp;

    printf("%.6f\n", cal(arr, count));

    for (int i = 0; i < count; i++)
        delete arr[i];
    delete arr;
    return 0;
}