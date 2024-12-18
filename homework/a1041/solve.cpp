#include <bits/stdc++.h>
using namespace std;

struct compare {
    bool operator() (int a, int b) {
        return a > b;
    }
};


int main(void) {
    priority_queue<int, vector<int>, compare> q;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        q.push(a);
    }

    int result = 0;
    while (q.size() != 1) {
        int a = q.top();
        q.pop();
        int b = q.top();
        q.pop();
        result += a + b;
        q.push(a + b);
        
    }
    cout << result << endl;
    return 0;
}