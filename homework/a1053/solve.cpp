#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

struct compare {
    bool operator()(LL a, LL b) {
        return a > b;
    }
};

int main(void) {
    int n;
    cin >> n;
    priority_queue<LL, vector<LL>, compare> pq;

    for (int i = 0; i < n; i++) {
        LL a;
        cin >> a;
        pq.push(a);
    }

    LL result = 0;
    while (pq.size() > 1) {
        LL a = pq.top();
        pq.pop();
        LL b = pq.top();
        pq.pop();
        LL c = a + b;
        result += c;
        pq.push(c);
    }
    result += pq.top();
    cout << result << endl;
    return 0;
}