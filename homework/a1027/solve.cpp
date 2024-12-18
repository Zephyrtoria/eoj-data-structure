#include <iostream>

class Queue
{
private:
    struct Node
    {
        int citizen;
        Node *next;
        Node(int c) : citizen(c), next(nullptr) {}
    };

    Node *front; // 队列的头指针
    Node *rear;  // 队列的尾指针

public:
    Queue();                          // 无参构造函数
    Queue(const Queue &q);            // 拷贝构造函数
    Queue &operator=(const Queue &q); // 赋值运算符重载
    ~Queue();                         // 析构函数

    bool isEmpty() const;
    void enqueueFront(int citizen);
    void enqueueRear(int citizen);
    int dequeue();
    void remove(int citizen);
};

// 无参构造函数
Queue::Queue() : front(nullptr), rear(nullptr) {}

// 拷贝构造函数
Queue::Queue(const Queue &q)
{
    front = rear = nullptr; // 初始化为空队列
    Node *temp = q.front;   // 从源队列的头开始遍历
    while (temp != nullptr)
    {
        enqueueRear(temp->citizen); // 逐个复制节点
        temp = temp->next;
    }
}

// 赋值运算符重载
Queue &Queue::operator=(const Queue &q)
{
    if (this != &q)
    {
        // 清空当前队列
        while (!isEmpty())
        {
            dequeue();
        }

        // 复制源队列
        Node *temp = q.front;
        while (temp != nullptr)
        {
            enqueueRear(temp->citizen);
            temp = temp->next;
        }
    }
    return *this;
}

// 析构函数
Queue::~Queue()
{
    while (front != nullptr)
    {
        Node *temp = front;
        front = front->next;
        delete temp;
    }
}

/* 你的代码将会被嵌入在这个位置 */
bool Queue::isEmpty() const
{
    // TODO
    return front == nullptr;
}
// 说明：检查队列是否为空，若为空，则返回 true，否则返回 false。

void Queue::enqueueFront(int citizen)
{
    // TODO
    if (isEmpty())
    {
        front = rear = new Node(citizen);
        return;
    }

    Node *newFront = new Node(citizen);
    newFront->next = front;
    front = newFront;
}
// 说明：从队列前端插入元素 citizen。

void Queue::enqueueRear(int citizen)
{
    // TODO
    if (isEmpty())
    {
        front = rear = new Node(citizen);
        return;
    }

    rear->next = new Node(citizen);
    rear = rear->next;
}
// 说明：从队列后端插入元素 citizen。

int Queue::dequeue()
{
    // TODO
    if (isEmpty())
    {
        return -1;
    }
    int result = front->citizen;

    Node *temp = front;
    front = front->next;
    delete temp;

    return result;
}
// 说明：从队列前端移除并返回元素。如果队列为空，返回 -1 表示错误。

void Queue::remove(int citizen)
{
    // TODO
    if (isEmpty())
        return;
    Node *cur = new Node(-1);
    cur->next = front;
    while (cur->next != nullptr)
    {
        if (cur->next->citizen == citizen)
        {
            Node *temp = cur->next;
            if (temp == front && temp == rear)
            {
                front = rear = nullptr;
            }
            else if (temp == front)
            {
                front = front->next;
            }
            else if (temp == rear)
            {
                rear = cur;
            }
            else
            {
                cur->next = cur->next->next;
            }
            delete temp;
            return;
        }
        cur = cur->next;
    }
}
// 说明：从队列中移除指定的元素 citizen。

int main()
{
    int caseCount = 0;
    int P, C;
    while (std::cin >> P >> C)
    {
        if (P == 0 && C == 0)
        {
            break;
        }

        caseCount++;
        std::cout << "Case " << caseCount << ":" << std::endl;

        Queue queue;
        for (int i = 1; i <= (P < C ? P : C); i++)
        {
            queue.enqueueRear(i);
        }

        int citizen;
        for (int i = 0; i < C; i++)
        {
            char command;
            std::cin >> command;
            if (command == 'N')
            {
                citizen = queue.dequeue();
                std::cout << citizen << std::endl;
                queue.enqueueRear(citizen);
            }
            else if (command == 'E')
            {
                int x;
                std::cin >> x;
                queue.remove(x);
                queue.enqueueFront(x);
            }
        }
    }

    return 0;
}