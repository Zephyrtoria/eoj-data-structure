#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef struct Node {
    int x, y;
    int id;
} Node;

typedef struct Edge {
    int a, b;
    double dist;
    bool operator<(const Edge &e) {
        return dist < e.dist;
    }
} Edge;

class DSU {
private:
    int n;
    vector<int> parent;

public:
    DSU(int n) {
        for (int i = 0; i <= n; i++) {
            parent.push_back(i);
        }
        this->n = n;
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

class Graph {
private:
    DSU *dsu;
    Node *nodes;
    int n;

public:
    Graph(int n) {
        this->n = n;
        dsu = new DSU(n);
        nodes = new Node[n + 1];

        for (int i = 1; i <= n; i++) {
            nodes[i].id = i;
            cin >> nodes[i].x >> nodes[i].y;
        }
    }

    ~Graph() {
        delete dsu;
        delete nodes;
    }

    void insertEdge(int from, int to) {
        dsu->unite(from, to);
    }

    double distance(Node from, Node to) {
        return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
    }

    double kruskal() {
        double result = 0.0;
        vector<Edge> edges;
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                Edge e = {i, j, distance(nodes[i], nodes[j])};
                edges.push_back(e);
            }
        }

        sort(edges.begin(), edges.end());

        for (auto &edge : edges) {
            if (dsu->connected(edge.a, edge.b)) {
                continue;
            } else {
                dsu->unite(edge.a, edge.b);
                result += edge.dist;
            }
        }

        return result;
    }
};

int main(void) {
    int N, M;
    cin >> N >> M;

    // 初始化点
    Graph graph(N);

    // 插入边
    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        graph.insertEdge(from, to);
    }
    printf("%.2f\n", graph.kruskal());
    return 0;
}