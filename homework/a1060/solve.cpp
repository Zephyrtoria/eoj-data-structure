#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef struct Node {
    int to;
    double weight;
    Node(int to_, double weight_) {
        to = to_;
        weight = weight_;
    }
} Node;
const int N = 35;

class Graph {
private:
    int n;
    list<Node*> graph[N];
    unordered_map<string, int> nameToId;
    bool flag;

public:
    Graph(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            nameToId[name] = i;
        }
    }

    int getIndexByName(string& name) {
        return nameToId[name];
    }

    void insertEdge(string& from, string& to, double weight) {
        int fromIdx = getIndexByName(from), toIdx = getIndexByName(to);
        graph[fromIdx].push_back(new Node(toIdx, weight));
    }

    bool findCycle(int start, int cur, int* state, double result, bool pass) {
        if (state[cur] == 1 && pass) {
            if (cur == start && result > 1) {
                flag = true;
            }
            return true;
        } else if (state[cur] == 2) {
            return false;
        }
        state[cur] = 1;
        for (auto e : graph[cur]) {
            findCycle(start, e->to, state, result * e->weight, true);
        }
        state[cur] = 2;
        return false;
    }

    bool arbitragePossible() {
        // 找回路，判断回路上的系数乘积是否大于1
        int* state = new int[n];
        flag = false;

        // 每个点做起点
        for (int i = 0; i < n; i++) {
            memset(state, 0, sizeof(int) * n);
            findCycle(i, i, state, 1, false);
        }

        return flag;
    }
};

int main(void) {
    int n, m;

    int count = 1;
    while (cin >> n && n != 0) {
        Graph g(n);
        cin >> m;
        for (int i = 0; i < m; i++) {
            string from, to;
            double weight;
            cin >> from >> weight >> to;
            g.insertEdge(from, to, weight);
        }
        if (g.arbitragePossible()) {
            cout << "Case " << count++ << ": Yes" << endl;
        } else {
            cout << "Case " << count++ << ": No" << endl;
        }
    }
    return 0;
}