#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1010;

class Graph {
private:
    int n;
    int *graph[N];
    bool visited[N];
    vector<int> result;

public:
    Graph(int n, int m) {
        this->n = n;

        for (int i = 1; i <= n; i++) {
            graph[i] = new int[n + 1];
            memset(graph[i], 0, sizeof(graph[i]));
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a][b] = graph[b][a] = 1;
        }
        memset(visited, false, sizeof(visited));
    }

    void dfs(int curNode) {
        result.push_back(curNode);
        visited[curNode] = true;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && graph[curNode][i] == 1) {
                dfs(i);
                result.push_back(curNode);
            }
        }
    }
    void explorePath(int s) {
        dfs(s);

        for (int i = 0, size = result.size(); i < size; i++) {
            cout << result[i] << " ";
        }

        for (int j = 1; j <= n; j++) {
            if (!visited[j]) {
                cout << '0';
                break;
            }
        }
        cout << endl;
    }
};

int main(void) {
    int n, m, s;
    cin >> n >> m >> s;
    Graph g(n, m);
    g.explorePath(s);
    return 0;
}