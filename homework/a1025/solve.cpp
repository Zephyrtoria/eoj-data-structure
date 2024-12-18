#include <iostream>
#include <string>
using namespace std;

class CircularQueue
{
private:
    int *data;    // 存储队列元素的数组
    int front;    // 队列头部索引
    int rear;     // 队列尾部索引
    int size;     // 当前队列中的元素数量
    int capacity; // 队列的最大容量（包括一个额外的空间用于区分队列满和空）

public:
    CircularQueue(int capacity);                          // 构造函数，初始化队列
    CircularQueue(const CircularQueue &other);            // 拷贝构造函数
    CircularQueue &operator=(const CircularQueue &other); // 赋值运算符重载
    ~CircularQueue();                                     // 析构函数，释放动态分配的内存
    bool isFull();                                        // 判断队列是否已满
    bool isEmpty();                                       // 判断队列是否为空
    int enqueue(int x);                                   // 入队操作，返回0表示成功，返回-1表示队列已满
    int dequeue();                                        // 出队操作，返回出队元素，返回-1表示队列为空
};

CircularQueue::CircularQueue(int capacity)
{
    this->capacity = capacity + 1; // 多一个空间用于区分队列满和空
    data = new int[this->capacity];
    front = 0;
    rear = 0;
    size = 0;
}

CircularQueue::CircularQueue(const CircularQueue &other)
{
    capacity = other.capacity;
    data = new int[capacity];
    front = other.front;
    rear = other.rear;
    size = other.size;
    for (int i = 0; i < capacity; ++i)
    {
        data[i] = other.data[i];
    }
}

CircularQueue &CircularQueue::operator=(const CircularQueue &other)
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        data = new int[capacity];
        front = other.front;
        rear = other.rear;
        size = other.size;
        for (int i = 0; i < capacity; ++i)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

CircularQueue::~CircularQueue()
{
    delete[] data;
}

bool CircularQueue::isFull()
{
    return (rear + 1) % capacity == front;
}

bool CircularQueue::isEmpty()
{
    return front == rear;
}

/*你的代码会被嵌入在这个位置*/

int CircularQueue::enqueue(int x)
{
    // TODO
    if (isFull())
        return -1;

    data[rear] = x;
    rear = (rear + 1) % capacity;
    return x;
}
int CircularQueue::dequeue()
{
    // TODO
    if (isEmpty())
        return -1;
    int res = data[front];
    front = (front + 1) % capacity;
    return res;
}

int main()
{
    int q;
    cin >> q;
    CircularQueue queue(100001);

    for (int i = 0; i < q; ++i)
    {
        string operation;
        cin >> operation;
        if (operation == "enqueue")
        {
            int x;
            cin >> x;
            if (queue.enqueue(x) == -1)
            {
                cout << "Full" << endl;
            }
        }
        else if (operation == "dequeue")
        {
            int result = queue.dequeue();
            if (result == -1)
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << result << endl;
            }
        }
    }

    return 0;
}