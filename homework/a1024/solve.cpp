#include <bits/stdc++.h>
using namespace std;

typedef int QElemSet; // 用户定义的数据类型
#define NIL -1
typedef int Position; // 整数下标，表示元素的位置
#define kMaxSize 100  // 队列的最大容量

class Queue
{
private:
    int capacity;   // 队列的容量
    Position front; // 队头指针
    int count;      // 队列中元素个数
    QElemSet *data; // 队列元素数组
public:
    struct QueueException
    {
        string error_;
        QueueException(string s); // 构造函数声明
    };

    Queue(unsigned size = kMaxSize); // 构造函数
    Queue(const Queue &);            // 拷贝构造函数
    Queue &operator=(const Queue &); // 赋值运算符重载
    ~Queue();                        // 析构函数

    void initQueue(int size); // 初始化队列
    bool IsFull();            // 判断队列是否已满
    bool IsEmpty();           // 判断队列是否为空
    QElemSet GetFront();      // 获取队列队头元素
    void DestroyQueue();      // 销毁队列
    void EnQueue(QElemSet x); // 入队操作
    void DeQueue();           // 出队操作
};

Queue::QueueException::QueueException(string s) : error_(s) {}

Queue::Queue(unsigned size) : capacity(size), front(0), count(0)
{
    data = new QElemSet[capacity];
}

Queue::Queue(const Queue &other) : capacity(other.capacity), front(other.front), count(other.count)
{
    data = new QElemSet[capacity];
    for (int i = 0; i < count; ++i)
    {
        data[i] = other.data[i];
    }
}

Queue &Queue::operator=(const Queue &other)
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        front = other.front;
        count = other.count;
        data = new QElemSet[capacity];
        for (int i = 0; i < count; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Queue::~Queue()
{
    DestroyQueue();
}

void Queue::initQueue(int size)
{
    capacity = size;
    front = count = 0;
    data = new QElemSet[capacity];
}

bool Queue::IsFull()
{
    return count == capacity;
}

QElemSet Queue::GetFront()
{
    if (IsEmpty())
    {
        return NIL;
    }
    return data[front];
}
void Queue::DestroyQueue()
{
    delete[] data;
    data = NULL;
    count = capacity = front = 0;
}

/* 你的代码将会被嵌入在这个位置 */
bool Queue::IsEmpty()
{
    // TODO
    return count == 0;
}

void Queue::EnQueue(QElemSet x)
{
    // TODO
    if (count == capacity)
    {
        cout << "ERROR" << endl;
        return;
    }

    data[(front + count) % capacity] = x;
    count++;
}

void Queue::DeQueue()
{
    // TODO
    if (IsEmpty())
    {
        cout << "ERROR" << endl;
        return;
    }
    int result = data[front];
    front = (front + 1) % capacity;
    count--;
}

int main()
{
    int n, x;
    cin >> n;
    Queue queue = Queue(n);
    char cmd;
    cin >> cmd;
    while (cmd != 'E')
    {
        if (cmd == 'I')
        {
            cin >> x;
            queue.EnQueue(x);
        }
        else if (cmd == 'O')
        {
            x = queue.GetFront();
            if (x != NIL)
            {
                cout << x << endl;
            }
            queue.DeQueue();
        }
        cin >> cmd;
    }
    queue.DestroyQueue();
    return 0;
}