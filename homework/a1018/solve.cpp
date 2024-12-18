#include <iostream>
using namespace std;

#define ERROR (-1)    // 定义出错的返回值
using SElemSet = int; /* 栈元素类型定义为整型 */
using Position = int; /* 整型下标，表示元素的位置 */
// 判断输入的操作类型
using Operation = enum { push,
                         pop,
                         stop };

class StackArray
{
private:
    int capacity;        /* 两个顺序栈的总容量 */
    Position top1, top2; /* 两个顺序栈的栈顶指针 */
    SElemSet *data;      /* 存储数据的数组 */

public:
    StackArray(int n); // 构造函数，初始化栈
    ~StackArray();     // 析构函数，释放动态分配的内存
    StackArray();
    StackArray(const StackArray &stack);            // 深拷贝构造函数
    StackArray &operator=(const StackArray &stack); // 赋值操作符重载
    bool Push(int tag, SElemSet x);                 // Push操作，将x插入tag指定的栈中
    bool IsEmpty(int tag);                          // 判断指定的栈是否为空
    SElemSet TopPop(int tag);                       // TopPop操作，返回栈顶元素并将其移除
    void PrintStack(int tag);                       //
};

StackArray::StackArray(int n) : capacity(n), top1(0), top2(n - 1)
{
    data = new SElemSet[n]; // 分配容量为 n 的数组
}

StackArray &StackArray::operator=(const StackArray &stack)
{
    if (this != &stack)
    {                  // 检查自赋值
        delete[] data; // 释放当前对象的内存

        capacity = stack.capacity;
        top1 = stack.top1;
        top2 = stack.top2;
        data = new SElemSet[capacity]; // 为新栈分配内存
        for (int i = 0; i <= top1; ++i)
        {
            data[i] = stack.data[i]; // 复制栈1的元素
        }
        for (int i = top2; i < capacity; ++i)
        {
            data[i] = stack.data[i]; // 复制栈2的元素
        }
    }
    return *this;
}

StackArray::StackArray(const StackArray &stack)
{
    capacity = stack.capacity;
    top1 = stack.top1;
    top2 = stack.top2;
    data = new SElemSet[capacity]; // 为新栈分配内存
    for (int i = 0; i <= top1; ++i)
    {
        data[i] = stack.data[i]; // 复制栈1的元素
    }
    for (int i = top2; i < capacity; ++i)
    {
        data[i] = stack.data[i]; // 复制栈2的元素
    }
}
StackArray::~StackArray()
{
    delete[] data;
}

StackArray::StackArray()
{
    capacity = 2;                  // 默认栈容量为10
    top1 = 0;                      // 栈1的初始栈顶为-1，表示栈为空
    top2 = capacity - 1;           // 栈2的初始栈顶为容量大小，表示栈为空
    data = new SElemSet[capacity]; // 动态分配数组
}

Operation GetOp()
{
    char op[5]; // 操作最长4个字符
    std::cin >> op;
    switch (op[1])
    { // 用第2个字母区分操作
    case 'u':
        return push;
    case 'o':
        return pop;
    case 'n':
        return stop;
    default:
        return stop;
    }
}

/* 你的代码将会被嵌入在这个位置 */
bool StackArray::Push(int tag, SElemSet x)
{
    // TODO
    if (top1 > top2)
    {
        cout << "Stack Full" << endl;
        return false;
    }
    if (tag == 1)
        data[top1++] = x;
    else
        data[top2--] = x;
    return true;
}
// 说明：将元素 x 插入第 tag 栈中。注意：如果目标栈已满，Push 函数必须输出 Stack Full 并且返回 false。成功插入则返回 true。

SElemSet StackArray::TopPop(int tag)
{
    // TODO
    if (tag == 1)
    {
        if (IsEmpty(1))
            return ERROR;
        return data[--top1];
    }
    else
    {
        if (IsEmpty(2))
            return ERROR;
        return data[++top2];
    }
}
// 说明：标准栈函数 Top 和 Pop 的组合，需要将第 tag 个栈的栈顶元素从该栈中移除，并返回其值。如果第 tag 个栈是空的，则返回 ERROR。

// 打印栈内容
void StackArray::PrintStack(int tag)
{
    // TODO
    cout << "Pop from Stack ";
    if (tag == 1)
    {
        cout << "1:";
        for (int i = top1 - 1; i >= 0; i--)
            cout << ' ' << data[i];
    }
    else
    {
        cout << "2:";
        for (int i = top2 + 1; i < capacity; i++)
            cout << ' ' << data[i];
    }
    cout << endl;
}
// 说明：打印第 tag 栈的内容。输出结果，具体输出模板请按照样例。

bool StackArray::IsEmpty(int tag)
{
    // TODO
    if (tag == 1)
        return top1 == 0;
    else
        return top2 == capacity - 1;
}
// 说明：打印第 tag 个栈是否为空，如果为空返回true，否则返回false。

int main()
{
    int n, tag, x;
    std::cin >> n;
    StackArray stack(n); // 初始化栈空间
    bool done = false;   // 初始化结束标识

    while (!done)
    {
        switch (GetOp())
        {
        case push: // 执行入栈操作
            std::cin >> tag >> x;
            if (!stack.Push(tag, x))
            {
                std::cout << x << " is not in Stack " << tag << std::endl;
            }
            break;
        case pop: // 执行出栈操作
            std::cin >> tag;
            x = stack.TopPop(tag);
            if (x == ERROR)
            {
                std::cout << "Stack " << tag << " is Empty" << std::endl;
            }
            break;
        case stop: // 输入结束，打印栈元素
            stack.PrintStack(1);
            stack.PrintStack(2);
            done = true;
            break;
        default:
            break;
        }
    }
    return 0;
}