#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
#define read(X) scanf("%d", &X)

const int MAXN = 501;
const int INF = 0x3f3f3f3f;
typedef struct Edge {
    int source;
    int dest;
    int weight;
    bool operator<(const Edge& o) const {
        return weight > o.weight;
    }
} Edge;

class DSU {
private:
    int n;
    vector<int> parents;
    unordered_map<int, int> components;

public:
    DSU(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) {
            parents.push_back(i);
        }
    }

    int find(int x) {
        if (x != parents[x]) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        parents[find(x)] = find(y);
    }

    int getComponents() {
        int result = 0;
        for (int i = 1; i <= n; i++) {
            if (components.count(find(i)) == 0) {
                result++;
                components[find(i)] = 1;
            }
        }
        return result;
    }
};

class Graph {
private:
    int n;
    DSU* graphConnectionUf;
    int minMst;
    vector<Edge> edges;
    vector<Edge> mst;
    vector<Edge> remainingEdges;
    vector<int> allMst;

public:
    Graph(int n) {
        this->n = n;
        graphConnectionUf = new DSU(n);
    }
    ~Graph() { delete graphConnectionUf; }

    void insertEdge(int u, int v, int w) {
        Edge e{u, v, w};
        edges.push_back(e);
        graphConnectionUf->unite(u, v);
    }

    int getComponent() {
        return graphConnectionUf->getComponents();
    }

    int kruskal() {
        priority_queue<Edge> pq;
        DSU uf(n);

        for (auto& e : edges) {
            pq.push(e);
        }

        minMst = 0;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            // cout << cur.source << " " << cur.dest << " " << cur.weight << endl;

            if (uf.same(cur.source, cur.dest)) {
                remainingEdges.push_back(cur);
            } else {
                uf.unite(cur.source, cur.dest);
                mst.push_back(cur);
                minMst += cur.weight;
            }
        }
        return minMst;
    }

    bool dfs(int cur, int target, vector<bool>& visited, int& maxEdge, vector<vector<pair<int, int>>>& adj) {
        if (cur == target) {
            return true;
        }
        visited[cur] = true;
        for (auto& edge : adj[cur]) {
            int next = edge.first;
            int weight = edge.second;
            if (!visited[next]) {
                if (dfs(next, target, visited, maxEdge, adj)) {
                    maxEdge = max(maxEdge, weight);
                    return true;
                }
            }
        }
        return false;
    }

    int findMaxEdgeInCycle(int source, int dest, vector<vector<pair<int, int>>>& adj) {
        // 使用 DFS 找到 source 和 dest 之间的路径，返回路径上的最大边权重
        vector<bool> visited(MAXN, false);
        int maxEdge = 0;
        dfs(source, dest, visited, maxEdge, adj);
        return maxEdge;
    }

    int findSecondMst() {
        vector<vector<pair<int, int>>> adj(MAXN);
        for (auto& edge : mst) {
            adj[edge.source].push_back({edge.dest, edge.weight});
            adj[edge.dest].push_back({edge.source, edge.weight});
        }

        // 枚举所有不在 MST 中的边
        int secondMinMst = INF;
        for (auto& edge : remainingEdges) {
            int maxEdge = findMaxEdgeInCycle(edge.source, edge.dest, adj);
            if (maxEdge > 0) {
                int newWeight = minMst - maxEdge + edge.weight;
                secondMinMst = min(secondMinMst, newWeight);
            }
        }
        return secondMinMst;
    }
};

int main(void) {
    int n, m;
    read(n);
    read(m);
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        read(u);
        read(v);
        read(w);
        g.insertEdge(u, v, w);
    }
    int component = g.getComponent();
    if (component != 1) {
        cout << "NO MST" << endl;
        cout << component << endl;
        return 0;
    }
    int minMst = g.kruskal();
    int secondMinMst = g.findSecondMst();
    if (minMst == secondMinMst) {
        cout << "YES" << endl
             << minMst << endl;
    } else {
        cout << "NO" << endl
             << minMst << " ";
        if (secondMinMst == INF) {
            cout << -1 << endl;
        } else {
            cout << secondMinMst << endl;
        }
    }

    return 0;
}