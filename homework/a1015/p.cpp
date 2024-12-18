#include <iostream>
using namespace std;

typedef struct item
{
    int x, y, v;
} item;
int main(void)
{
    int m, n, c;
    cin >> m >> n >> c;
    item *arr = new item[c];
    item *res = new item[c];
    int *location = new int[n];

    for (int i = 0; i < c; i++)
    {
        cin >> arr[i].x >> arr[i].y >> arr[i].v;
        location[arr[i].y + 1]++;
    }

    location[0] = 0;
    for (int i = 1; i < n; i++)
        location[i] = location[i] + location[i - 1];

    for (int i = 0; i < c; i++)
    {
        res[location[arr[i].y]++] = arr[i];
    }

    for (int i = 0; i < c; i++)
    {
        cout << res[i].y << ' ' << res[i].x << ' ' << res[i].v << endl;
    }

    delete arr;
    delete res;
    delete location;
    return 0;
}