#include <cstring>
#include <iostream>
#include <list>

using namespace std;
const int N = 1010;
const int INF = 0x3f3f3f3f;
class MST {
private:
    int n;
    int m;
    int (*graph)[N];
    int result;

public:
    MST() {
        cin >> n >> m;
        graph = new int[N][N];
        memset(graph, 0x3f, sizeof(graph));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = INF;
            }
        }
        for (int i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graph[from][to] = min(graph[from][to], weight);
            graph[to][from] = min(graph[to][from], weight);
        }
    }

    int mst() {
        if (m < n - 1) {
            return INF;
        }
        bool visited[N];
        int dist[N];
        memset(visited, false, sizeof(visited));
        memset(dist, 0x3f, sizeof(dist));
        result = 0;
        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 1; j <= n; j++) {
                if (!visited[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }
            if (i != 0 && dist[t] == INF) {
                return INF;
            }
            if (i != 0) {
                result += dist[t];
            }
            for (int j = 1; j <= n; j++) {
                dist[j] = min(dist[j], graph[t][j]);
            }
            visited[t] = true;
        }
        return result;
    }
};  

int main(void) {
    MST m;
    int result = m.mst();
    if (result == INF) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}