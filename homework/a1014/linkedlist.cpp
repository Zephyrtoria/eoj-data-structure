/* #include <iostream>
using namespace std;

typedef struct node
{
    int x, y, v;
    node *next;
} node;

void insert(node *dummyHead, node *appendence)
{
    node *cur = dummyHead;
    while (cur->next != nullptr)
    {
        if (cur->next->x > appendence->x)
            break;
        
        if (cur->next->x == appendence->x)
        {
            if (cur->next->y > appendence->y)
                break;
            else if (cur->next->y == appendence->y)
            {
                cur->next->v += appendence->v;
                delete appendence;
                if (cur->next->v == 0)
                {
                    node *temp = cur->next;
                    cur->next = cur->next->next;
                    delete temp;
                }
                return;
            }
        }
        cur = cur->next;
    }
    appendence->next = cur->next;
    cur->next = appendence;
}

void show(node *dummyHead)
{
    node *cur = dummyHead->next;
    while (cur != nullptr)
    {
        cout << cur->x << " " << cur->y << " " << cur->v << endl;
        cur = cur->next;
    }
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    node *dummyHead = new node{-1, -1, -1, nullptr};
    node *cur = dummyHead;
    int n, m, N;
    cin >> n >> m >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        node *temp = new node{x, y, v, nullptr};
        cur->next = temp;
        cur = cur->next;
    }

    cin >> n >> m >> N;
    for (int i = 0; i < N; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        node *temp = new node{x, y, v, nullptr};
        insert(dummyHead, temp);
    }

    show(dummyHead);
    return 0;
}
 */