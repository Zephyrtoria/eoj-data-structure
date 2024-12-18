#include <iostream>
using namespace std;

const int N = 1010;
int a[N], b[N];

int solve(int m, int n)
{
    for (int i = 0; i < m; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    // m == n below
    for (int i = 0; i < m && i < n; i++)
        if (a[i] < b[i])
            return -1;
        else if (a[i] > b[i])
            return 1;

    if (m < n)
        return -1;
    else if (m > n)
        return 1;
    return 0;
}

int main()
{
    int m, n;
    cin >> m >> n;
    int out = solve(m, n);
    cout << out << endl;
    return 0;
}
