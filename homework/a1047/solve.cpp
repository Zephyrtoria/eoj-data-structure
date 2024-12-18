#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int N = 1010;


class DSU {
    private:
    int n;
    vector<int> parents;
    public:
    void create(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) {
            parents.push_back(i);
        }
    }
    int find(int x) {
        if (x != parents[x]) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    void unite(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa == fb) {
            return;
        }
        parents[fa] = fb;
    }

    bool isConnected() {
        int record = find(1);
        for (int i = 1; i <= n; i++) {
            if (find(i) != record) {
                return false;
            }
        }
        return true;
    }

    void show() {
        for (int i = 1; i <= n; i++) {
            cout << parents[i] << " ";
        }
        cout << endl;
    }
};

class Graph {
    private:
    DSU dsu;
    int n;
    int m;
    list<int> graph[N];    

    public:
    Graph(int n, int m) {
        this->n = n;
        this->m = m;
        dsu.create(n);
    }

    void insertEdge(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
        dsu.unite(a, b);
    }

    int eulerExist() {
        if (!dsu.isConnected()) {
            return 0;
        }
        for (int i = 1; i <= n; i++) {
            if (graph[i].size() % 2 != 0) {
                return 0;
            }
        }
        return 1;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g.insertEdge(a, b);
    }
    cout << g.eulerExist() << endl;
    return 0;
}