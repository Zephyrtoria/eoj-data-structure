#include <bits/stdc++.h>
using namespace std;

#define ERROR -1
#define kMaxSize 100
typedef int QElemSet; /* 队列元素类型定义为整型 */
typedef enum
{
    Push,
    Pop,
    Inject,
    Eject,
    End
} Operation; /* 操作类型 */

Operation GetOp()
{ /* 判断输入的操作类型 */
    string op;
    Operation ret;

    cin >> op; /* 读入一个操作 */
    switch (op[2])
    { /* 用第3个字母区分操作 */
    case 's':
        ret = Push;
        break;
    case 'p':
        ret = Pop;
        break;
    case 'j':
        ret = Inject;
        break;
    case 'e':
        ret = Eject;
        break;
    case 'd':
        ret = End;
        break;
    default:
        break;
    }

    return ret;
}
typedef int Position;

class Deque
{
private:
    int capacity;   /* 双端队列的容量 */
    Position front; /* 双端队列的队首指针，初始化为0 */
    Position rear;  /* 双端队列的队尾指针，初始化为0 */
    QElemSet *data; /* 存储数据的数组 */
public:
    struct DequeException
    {
        std::string error_;
        DequeException(std::string s);
    };
    Deque(unsigned = kMaxSize);      // 构造函数，初始化一个空的线性表
    Deque(const Deque &);            // 拷贝构造函数
    Deque &operator=(const Deque &); // 重载赋值运算符=
    ~Deque();                        // 析构函数,释放线性表占用的空间

    void InitDeque(int n);   // 初始化
    bool Push(QElemSet x);   // 从头部入队列，如果队满，无法入队列返回false, 否则返回true
    QElemSet Pop();          // 从头部出队列, 如果队空，返回ERROR，否则返回出队列元素
    bool Inject(QElemSet x); // 从尾部入队列，如果队满，无法入队列返回false, 否则返回true
    QElemSet Eject();        // 从尾部出队列, 如果队空，返回ERROR，否则返回出队列元素
    void PrintDeque();       // 打印队列
    void show()
    {
        cout << "front = " << front << " rear = " << rear << endl;
    }
};
Deque::DequeException::DequeException(std::string s) : error_(s) {}

Deque::Deque(unsigned size) : capacity(size + 1), front(0), rear(0)
{
    data = new QElemSet[capacity + 1];
}
void Deque::InitDeque(int n)
{
    data = new QElemSet[n + 1];
    front = rear = 0;
    capacity = n + 1;
}
Deque::Deque(const Deque &other) : capacity(other.capacity), front(other.front), rear(other.rear)
{
    data = new QElemSet[capacity + 1];
    for (int i = front; i != rear; i = (i + 1) % capacity)
    {
        data[i] = other.data[i];
    }
}

Deque &Deque::operator=(const Deque &other)
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        front = other.front;
        rear = other.rear;
        data = new QElemSet[capacity + 1];
        for (int i = front; i != rear; i = (i + 1) % capacity)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Deque::~Deque()
{
    delete[] data;
}

/* 你的代码将会被嵌入在这个位置 */
bool Deque::Push(QElemSet x)
{
    // TODO 从头部入队列，如果队满，无法入队列返回false, 否则返回true
    if ((rear + 1) % capacity == front)
        return false;

    if (front == rear)
        rear = (rear + 1) % capacity;
    else
        front = (front - 1 + capacity) % capacity;
    data[front] = x;
    return true;
}
QElemSet Deque::Pop()
{
    // TODO 从头部出队列, 如果队空，返回ERROR，否则返回出队列元素
    if (front == rear)
        return ERROR;
    QElemSet result = data[front];
    front = (front + 1) % capacity;
    return result;
}
bool Deque::Inject(QElemSet x)
{
    // TODO 从尾部入队列，如果队满，无法入队列返回false, 否则返回true
    if ((rear + 1) % capacity == front)
        return false;

    data[rear] = x;
    rear = (rear + 1) % capacity;

    return true;
}
QElemSet Deque::Eject()
{
    // TODO 从尾部出队列, 如果队空，返回ERROR，否则返回出队列元素
    if (front == rear)
        return ERROR;

    rear = (rear - 1 + capacity) % capacity;
    return data[rear];
}

void Deque::PrintDeque()
{
    if (front == rear)
    {
        cout << "Deque is empty" << endl;
        return;
    }
    cout << "Inside Deque: ";
    for (int i = front; i != rear; i = (i + 1) % capacity)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    QElemSet x;
    Deque deque(n);
    bool done = false;
    while (done == false)
    {
        deque.show();
        switch (GetOp())
        {
        case Push:
            cin >> x;
            if (deque.Push(x) == false)
            {
                cout << "Deque is Full!" << endl;
            }
            break;
        case Pop:
            x = deque.Pop();
            if (x == ERROR)
            {
                cout << "Deque is Empty!" << endl;
            }
            else
            {
                cout << x << " is out" << endl;
            }
            break;
        case Inject:
            cin >> x;
            if (deque.Inject(x) == false)
            {
                cout << "Deque is Full!" << endl;
            }
            break;
        case Eject:
            x = deque.Eject();
            if (x == ERROR)
            {
                cout << "Deque is Empty!" << endl;
            }
            else
            {
                cout << x << " is out" << endl;
            }
            break;
        case End:
            deque.PrintDeque();
            done = true;
            break;
        default:
            break;
        }
    }
    return 0;
}