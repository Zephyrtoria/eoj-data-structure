#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;

class Graph {
private:
    int n;
    int** graph;
    int** costs;
    int* minCost;

public:
    Graph(int n, int m) {
        this->n = n;
        graph = new int*[n];
        costs = new int*[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new int[n];
            costs[i] = new int[n];
            memset(graph[i], 0x3f, sizeof(int) * n);
        }
        for (int i = 0; i < m; i++) {
            int source, dest, weight, cost;
            cin >> source >> dest >> weight >> cost;
            if (graph[source][dest] > weight) {
                graph[source][dest] = graph[dest][source] = weight;
                costs[source][dest] = costs[dest][source] = cost;
            }
            minCost = new int[n];
            memset(minCost, 0x3f, sizeof(int) * n);
        }
    }

    int dijkstra(int s, int d) {
        int* dist = new int[n];
        memset(dist, 0x3f, sizeof(int) * n);
        bool* visited = new bool[n];
        memset(visited, false, sizeof(bool) * n);

        dist[s] = 0;
        minCost[s] = 0;
        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }

            if (t == -1) {
                return -1;
            }

        for (int j = 0; j < n; j++) {
            if (dist[j] > dist[t] + graph[t][j]) {
                dist[j] = dist[t] + graph[t][j];
                minCost[j] = minCost[t] + costs[t][j];
            } else if (dist[j] == dist[t] + graph[t][j]) {
                minCost[j] = min(minCost[j], minCost[t] + costs[t][j]);
            }
        }
            visited[t] = true;
        }
        return dist[d];
    }

    int getMinCost(int d) {
        return minCost[d];
    }
};

int main(void) {
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    Graph g(n, m);
    cout << g.dijkstra(s, d) << " " << g.getMinCost(d) << endl;
    return 0;
}