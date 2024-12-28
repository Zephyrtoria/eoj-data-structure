#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long LL;
typedef struct Node {
    LL c;
    LL v;
    bool operator<(Node n) const {
        return v < n.v;
    }
} Node;

bool cmp(Node& a, Node& b) {
    return a.c < b.c;
}

const int N = 1000010;
Node nodes[N];

int main(void) {
    int n, k;
    LL w;
    cin >> n >> w >> k;
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].c >> nodes[i].v;
    }

    sort(nodes, nodes + n, cmp);

    int end = 0;
    priority_queue<Node> pq;
    while (k--) {
        while (end < n && nodes[end].c <= w) {
            pq.push(nodes[end]);
            end++;
        }
        if (pq.empty()) {
            continue;
        }
        w += pq.top().v;
        pq.pop();
    }
    cout << w << endl;
    return 0;
}