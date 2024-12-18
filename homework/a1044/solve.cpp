#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class DSU {
private:
    vector<int> parent;
    int n;

public:
    DSU(int n_) {
        n = n_;
        for (int i = 0; i <= n; i++) {
            parent.push_back(i);
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    int maxCount() {
        // id:count
        unordered_map<int, int> map;
        int maxCount = 1;
        for (int i = 1; i <= n; i++) {
            if (map.count(parent[i]) == 0) {
                map[parent[i]] = 1;
            } else {
                map[parent[i]]++;
            }
            maxCount = max(maxCount, map[parent[i]]);
        }
        return maxCount;
    }

    void convert() {
        for (int i = 1; i <= n; i++) {
            find(i);
        }
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 1; i <= m; i++) {
        int t;
        cin >> t;
        int a = 0, b;
        while (t--) {
            if (a == 0) {
                cin >> a;
            } else {
                cin >> b;
                dsu.unite(a, b);
            }
        }
    }
    dsu.convert();
    cout << dsu.maxCount() << endl;
    return 0;
}