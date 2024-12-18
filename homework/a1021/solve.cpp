/* #include <iostream>
using namespace std;

typedef struct node
{
    int val;
    node *prev;
    node *next;
} node;

typedef struct stack
{
    node *head;
    node *end;
    int mode; // 0-normal 1-reverse
} stack;

void push(stack *s, int x)
{
    node *append = new node{x, nullptr, nullptr};
    if (s->head == nullptr)
    {
        s->head = s->end = append;
        return;
    }

    if (s->mode == 0)
    {
        append->next = s->head;
        s->head->prev = append;
        s->head = append;
    }
    else
    {
        append->prev = s->end;
        s->end->next = append;
        s->end = append;
    }
}

void pop(stack *s)
{
    if (s->mode == 0)
    {
        node *temp = s->head;
        s->head = temp->next;
        delete temp;
    }
    else
    {
        node *temp = s->end;
        s->end = temp->prev;
        delete temp;
    }

    if (s->head == nullptr || s->end == nullptr)
        s->head = s->end = nullptr;
}

void showTop(stack *s)
{
    if (s->head == nullptr || s->end == nullptr)
        cout << -1 << endl;
    else if (s->mode == 0)
        cout << s->head->val << endl;
    else
        cout << s->end->val << endl;
}

int main(void)
{
    int q;
    cin >> q;

    stack *s = new stack{nullptr, nullptr, 0};

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
} */