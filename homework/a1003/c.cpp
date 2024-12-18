#include <iostream>
using namespace std;

#define MAX_SIZE 100000
#define NIL -1

typedef int ElemType; // 元素类型，本题中定义元素类型为整型
typedef int Position; // 元素位置，这里我们用元素在线性表存储数据的数组中的下标表示元素位置

class List
{
private:
    ElemType *_data; // 存储数据的数组，数据从下标为 0 的位置开始存储
    Position _last;  // 线性表中最后一个元素在数组中的下标，注意数组的下标从 0 开始
    int _max_size;   // 线性表最大能容纳的元素个数
public:
    struct ListException // 异常处理
    {
        std::string error;
        ListException(std::string s) : error(s) {};
    };
    List(unsigned = MAX_SIZE); // 构造函数，初始化一个空的线性表，根据指定的最大长度分配连续的内存空间
    List(const List &);
    List &operator=(const List &);
    ~List(); // 析构函数，释放线性表占用的空间

    Position search(ElemType x);           // 在线性表中查找元素 x
    bool insert(Position idx, ElemType x); // 在线性表下标为 idx 的位置插入元素 x
    ElemType remove(Position idx);         // 删除线性表中下标为 idx 的元素

    friend std::istream &operator>>(std::istream &, List &); // 读入一个线性表
};

int main()
{
    List ls;   // 创建线性表
    cin >> ls; // 读入线性表
    int q, cmd, idx, x;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> cmd;
        if (cmd == 1)
        {
            cin >> x;
            cout << ls.search(x) << endl; // 查找下标为 k 的元素，并输出结果
        }
        else if (cmd == 2)
        {
            cin >> idx >> x;
            cout << ls.insert(idx, x) << endl; // 将元素 x 插入到下标为 k 的位置，并输出结果
        }
        else if (cmd == 3)
        {
            cin >> idx;
            cout << ls.remove(idx) << endl; // 删除下标为 k 的元素，并输出结果
        }
        else
        {
            throw "Error: Invalid command!"; // 无效的操作，抛出异常
        }
    }
    return 0;
}

List::List(unsigned list_size)
{
    _data = new ElemType[list_size]{0};
    _last = -1;
    _max_size = list_size;
}

List::List(const List &li) // Makes a deep copy of the original List.
{
    _data = new ElemType[li._max_size]{0};
    _max_size = li._max_size;
    _last = li._last;
    for (int i = 0; i <= _last; i++)
    {
        _data[i] = li._data[i];
    }
}

List &List::operator=(const List &li)
{
    if (this != &li)
    {
        delete[] _data;
        _data = new ElemType[li._max_size]{0};
        _max_size = li._max_size;
        _last = li._last;
        for (int i = 0; i <= _last; i++)
        {
            _data[i] = li._data[i];
        }
    }
    return *this;
}

List::~List()
{
    delete[] _data;
    _last = NIL;
}

std::istream &operator>>(std::istream &is, List &li)
{
    int n;
    std::cin >> n;

    if (n < 0)
    {
        throw List::ListException("Error: Invalid list length!");
    }

    if (n > (li._max_size))
    { // 插入元素个数大于线性表的最大容量，抛出异常
        throw List::ListException("Error: The number of inserted elements exceeds the maximum capacity!");
    }

    li._last = n - 1;

    for (int i = 0; i < n; i++)
    {
        std::cin >> li._data[i];
    }
    return is;
}

/**
 * 【线性表查找操作】
 * @param  x   [目标元素的值 x]
 * @return     [存在值为 x 的元素则返回其第一次出现的下标，否则返回 NIL]
 */
Position List::search(ElemType x)
{
    // TODO
    for (Position i = 0; i <= _last; i++)
    {
        if (_data[i] == x)
        {
            return i;
        }
    }
    return NIL;
}

/**
 * 【线性表插入操作】
 * @param  idx [插入元素的位置（以下标表示） idx]
 * @param  x   [被插入的元素值 x]
 * @return     [返回是否成功执行插入操作]
 */
bool List::insert(Position idx, ElemType x)
{
    // TODO
    if (idx < 0 || idx > _last + 1 || _last == _max_size - 1)
        return false;
    for (Position i = _last; i >= idx; i--)
    {
        _data[i + 1] = _data[i];
    }
    _data[idx] = x;
    _last++;
    return true;
}

/**
 * 【线性表删除操作】
 * @param  idx [被删除的元素下标 idx]
 * @return     [成功执行则返回被删除的元素的值，否则返回 NIL]
 */
ElemType List::remove(Position idx)
{
    // TODO
    if (idx < 0 || idx > _last)
        return NIL;

    ElemType res = _data[idx];
    for (int i = idx; i < _last; i++)
    {
        _data[i] = _data[i + 1];
    }
    _last--;
    return res;
}
