#include <cstring>
#include <iostream>
#include <list>
#include <queue>
using namespace std;
const int MAXN = 10001;
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef struct Node {
    int dest;
    int weight;
    Node(int dest, int weight) {
        this->dest = dest;
        this->weight = weight;
    }
} Node;

class Graph {
private:
    int n;
    list<Node*> graph[MAXN];
    vector<LL> counts;
    vector<int> dist;

public:
    Graph(int n, int m) {
        this->n = n;
        for (int i = 0; i <= n; i++) {
            counts.push_back(0);
            dist.push_back(INF);
        }
        for (int i = 0; i < m; i++) {
            int s, d, w;
            cin >> s >> d >> w;
            graph[s].push_back(new Node(d, w));
        }
    }

    void dijkstra(int s) {
        // 朴素版
        priority_queue<pair<int, int>> q;  // 按照离集合的距离存放
        bool* visited = new bool[n + 1];
        memset(visited, false, sizeof(bool) * (n + 1));

        q.push({0, s});
        dist[s] = 0;
        counts[s] = 1;
        while (!q.empty()) {
            int cur = q.top().second;
            q.pop();
            if (visited[cur]) {
                continue;
            }
            visited[cur] = true;

            for (auto edge : graph[cur]) {
                int next = edge->dest;
                int nextDist = edge->weight;
                if (nextDist + dist[cur] < dist[next]) {
                    dist[next] = nextDist + dist[cur];
                    counts[next] = counts[cur];
                    q.push({-dist[next], next});
                } else if (nextDist + dist[cur] == dist[next]) {
                    counts[next] += counts[cur];
                }
            }
        }
    }

    void show(int s) {
        for (int i = 1; i <= n; i++) {
            if (i == s) {
                continue;
            }
            cout << dist[i] << " " << counts[i] << endl;
        }
    }
};

int main(void) {
    int n, m, s;
    cin >> n >> m >> s;
    Graph g(n, m);
    g.dijkstra(s);
    g.show(s);
    return 0;
}