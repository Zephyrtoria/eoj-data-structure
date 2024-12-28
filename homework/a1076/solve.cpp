#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;
class Graph {
private:
    int n;
    int** graph;

public:
    Graph(int n, int m, int c) {
        this->n = n;
        graph = new int*[n + 1];
        // graph[n] 作为虚拟节点
        for (int i = 0; i <= n; i++) {
            graph[i] = new int[n + 1];
            memset(graph[i], 0x3f, sizeof(int) * (n + 1));
        }
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            graph[n][i] = v;
            graph[i][n] = v;
        }
        for (int i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graph[from - 1][to - 1] = min(graph[from - 1][to - 1], weight * c);
            graph[to - 1][from - 1] = min(graph[to - 1][from - 1], weight * c);
        }
    }

    int prim() {
        int result = 0;
        bool* visited = new bool[n + 1];
        memset(visited, false, sizeof(bool) * (n + 1));
        int* dist = new int[n + 1];
        memset(dist, 0x3f, sizeof(int) * (n + 1));

        // n + 1 个点
        dist[0] = 0;
        for (int i = 0; i <= n; i++) {
            int t = -1;
            for (int j = 0; j <= n; j++) {
                if (!visited[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }

            if (t == -1) {
                return INF;
            }

            result += dist[t];
            for (int j = 0; j <= n; j++) {
                dist[j] = min(dist[j], graph[t][j]);
            }
            visited[t] = true;
        }
        return result;
    }
};

int main() {
    int n, m, c;
    cin >> n >> m >> c;
    Graph g(n, m, c);
    cout << g.prim() << endl;
    return 0;
}