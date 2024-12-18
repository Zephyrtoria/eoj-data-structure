#include <iostream>
using namespace std;
#define kMaxSize 200000
#define NIL -1
typedef int ElemType;   // 元素类型
typedef int Position;  // 整型下标，表示元素的位置
class List {
private:
    ElemType *data_;  // 存储数据的数组
    Position last_;  //线性表中最后一个元素在数组中的位置
    Position maxsize_; //线性表最大容纳元素个数
public:
    struct ListException   //异常处理
    {
        std::string error_;
        ListException(std::string s): error_(s) {};
    };
    List(unsigned=kMaxSize);  //构造函数，初始化一个空的线性表
    List(const List&);
    List& operator=(const List&);
    ~List();  // 析构函数,释放线性表占用的空间

    Position Search(ElemType x);  // 在线性表中查找元素x，查找成功，返回x的位置(位序从1开始)，否则返回-1
    void Insert(Position i,ElemType x);  // 在线性表第i个位置之后插入元素x，位置从1开始
    void Remove(Position i);  // 从线性表中删除第i个位置的元素

    friend std::istream& operator>>(std::istream&, List&);  //输入一个顺序表
};



