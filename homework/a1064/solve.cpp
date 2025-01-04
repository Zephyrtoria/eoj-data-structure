#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 101;
const int INF = 0x3f3f3f3f;

class Graph {
private:
    int n;
    int graph[MAXN][MAXN];

public:
    Graph(int n) {
        this->n = n;
        memset(graph, 0x3f, sizeof(graph));
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int s;
                cin >> s;
                graph[s][i] = 1;
            }
        }
    }

    bool topologicalSort() {
        vector<int> topoResult;
        queue<int> q;
        bool visited[MAXN];
        memset(visited, false, sizeof(visited));

        for (int i = 1; i <= n; i++) {
            bool hasInEdge = false;
            for (int j = 1; j <= n; j++) {
                if (graph[j][i] == 1) {
                    hasInEdge = true;
                }
            }
            if (!hasInEdge) {
                q.push(i);
                visited[i] = true;
            }
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            topoResult.push_back(cur);

            // 删除出边
            for (int j = 1; j <= n; j++) {
                graph[cur][j] = INF;
            }

            for (int i = 1; i <= n; i++) {
                if (visited[i]) {
                    continue;
                }
                bool hasInEdge = false;
                for (int j = 1; j <= n; j++) {
                    if (graph[j][i] == 1) {
                        hasInEdge = true;
                        break;
                    }
                }
                if (!hasInEdge) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        return topoResult.size() == n;
    }
};

int main(void) {
    int n;
    cin >> n;
    Graph g(n);
    if (g.topologicalSort()) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    return 0;
}