#include <iostream>
using namespace std;

struct node
{
    int data_;
    node *prev_;
    node *next_;
};

class LinkedList
{
private:
    node *head_; // head and tail are dummy nodes

public:
    LinkedList()
    {
        head_ = new node{-1, NULL, NULL};
        head_->next_ = head_;
        head_->prev_ = head_;
    };
    ~LinkedList();

    void insert(int x);
    bool remove(int x);
    void print();
};

LinkedList::~LinkedList()
{
    node *cur = head_->next_;
    while (cur != head_)
    {
        node *temp = cur;
        delete temp;
        cur = cur->next_;
    }
    delete head_;
}

void LinkedList::insert(int x)
{
    node *insertion = new node{x, NULL, NULL};
    node *last = head_->prev_;

    insertion->next_ = head_;
    insertion->prev_ = last;
    last->next_ = insertion;
    head_->prev_ = insertion;
}

bool LinkedList::remove(int x)
{
    if (head_->next_ == head_)
        return false;

    bool flag = false;

    node *pre = head_;
    node *cur = head_->next_;
    while (cur != head_)
    {
        if (cur->data_ == x)
        {
            flag = true;
            pre->next_ = cur->next_;
            cur->next_->prev_ = pre;

            node *temp = cur;
            cur = cur->next_;
            delete temp;
        }
        else
        {
            pre = cur;
            cur = cur->next_;
        }
    }

    return flag;
}

void LinkedList::print()
{
    node *cur = head_->next_;
    while (cur != head_)
    {
        cout << cur->data_ << ' ';
        cur = cur->next_;
    }
    cout << endl;
}

int main(void)
{
    LinkedList ls = LinkedList();

    int x;
    while (true)
    {
        cin >> x;
        if (x == -1)
            break;
        ls.insert(x);
    }

    while (true)
    {
        cin >> x;
        if (x == -1)
            break;
        bool flag = ls.remove(x);
        if (!flag)
            cout << -1 << endl;
    }

    ls.print();
    return 0;
}