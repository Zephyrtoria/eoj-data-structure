#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 501;
const int INF = 0x3f3f3f3f;

int maxPartner[MAXN];
int pre[MAXN];
int counts[MAXN];

class Graph {
private:
    int n;
    int partner[MAXN];
    int graph[MAXN][MAXN];

public:
    Graph(int n, int m) {
        this->n = n;
        for (int i = 1; i <= n; i++) {
            cin >> partner[i];
            maxPartner[i] = partner[i];
        }

        memset(graph, 0x3f, sizeof(graph));
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u][v] = graph[v][u] = w;
        }
    }

    void dijkstra(int s, int d) {
        int dist[MAXN];
        bool visited[MAXN];
        memset(dist, 0x3f, sizeof(dist));
        memset(visited, false, sizeof(visited));
        memset(pre, 0x3f, sizeof(pre));

        dist[s] = 0;
        pre[s] = -1;
        counts[s] = 1;
        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 1; j <= n; j++) {
                if (!visited[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }

        for (int j = 1; j <= n; j++) {
            int nextDist = dist[t] + graph[t][j];
            if (dist[j] > nextDist) {
                dist[j] = nextDist;
                counts[j] = counts[t];
                maxPartner[j] = maxPartner[t] + partner[j];
                pre[j] = t;
            } else if (dist[j] == nextDist) {
                counts[j] += counts[t];
                if (maxPartner[j] < maxPartner[t] + partner[j]) {
                    maxPartner[j] = maxPartner[t] + partner[j];
                    pre[j] = t;
                }
            }
        }
            visited[t] = true;
        }
    }
};

int main(void) {
    int n, m, s, d;
    cin >> n >> m >> s >> d;
    Graph g(n, m);
    g.dijkstra(s, d);

    cout << counts[d] << " " << maxPartner[d] << endl;

    int cur = d;
    vector<int> result;
    result.push_back(cur);
    cur = pre[cur];
    while (cur != -1) {
        result.push_back(cur);
        cur = pre[cur];
    }
    for (int i = result.size() - 1; i >= 0; i--) {
        if (i != 0) {
            cout << result[i] << ' ';
        } else {
            cout << result[i];
        }
    }

    return 0;
}