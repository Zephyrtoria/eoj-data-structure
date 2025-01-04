#include <cstring>
#include <iostream>
#include <queue>

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;

using namespace std;
int graph[MAXN][MAXN];
class Graph {
private:
    int n;

public:
    Graph(int n, int m) {
        this->n = n;
        memset(graph, 0x3f, sizeof(graph));
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a][b] = graph[b][a] = 1;
        }
    }

    void floyd() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] <= 6) {
                    sum++;
                }
            }
            printf("%d: %.2f%%\n", i, (double)sum / n * 100);
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    g.floyd();
    g.solve();
    return 0;
}