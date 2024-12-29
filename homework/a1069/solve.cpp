#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main(void) {
    int n, m;
    cin >> n >> m;
    if (n <= m) {
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        sort(arr, arr + n, cmp);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        pq.push(a);
    }

    for (int i = m; i < n; i++) {
        int a;
        cin >> a;
        if (a > pq.top()) {
            pq.pop();
            pq.push(a);
        }
    }

    int* result = new int[m];
    int end = m - 1;
    while (!pq.empty()) {
        result[end--] = pq.top();
        pq.pop();
    }
    for (int i = 0; i < m; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}