#include <iostream>
#include <stack>
using namespace std;

void change(stack<int> &inqueue, stack<int> &dequeue)
{
    while (!inqueue.empty())
    {
        dequeue.push(inqueue.top());
        inqueue.pop();
    }
}

int main(void)
{
    int n;
    cin >> n;

    stack<int> inqueue, dequeue;

    while (n--)
    {
        string input;
        cin >> input;
        if (input == "push")
        {
            int x;
            cin >> x;
            inqueue.push(x);
        }
        else if (input == "pop")
        {
            if (dequeue.empty())
                change(inqueue, dequeue);
            dequeue.pop();
        }
        else
        {
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                if (dequeue.empty())
                    change(inqueue, dequeue);
                cout << dequeue.top() << endl;
            }
            else
            {
                int a = inqueue.size();
                int b = dequeue.size();
                if (a > b)
                    cout << b << " " << a << endl;
                else
                    cout << a << " " << b << endl;
            }
        }
    }

    return 0;
}