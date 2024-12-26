#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

const int INF = 0x3f3f3f3f;
class Graph {
private:
    int n;
    int** graph;
    int** dist;
    unordered_map<string, int> ipToId;

public:
    Graph(int n, int m) {
        this->n = n;
        int count = 0;
        graph = new int*[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new int[n];
            memset(graph[i], 0x3f, sizeof(int) * n);
        }

        for (int i = 0; i < m; i++) {
            string a, b;
            int cost;
            cin >> a >> b >> cost;
            if (ipToId.count(a) == 0) {
                ipToId[a] = count++;
            }
            if (ipToId.count(b) == 0) {
                ipToId[b] = count++;
            }
            int ia = ipToId[a], ib = ipToId[b];
            graph[ia][ib] = graph[ib][ia] = cost;
        }
    }

    int getShortestPath(string from, string to) {
        if (ipToId.count(from) == 0 || ipToId.count(to) == 0) {
            return INF;
        }
        int ifrom = ipToId[from], ito = ipToId[to];
        return dist[ifrom][ito];
    }

    void Flody() {
        dist = new int*[n];
        for (int i = 0; i < n; i++) {
            dist[i] = new int[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = graph[i][j];
            }
            dist[i][i] = 0;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    g.Flody();
    int t;
    cin >> t;
    while (t--) {
        string from, to;
        cin >> from >> to;
        int result = g.getShortestPath(from, to);
        result = (result == INF) ? -1 : result;
        cout << result << endl;
    }
    return 0;
}