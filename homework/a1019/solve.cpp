#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
class Solution
{
public:
    struct Node
    {                    // Node为链式存储的栈内结点类
        int element_;    // 结点存储的元素
        Node *next_;     // 下一个结点地址（自顶向下）
        Node() = delete; // 创建结点必须指定元素值和下一个结点地址
        Node(int element, Node *next) : element_(element), next_(next) {}
    };
    static void Solve()
    { // 对一个序列进行判断，输出结果
        int n;
        std::cin >> n;
        std::string out_seq;
        std::cin >> out_seq;
        MyStackAndGetAns::GetAns(n, out_seq);
    }

private:
    class MyStackAndGetAns
    { // 栈的实现和答案输出
    public:
        MyStackAndGetAns()
        { // 构造函数，重置栈顶和栈内元素个数
            top_ = nullptr;
            size_ = 0;
        }
        virtual ~MyStackAndGetAns()
        { // 析构函数，清空栈
            while (top_ != nullptr)
            {
                Node *next = top_->next_;
                delete top_;
                top_ = next;
                assert(size_ > 0);
                size_--;
            }
            assert(size_ == 0);
        }

        /* 你的代码将会被嵌入在这个位置 */
        void Push(int element)
        {
            // TODO
            Node *newNode = new Node(element, top_);
            top_ = newNode;
            size_++;
        }
        int Top()
        {
            // TODO
            return top_->element_;
        }
        void Pop()
        {
            // TODO
            Node *temp = top_;
            top_ = top_->next_;
            size_--;
            delete temp;
        }
        bool Empty()
        {
            // TODO
            return size_ == 0;
        }
        static void GetAns(int n, std::string out_seq)
        {
            // TODO
            MyStackAndGetAns stack = MyStackAndGetAns();
            int count = 1;
            for (int i = 0, size = out_seq.size(); i < size; i++)
            {
                while (count <= n && (stack.Empty() || stack.Top() != out_seq[i] - '0'))
                {
                    stack.Push(count);
                    count++;
                }
                // stack.Top() == out_seq[i] - '0'
                if (stack.Top() == out_seq[i] - '0')
                    stack.Pop();
                else
                {
                    std::cout << "no" << std::endl;
                    return;
                }
            }
            std::cout << "yes" << std::endl;
        }

    private:
        size_t size_; // 栈内元素数量
        Node *top_;   // 栈顶指针
    };
};

int main()
{
    int k;
    std::cin >> k;
    while (k--)
    {
        Solution::Solve();
    }
    return 0;
}