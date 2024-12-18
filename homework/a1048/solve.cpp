#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int W = 85;
const int H = 1010;

class Graph {
private:
    int w;
    int h;
    int graph[H][W];
    int result;
    int sum;
    bool visited[H][W];
    const int fx[4]{1, -1, 0, 0};
    const int fy[4]{0, 0, 1, -1};

public:
    Graph(int w, int h) {
        this->w = w;
        this->h = h;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                char c;
                cin >> c;
                graph[i][j] = (c == '*') ? 1 : 0;
            }
        }
    }

    void bfs(int x, int y) {
        sum = 0;
        queue<pair<int, int>> q;
        q.push({x, y});
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int dx = fx[i] + cur.first, dy = fy[i] + cur.second;
                if (0 <= dx && dx < h && 0 <= dy && dy < w && !visited[dx][dy] && graph[dx][dy] == 1) {
                    sum++;
                    visited[dx][dy] = true;
                    q.push({dx, dy});
                }
            }
        }

        result = max(sum, result);
    }

    int getMaxArea() {
        result = 0;
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (!visited[i][j] && graph[i][j] == 1) {
                    bfs(i, j);
                }
            }
        }

        return result;
    }
};

int main(void) {
    int w, h;
    cin >> w >> h;
    Graph g(w, h);
    cout << g.getMaxArea() << endl;
    return 0;
}