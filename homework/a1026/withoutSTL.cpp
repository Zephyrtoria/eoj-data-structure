/* #include <iostream>
using namespace std;

typedef struct
{
    int *stack;
    int top = 0;
} stack;

void change(stack &enqueue, stack &dequeue)
{
    while (enqueue.top != 0)
    {
        dequeue.stack[dequeue.top++] = enqueue.stack[--enqueue.top];
    }
}

int main(void)
{
    int n;
    cin >> n;

    stack enqueue;
    stack dequeue;

    enqueue.stack = new int[n];
    dequeue.stack = new int[n];

    while (n--)
    {
        string input;
        cin >> input;
        if (input == "push")
        {
            int x;
            cin >> x;
            enqueue.stack[enqueue.top++] = x;
        }
        else if (input == "pop")
        {
            if (dequeue.top == 0)
                change(enqueue, dequeue);

            dequeue.top--;
        }
        else
        {
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                if (dequeue.top == 0)
                    change(enqueue, dequeue);
                cout << dequeue.stack[dequeue.top - 1] << endl;
            }
            else
            {
                int a = enqueue.top;
                int b = dequeue.top;
                if (a > b)
                {
                    int temp = a;
                    a = b;
                    b = a;
                }
                cout << a << " " << b << endl;
            }
        }
    }

    delete enqueue.stack;
    delete dequeue.stack;
    return 0;
} */