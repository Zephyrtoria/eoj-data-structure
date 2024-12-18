#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
/*
在这里添加了额外的代码，用于检测可能发生的内存泄漏。
Node 和 CircularQueue 中也添加了部分代码用于检测，这不影响你的正常做题。
*/
struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};
class CircularQueue
{
private:
    const char *error_msg;
    Node *rear; // 仅使用尾指针
public:
    // 构造函数
    CircularQueue();
    // 拷贝构造函数
    CircularQueue(const CircularQueue &other);
    // 赋值操作符重载
    CircularQueue &operator=(const CircularQueue &other);
    // 析构函数
    ~CircularQueue();
    // 入队
    void enqueue(int val);
    // 出队
    void dequeue();
    // 获取队头元素
    int front() const;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    CircularQueue q;
    int n;
    std::cin >> n;
    int opt;
    while (n--)
    {
        std::cin >> opt;
        if (opt == 1) // enqueue
        {
            int x;
            std::cin >> x;
            q.enqueue(x);
        }
        else if (opt == 2) // dequeue
        {
            try
            {
                q.dequeue();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else if (opt == 3) // get front
        {
            try
            {
                int x = q.front();
                std::cout << x << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }
    /*
    在这里进行内存泄漏检测
    如果检测到了内存泄露，则会抛出异常。
    你将会得到 Runtime Error 的评测结果
    */
    return 0;
}

void CircularQueue::dequeue()
{
    if (rear == nullptr) /*判断队列为空*/
    {
        // 抛出异常
        throw std::out_of_range(error_msg);
    }
    /*
    在这里完成出队操作
    */
    if (rear->next == rear)
    {
        Node *temp = rear;
        delete temp;
        rear = nullptr;
        return;
    }

    Node *temp = rear->next;
    rear->next = temp->next;
    delete temp;
}