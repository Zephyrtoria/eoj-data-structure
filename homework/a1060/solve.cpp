#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;

typedef struct Edge {
    int source;
    int dest;
    double rate;
    Edge(int source, int dest, double rate) {
        this->source = source;
        this->dest = dest;
        this->rate = rate;
    }
} Edge;

class Graph {
private:
    int n;
    vector<Edge*> edges;
    unordered_map<string, int> nameToId;

public:
    Graph(int n) {
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            nameToId[name] = i;
        }
        this->n = n;
    }

    int getIdByName(string& name) {
        return nameToId[name];
    }

    void insertEdge(string& source, string& dest, double rate) {
        // 将边权转为-log(rate):乘法->加法
        rate = -log(rate);
        edges.push_back(new Edge(getIdByName(source), getIdByName(dest), rate));
    }

    int bellmanFord() {
        double* dist = new double[n];
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
        }

        // 松弛边n - 1次
        for (int i = 0; i < n - 1; i++) {
            for (auto edge : edges) {
                int source = edge->source, dest = edge->dest;
                double weight = edge->rate;
                if (dist[source] + weight < dist[dest]) {
                    dist[dest] = dist[source] + weight;
                }
            }
        }

        // 尝试第n次松弛边，如果还能松弛就说明有负权环
        for (auto edge : edges) {
            int source = edge->source, dest = edge->dest;
            double weight = edge->rate;
            if (dist[source] + weight < dist[dest]) {
                return true;
            }
        }
        return false;
    }
};

int main(void) {
    int n, m;
    int t = 1;
    while (cin >> n && n != 0) {
        Graph g(n);
        cin >> m;
        for (int i = 0; i < m; i++) {
            string source, dest;
            double rate;
            cin >> source >> rate >> dest;
            g.insertEdge(source, dest, rate);
        }

        if (g.bellmanFord()) {
            cout << "Case " << t << ": Yes" << endl;
        } else {
            cout << "Case " << t << ": No" << endl;
        }
        t++;
    }
    return 0;
}