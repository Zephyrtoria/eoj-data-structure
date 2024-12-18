#include <bits/stdc++.h>
using namespace std;
struct node
{
    int val;
    node *next;
    node() {}
    node(int v) : val(v), next(NULL) {}
};
class LinkedList
{
private:
    node *head; // 头指针，指向不存数据的表头结点
public:
    LinkedList();                                   // 默认构造函数
    LinkedList(const LinkedList &other);            // 拷贝构造函数
    LinkedList &operator=(const LinkedList &other); // 赋值运算符重载
    ~LinkedList();                                  // 析构函数

    void insert(int v);    // 插入函数
    void print();          // 打印链表
    void clear();          // 清除链表
    void K_Reverse(int k); // K 反转函数
};

LinkedList::LinkedList()
{
    head = new node(-1); // 表头结点的值可以任意，因为它不存储实际数据
    head->next = NULL;
}
LinkedList::LinkedList(const LinkedList &other)
{
    head = new node(-1);
    node *current = head;
    node *other_current = other.head->next;

    while (other_current != NULL)
    {
        current->next = new node(other_current->val);
        current = current->next;
        other_current = other_current->next;
    }
}

LinkedList &LinkedList::operator=(const LinkedList &other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();

    head = new node(-1);
    node *current = head;
    node *other_current = other.head->next;

    while (other_current != NULL)
    {
        current->next = new node(other_current->val);
        current = current->next;
        other_current = other_current->next;
    }

    return *this;
}

void LinkedList::clear()
{
    node *current = head;
    while (current != NULL)
    {
        node *temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::print()
{
    node *now = head;
    now = now->next;
    while (now != NULL)
    {
        cout << now->val << " ";
        now = now->next;
    }
    cout << endl;
}

void LinkedList::insert(int v)
{
    node *temp = new node(v);
    node *temp1 = head;
    while (temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = temp;
}

/*你的代码会被嵌入到这个位置*/
void LinkedList::K_Reverse(int k)
{
    // TODO
    node *last = head;
    node *start = head->next, *end;

    while (start != NULL)
    {
        end = start;
        for (int i = 1; i < k && end != NULL; i++)
            end = end->next;
        
        if (end == NULL)  // last nodes which less than k
            break;
        
        node *pre = start, *cur = start->next;
        last->next = end;
        start->next = end->next;
        while (pre != end)
        {
            node *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }

        last = start;
        start = start->next;
    }
}

int main()
{
    LinkedList l;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        l.insert(x);
    }
    l.K_Reverse(k);
    l.print();
    return 0;
}