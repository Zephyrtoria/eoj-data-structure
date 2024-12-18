#include <iostream>
using namespace std;

const int N = 300010;

typedef struct stack
{
    int data[N];
    int front = 0;
    int rear = 0;
    int mode = 0;
} stack;

void push(stack *s, int x)
{
    if (s->front == s->rear)
    {
        s->data[s->rear] = x;
        s->rear = (s->rear + 1) % N;
    }
    else if (s->mode == 0)
    {
        s->front = (s->front + N - 1) % N;
        s->data[s->front] = x;
    }
    else
    {
        s->data[s->rear] = x;
        s->rear = (s->rear + 1) % N;
    }
}

void pop(stack *s)
{
    if (s->mode == 0)
    {
        s->front = (s->front + 1) % N;
    }
    else
    {
        s->rear = (s->rear - 1 + N) % N;
    }
}

void showTop(stack *s)
{
    if (s->front == s->rear)
        cout << -1;
    else if (s->mode == 0)
    {
        cout << s->data[s->front];
    }
    else
    {
        cout << s->data[(s->rear - 1 + N) % N];
    }

    cout << endl;
}

int main(void)
{
    int q;
    cin >> q;

    stack *s = new stack;

    while (q--)
    {
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            int x;
            cin >> x;
            push(s, x);
            break;
        case 2:
            pop(s);
            break;
        case 3:
            s->mode = 1 - s->mode;
            break;
        }
        showTop(s);
    }
    return 0;
}