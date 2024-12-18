#include <iostream>
using namespace std;
typedef struct node
{
    int x, y, v;
} node;
int N, M;

int merge(node *A, node *B, node *C)
{
    int count = 0;
    int i = 0, j = 0;
    while (i < N && j < M)
    {
        if (A[i].x < B[j].x)
            C[count++] = A[i++];
        else if (A[i].x > B[j].x)
            C[count++] = B[j++];
        else
        {
            if (A[i].y < B[j].y)
                C[count++] = A[i++];
            else if (A[i].y > B[j].y)
                C[count++] = B[j++];
            else
            {
                C[count] = A[i++];
                C[count++].v += B[j++].v;
            }
        }
    }

    while (i < N)
    {
        C[count++] = A[i++];
    }
    while (j < M)
    {
        C[count++] = B[j++];
    }
    return count;
}

void show(node *a, int c)
{
    for (int i = 0; i < c; i++)
        cout << a[i].x << ' ' << a[i].y << ' ' << a[i].v << '\n';
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m >> N;

    node *A = new node[N];
    for (int i = 0; i < N; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        A[i] = *(new node{x, y, v});
    }

    cin >> n >> m >> M;
    node *B = new node[M];
    for (int i = 0; i < M; i++)
    {
        int x, y, v;
        cin >> x >> y >> v;
        B[i] = *(new node{x, y, v});
    }

    node *C = new node[N + M];
    int s = merge(A, B, C);
    show(C, s);
    return 0;
}