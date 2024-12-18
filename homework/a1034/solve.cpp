#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int N = 200010;
int group[N];
bool st[N];

queue<int> mapQ;
queue<int> allQ[N];

void enqueue(int x)
{
    if (st[x])
        return;
    st[x] = true;

    int groupId = group[x];
    if (allQ[groupId].empty())
    {
        allQ[groupId].push(x);
        mapQ.push(groupId);
    }
    else
    {
        allQ[groupId].push(x);
    }
}

int dequeue()
{
    if (mapQ.empty())
        return -1;

    int groupId = mapQ.front();
    int res = allQ[groupId].front();
    allQ[groupId].pop();
    if (allQ[groupId].empty())
        mapQ.pop();

    st[res] = false;
    return res;
}

int main(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> group[i];
    }

    int T;
    cin >> T;
    while (T--)
    {
        string choice;
        cin >> choice;
        if (choice[0] == 'E')
        {
            int x;
            cin >> x;
            enqueue(x);
        }
        else
        {
            cout << dequeue() << endl;
        }
    }
    return 0;
}