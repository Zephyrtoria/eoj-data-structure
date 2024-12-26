#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
    priority_queue<int, vector<int>, greater<int>> emb;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (i < m) {
            emb.push(a);
        } else {
            if (a > emb.top()) {
                emb.pop();
                emb.push(a);
            }
        }
    }

    int len = min(n, m);
    int result[len];
    for (int i = 0; i < len; i++) {
        result[i] = emb.top();
        emb.pop();
    }
    for (int i = len - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}