#include <cstring>
#include <iostream>

using namespace std;

const int INF = 0x3f3f3f3f;

class Graph {
private:
    int n;
    int** graph;
    int resultLength;

public:
    Graph(int n, int m) {
        this->n = n;
        graph = new int*[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new int[n + 1];
            memset(graph[i], 0x3f, sizeof(int) * (n + 1));
            graph[i][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graph[from][to] = min(graph[from][to], weight);
            graph[to][from] = min(graph[to][from], weight);
        }
    }

    bool Floyd() {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] == INF) {
                    return false;
                }
            }
        }
        return true;
    }

    int findMaxInLine(int line) {
        int result = 0;
        for (int i = 1; i <= n; i++) {
            if (graph[line][i] == INF) {
                return 0;
            }
            result = max(result, graph[line][i]);
        }
        return result;
    }

    int getResultId() {
        int id = 0;
        resultLength = INF;
        for (int i = 1; i <= n; i++) {
            int curLineMax = findMaxInLine(i);
            if (curLineMax < resultLength) {
                id = i;
                resultLength = curLineMax;
            }
        }
        return id;
    }

    int getResultLength() {
        return resultLength;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    if (!g.Floyd()) {
        cout << 0 << endl;
        return 0;
    }
    cout << g.getResultId() << " " << g.getResultLength() << endl;
    return 0;
}