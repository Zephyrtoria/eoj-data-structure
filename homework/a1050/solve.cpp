#include <cstring>
#include <iostream>
#include <list>
#include <queue>

const int N = 10010;

using namespace std;
class Graph {
private:
    int n;
    list<int> nodes[N];

public:
    Graph(int n, int m) {
        this->n = n;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            nodes[a].push_back(b);
            nodes[b].push_back(a);
        }

        /* for (int i = 1; i <= n; i++) {
            cout << i << ": ";
            for (int next : nodes[i]) {
                cout << next << ' ';
            }
            cout << endl;
        }
         */
    }

    int bfs(int index) {
        int result = 0;
        queue<int> q;
        bool *visited = new bool[n + 1];
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; i++) {
            visited[i] = false;
        }
        q.push(index);

        int count = 0;
        while (count < 7 && !q.empty()) {  // 包含自身
            int size = q.size();
            while (size--) {
                int cur = q.front();
                q.pop();
                result++;
                visited[cur] = true;
                for (int next : nodes[cur]) {
                    if (!visited[next]) {
                        q.push(next);
                    }
                }
            }
            count++;
        }
        delete visited;
        return result;
    }

    void getSixthSpace() {
        for (int i = 1; i <= n; i++) {
            printf("%d: %.2f%%\n", i, (double)bfs(i) / n * 100);
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph solve(n, m);
    solve.getSixthSpace();
    return 0;
}