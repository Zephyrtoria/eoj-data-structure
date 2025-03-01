#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

class Graph {
private:
    int n;
    int** graph;
    int* count;
    vector<int> path;
    int** duplicatePath;  // 记录重复路径，虽然要丢弃小的边，但是要考虑相同权重的边

public:
    Graph(int n, int m) {
        graph = new int*[n + 1];
        duplicatePath = new int*[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new int[n + 1];
            duplicatePath[i] = new int[n + 1];
            memset(graph[i], 0x3f, sizeof(int) * (n + 1));
            for (int j = 1; j <= n; j++) {
                duplicatePath[i][j] = 1;
            }
        }

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            if (graph[u][v] == w) {
                duplicatePath[u][v]++;
                duplicatePath[v][u]++;
            } else if (graph[u][v] > w) {
                duplicatePath[u][v] = duplicatePath[v][u] = 1;
                graph[u][v] = w;
                graph[v][u] = w;
            }
        }

        this->n = n;
        count = new int[n + 1];
        memset(count, 0, sizeof(int) * (n + 1));
        count[1] = 1;
    }

    // 返回最短路径数量
    int dijkstra() {
        int result = 0;
        bool* visited = new bool[n + 1];
        int* dist = new int[n + 1];
        int* prev = new int[n + 1];
        memset(visited, false, sizeof(bool) * (n + 1));
        memset(dist, 0x3f, sizeof(int) * (n + 1));

        prev[1] = -1;
        dist[1] = 0;
        for (int i = 0; i < n; i++) {
            int t = -1;
            for (int j = 1; j <= n; j++) {
                if (!visited[j] && (t == -1 || dist[j] < dist[t])) {
                    t = j;
                }
            }

            if (t == -1) {
                return -1;
            }

            result += dist[t];
            for (int j = 1; j <= n; j++) {
                int nextDist = dist[t] + graph[t][j];
                if (dist[j] > nextDist) {
                    prev[j] = t;
                    dist[j] = nextDist;
                    count[j] = count[t] * duplicatePath[t][j];
                } else if (dist[j] == nextDist) {  // 有边相连，而且可以到达
                    // 处理权重相同的边
                    count[j] += count[t] * duplicatePath[t][j];
                }
            }

            visited[t] = true;
        }

        if (dist[n] == INF) {
            return -1;
        }

        // 计算路径
        int cur = n;
        while (cur != -1) {
            path.push_back(cur);
            cur = prev[cur];
        }

        return dist[n];
    }

    int getCount() {
        return count[n];
    }

    vector<int> getPath() {
        return path;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    int result = g.dijkstra();
    if (result == -1) {
        cout << result << endl
             << 0 << endl
             << -1 << endl;
    } else {
        cout << result << endl
             << g.getCount() << endl;
        auto path = g.getPath();
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}