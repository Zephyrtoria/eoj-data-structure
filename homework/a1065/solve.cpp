#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 101;

typedef struct Edge {
    int source;
    int dest;
    int weight;
} Edge;

typedef struct Node {
    int id;
    list<Edge> outEdge;
    list<Edge> inEdge;
    Node(int id_) {
        id = id_;
    }
} Node;

class Graph {
private:
    int n;
    vector<Node> graph;
    vector<int> inEdges;
    int totalTime;

public:
    Graph(int n) {
        for (int i = 0; i <= n; i++) {
            Node cur(i);
            graph.push_back(cur);
            inEdges.push_back(0);
        }
        this->n = n;
    }

    void insertEdge(int s, int d, int w) {
        Edge edge{s, d, w};
        graph[s].outEdge.push_back(edge);
        graph[d].inEdge.push_back(edge);
        inEdges[d]++;
    }

    vector<int> topologicalSort() {
        vector<int> topological;
        queue<int> q;

        for (int i = 1; i <= n; i++) {
            if (inEdges[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            topological.push_back(cur);

            for (auto& edge : graph[cur].outEdge) {
                int dest = edge.dest;
                inEdges[dest]--;
                if (inEdges[dest] == 0) {
                    q.push(dest);
                }
            }
        }
        return topological;
    }

    vector<pair<int, int>> criticalPath() {
        auto topological = topologicalSort();
        vector<pair<int, int>> path;
        if (topological.empty()) {
            return path;
        }

        vector<int> earliest(n + 1, 0);
        int maxTime = 0;
        for (int i = 0; i < n; i++) {
            int node = topological[i];
            for (auto& edge : graph[node].outEdge) {
                earliest[edge.dest] = max(earliest[edge.dest], earliest[node] + edge.weight);
                maxTime = max(maxTime, earliest[edge.dest]);
            }
        }
        totalTime = maxTime;

        vector<int> latest(n + 1, maxTime);
        for (int i = n - 1; i >= 0; i--) {
            int node = topological[i];
            for (auto& edge : graph[node].inEdge) {
                latest[edge.source] = min(latest[edge.source], latest[node] - edge.weight);
            }
        }

        for (int i = 0; i < n; i++) {
            int node = topological[i];
            if (earliest[node] == latest[node]) {
                for (auto& edge : graph[node].outEdge) {
                    if (earliest[edge.dest] == latest[edge.dest]) {
                        path.push_back(make_pair(node, edge.dest));
                    }
                }
            }
        }
        return path;
    }

    int getTotalTime() {
        return totalTime;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.insertEdge(u, v, w);
    }
    auto criticalPath = graph.criticalPath();
    if (criticalPath.empty()) {
        cout << 0 << endl;
        return 0;
    }
    cout << graph.getTotalTime() << endl;
    for (auto& a : criticalPath) {
        cout << a.first << "->" << a.second << endl;
    }
    return 0;
}
