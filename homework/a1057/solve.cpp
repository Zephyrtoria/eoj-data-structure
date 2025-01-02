#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

typedef struct Edge {
    int source;
    int dest;
    int weight;
    bool operator<(const Edge& a) const {
        return weight < a.weight;
    }
} Edge;

class DSU {
private:
    int n;
    vector<int> parent;
    vector<int> counts;
    unordered_map<int, bool> component;

public:
    DSU(int n) {
        for (int i = 0; i <= n; i++) {
            parent.push_back(i);
            counts.push_back(1);
        }
        this->n = n;
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        parent[find(a)] = find(b);
        counts[find(b)] += counts[find(a)];
    }

    int getComponent() {
        int result = 0;
        for (int i = 1; i <= n; i++) {
            if (component.count(parent[find(i)]) == 0) {
                result++;
                component[find(i)] = true;
            }
        }
        return result;
    }
};

class Graph {
private:
    int n;
    DSU* dsu;
    priority_queue<Edge*> edges;

public:
    Graph(int n) {
        this->n = n;
        dsu = new DSU(n);
    }

    void insertEdge(int source, int dest, int weight) {
        dsu->unite(source, dest);
        edges.push(new Edge{source, dest, weight});
    }

    bool connected() {
        for (int i = 1; i < n; i++) {
            if (!dsu->same(i, i + 1)) {
                return false;
            }
        }
        return true;
    }

    int getComponent() {
        return dsu->getComponent();
    }

    void dfs(vector<vector<Edge*>>& allMST, vector<Edge*>& currentMST, vector<Edge*> remainingEdges, DSU uf, int u) {
        if (currentMST.size() == n - 1) {
            vector<Edge*> temp = currentMST;
            allMST.push_back(temp);
            return;
        }

        for (int i = u; i < n; i++) {
            auto edge = remainingEdges[i];
            int u = edge->source, v = edge->dest;
            if (!uf.same(u, v)) {
                uf.unite(u, v);
            }
        }
    }

    int kruskalWithAlternatives() {
        DSU uf(n);
        // 记录候选边
        vector<Edge*> alternatives;
        // 记录最小生成树的边
        vector<Edge*> MST;
        int cost = 0;
        while (!edges.empty()) {
            auto edge = edges.top();
            edges.pop();
            int u = edge->source, v = edge->dest, w = edge->weight;
            if (!uf.same(u, v)) {
                MST.push_back(edge);
                uf.unite(u, v);
                cost += w;
            } else {
                alternatives.push_back(edge);
            }
        }
        return cost;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int s, d, w;
        cin >> s >> d >> w;
        g.insertEdge(s, d, w);
    }

    if (!g.connected()) {
        // 不连通
        cout << "NO MST" << endl
             << g.getComponent() << endl;
    } else {
        // 连通
        // 判断有无多个最小生成树（不会）
        cout << "YES" << endl
             << g.kruskalWithAlternatives() << endl;
    }
    return 0;
}