#include <iostream>
using namespace std;

class DSU {
private:
    int n;
    int* parent;

public:
    DSU(int n) {
        this->n = n;
        int size = n * 2;
        parent = new int[size + 1];
        for (int i = 1; i <= size; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa == fb) {
            return;
        }
        parent[fa] = fb;
    }
};

int main(void) {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        DSU dsu(n);

        while (m--) {
            char choice;
            int a, b;
            cin >> choice >> a >> b;
            if (choice == 'Q') {
                // 查询团伙
                if (dsu.same(a, b)) {
                    cout << "In the same gang." << endl;
                } else if (dsu.same(a, b + n)) {
                    // dsu.same(a, b + n) == dsu.same(a + n, b)
                    cout << "In different gangs." << endl;
                } else {
                    cout << "Not sure yet." << endl;
                }
            } else {
                // 添加敌对关系
                dsu.unite(a, b + n);
                dsu.unite(b, a + n);
            }
        }
    }

    return 0;
}