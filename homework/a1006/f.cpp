#include <iostream>
#include <string>
using namespace std;
#define NIL nullptr
using ElemType = int;
using Position = struct ListNode *; // 指针即结点位置

struct ListNode
{
    ElemType data_; // 存储数据
    Position next_; // 线性表中下一个元素的位置
};

class LinkedList
{
private:
    Position head_; // 单链表头指针,指向空头结点
    int length_;    // 表长
public:
    struct ListException // 异常处理
    {
        std::string error_;
        ListException(std::string s) : error_(s) {};
    };
    LinkedList(); // 构造函数，初始化一个空的线性表
    LinkedList(const LinkedList &);
    LinkedList &operator=(const LinkedList &);
    ~LinkedList(); // 析构函数,释放线性表占用的空间
    void Insert(ElemType value);
    ElemType findKthToTail(int k);
};

LinkedList::LinkedList()
{
    head_ = new ListNode{0, NIL}; // 头指针指向一个空头结点
    length_ = 0;
}
LinkedList::LinkedList(const LinkedList &llist)
{
    Position temp, p;
    temp = llist.head_->next_;
    length_ = llist.length_;
    head_ = new ListNode{0, NIL}; // 产生空头结点
    p = head_;
    while (temp != NIL)
    {
        p->next_ = new ListNode{temp->data_, NIL};
        p = p->next_;
        temp = temp->next_;
    }
}
LinkedList &LinkedList::operator=(const LinkedList &llist)
{
    Position p, temp;

    if (this != &llist)
    {
        p = head_->next_;
        while (p != NIL)
        {
            temp = p;
            p = p->next_;
            delete temp;
        }
        length_ = 0;
        head_->next_ = NIL;

        temp = llist.head_->next_;
        length_ = llist.length_;
        p = head_;
        while (temp != NIL)
        {
            p->next_ = new ListNode{temp->data_, NIL};
            p = p->next_;
            temp = temp->next_;
        }
    }
    return *this;
}

LinkedList::~LinkedList()
{
    Position p = head_;
    while (p != NIL)
    {
        head_ = p->next_;
        delete p;
        p = head_;
    }
    length_ = 0;
}

void LinkedList::Insert(ElemType x)
{
    Position p = head_;
    while (p->next_ != NIL)
    {
        p = p->next_;
    }
    Position new_node = new ListNode{x, NIL};
    p->next_ = new_node;
    length_++;
}

/* 你的代码将会被嵌入在这个位置 */
ElemType LinkedList::findKthToTail(int k)
{
    if (k > length_)
        return -1;
    Position fastPointer, slowPointer;
    fastPointer = slowPointer = head_;

    for (int i = 1; i < k; i++)
        fastPointer = fastPointer->next_;

    while (fastPointer->next_ != NIL)
    {
        slowPointer = slowPointer->next_;
        fastPointer = fastPointer->next_;
    }
    return slowPointer->data_;
}

int main()
{
    LinkedList mylist;
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        ElemType x;
        cin >> x;
        mylist.Insert(x);
    }

    ElemType ans = mylist.findKthToTail(k);
    cout << ans << endl;
    return 0;
}