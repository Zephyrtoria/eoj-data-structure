#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define NIL nullptr

struct term
{              // 多项式的一项
    int coef_; // 系数
    int expn_; // 指数
};
typedef term ElemType;

typedef struct ListNode *Position; // 指针即结点位置
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
    LinkedList();                                                        // 构造函数，初始化一个空的线性表
    LinkedList(const LinkedList &);                                      // 复制构造函数，复制一个线性表
    LinkedList &operator=(const LinkedList &llist);                      // 赋值运算符重载
    ~LinkedList();                                                       // 析构函数,释放线性表占用的空间
    void insert(Position pos, ElemType e);                               // 在pos位置后插入元素e
    void remove(Position pos);                                           // 删除pos位置后的元素
    void from_string(const string &);                                    // 从字符串构造一个多项式
    bool is_valid_position(Position pos);                                // 判断pos是否为合法位置
    friend std::ostream &operator<<(std::ostream &, const LinkedList &); // 输出一个链表
    friend LinkedList operator*(LinkedList &, LinkedList &);             // 多项式乘法
};
int main()
{
    string s1, s2;
    while (cin >> s1 >> s2)
    {
        LinkedList l1, l2;
        l1.from_string(s1);
        l2.from_string(s2);
        LinkedList l3 = l1 * l2;
        cout << l3;
    }
}
LinkedList::LinkedList()
{
    head_ = new ListNode{{-1, -1}, NIL}; // 头指针指向一个空头结点
    length_ = 0;
}
LinkedList::~LinkedList()
{
    Position p = head_->next_;
    while (p != NIL)
    {
        head_ = p->next_;
        delete p;
        p = head_;
        --length_;
    }
    delete head_;
    if (length_ != 0)
    {
        std::cout << "链表没有清空，lenth_" << length_ << endl;
    }
}

LinkedList::LinkedList(const LinkedList &llist)
{
    Position temp, p;
    temp = llist.head_->next_;
    length_ = llist.length_;
    head_ = new ListNode{{-1, -1}, NIL}; // 产生空头结点
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
bool LinkedList::is_valid_position(Position pos)
{
    Position temp = head_;
    while (temp != NIL)
    {
        if (temp == pos)
            return true;
        temp = temp->next_;
    }
    return false;
}

void LinkedList::insert(Position pos, ElemType e)
{
    // 在pos后插入一个节点，请尽可能考虑异常情况
    if (!is_valid_position(pos))
        return;

    Position temp = head_;
    length_++;
    while (temp != NIL)
    {
        if (temp == pos)
        {
            temp->next_ = new ListNode{e, temp->next_};
            return;
        }
        temp = temp->next_;
    }
}
void LinkedList::remove(Position pos)
{
    // 在pos后插入一个节点，请尽可能考虑异常情况
    if (!is_valid_position(pos))
        return;

    Position temp = head_;
    length_--;
    while (temp->next_ != NIL)
    {
        if (temp->next_ == pos->next_)
        {
            temp->next_ = temp->next_->next_;
            return;
        }
        temp = temp->next_;
    }
}

void LinkedList::from_string(const string &s)
{
    // 需要完成从字符串构造一个多项式
    string s_;
    if (s[0] != '-')
        s_ = "+" + s;
    else
        s_ = s;
    Position insertPosition = head_;
    int i = 0, size = s_.size();

    Position temp = head_;
    while (i < size)
    {
        int j;
        int sign = (s_[i] == '-') ? -1 : 1;
        for (j = i + 1; j < size && s_[j] != '+' && s_[j] != '-'; j++)
            ;

        // (i, j)
        int u = i + 1;
        while (u < j && s_[u] != 'x')
            u++;
        if (i + 1 == u) // c = 1
        {
            if (s_[u + 1] == '^') // c = 1 && e != 1
            {
                int ex = 0;
                for (int w = u + 2; w < j; w++)
                    ex = ex * 10 + s_[w] - '0';
                ListNode *newNode = new ListNode{{sign, ex}, NIL};
                temp->next_ = newNode;
            }
            else // c = 1 && e = 1
            {
                ListNode *newNode = new ListNode{{sign, 1}, NIL};
                temp->next_ = newNode;
            }
        }
        else if (u == j) // e = 0
        {
            int an = 0;
            for (int w = i + 1; w < j; w++)
                an = an * 10 + s_[w] - '0';
            ListNode *newNode = new ListNode{{sign * an, 0}, NIL};
            temp->next_ = newNode;
        }
        else // c != 1
        {
            int an = 0;
            for (int w = i + 1; w < u; w++)
                an = an * 10 + s_[w] - '0';
            if (s_[u + 1] == '^') // e != 1
            {
                int ex = 0;
                for (int w = u + 2; w < j; w++)
                    ex = ex * 10 + s_[w] - '0';
                ListNode *newNode = new ListNode{{sign * an, ex}, NIL};
                temp->next_ = newNode;
            }
            else // e = 1
            {
                ListNode *newNode = new ListNode{{sign * an, 1}, NIL};
                temp->next_ = newNode;
            }
        }
        temp = temp->next_;
        i = j;
        length_++;
    }
}
std::ostream &operator<<(std::ostream &os, const LinkedList &llist)
{
    // 需要完成输出
    ListNode *cur = llist.head_->next_;

    while (cur != NIL)
    {
        cout << cur->data_.coef_ << " ";
        cur = cur->next_;
    }
    cout << '\n';
    return os;
}
LinkedList operator*(LinkedList &l1, LinkedList &l2)
{
    // 需要完成多项式乘法, 返回一个链表表示的多项式。
    LinkedList *res = new LinkedList;

    ListNode *curRes = res->head_;
    for (ListNode *cur1 = l1.head_->next_; cur1 != NIL; cur1 = cur1->next_)
    {
        int newCoe;
        int newExp;
        for (ListNode *cur2 = l2.head_->next_; cur2 != NIL; cur2 = cur2->next_)
        {
            newCoe = cur1->data_.coef_ * cur2->data_.coef_;
            newExp = cur1->data_.expn_ + cur2->data_.expn_;

            ListNode *temp = res->head_;
            while (temp->next_ != NIL && temp->next_->data_.expn_ > newExp)
                temp = temp->next_;

            if (temp->next_ == NIL)
                res->insert(temp, {newCoe, newExp});
            else if (temp->next_->data_.expn_ < newExp)
            {
                res->insert(temp, {newCoe, newExp});
            }
            else if (temp->next_->data_.expn_ == newExp)
            {
                temp->next_->data_.coef_ += newCoe;
                if (temp->next_->data_.coef_ == 0)
                    res->remove(temp);
            }
        }
    }

    return *res;
}
