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
    int* prev;
    int cheap;

public:
    Graph(int n, int m) {
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
                graph[source][dest] = weight;
                costs[source][dest] = cost;
            }
        }
    }

    int dijkstra(int s, int d) {
        int* dist = new int[n];
        memset(dist, 0x3f, sizeof(int) * n);
        bool* visited = new bool[n];
        memset(visited, false, sizeof(bool) * n);
        prev = new int[n];
        int result = 0;

        dist[s] = 0;
        prev[s] = -1;
        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }

            if (t == -1) {
                return;
            }
            result += dist[t];

            for (int j = 0; j < n; j++) {
                if (dist[j] > dist[t] + graph[t][j]) {
                    dist[j] = dist[t] + graph[t][j];
                    prev[j] = t;
                }
            }
            visited[t] = true;
        }
        return dist[d];
    }


    int findCheapestPath(int s, int d) {
        
    }
};

int main(void) {
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    Graph g(n, m);
    cout << g.dijkstra(s, d) << " " << g.findCheapestPath(s, d) << endl;
    return 0;
}