#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class DSU {
private:
    int n;
    vector<int> parents;
    vector<int> sizes;

public:
    DSU(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) {
            parents.push_back(i);
            sizes.push_back(1);
        }
    }

    int find(int x) {
        if (x != parents[x]) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    int unite(int a, int b) {
        int fa = find(a), fb = find(b);
        if (fa == fb) {
            return sizes[fb];
        }
        parents[fa] = fb;
        sizes[fb] += sizes[fa];
        return sizes[fb];
    }
};

int main(void) {
    int T;
    cin >> T;
    while (T--) {
        unordered_map<string, int> nameToId;
        int F, idx = 1;
        cin >> F;
        DSU dsu(2 * F);
        while (F--) {
            string a, b;
            cin >> a >> b;
            int ia, ib;
            if (nameToId.count(a) == 0) {
                ia = idx;
                nameToId[a] = idx++;
            } else {
                ia = nameToId[a];
            }
            if (nameToId.count(b) == 0) {
                ib = idx;
                nameToId[b] = idx++;
            } else {
                ib = nameToId[b];
            }

            cout << dsu.unite(ia, ib) << endl;
        }
    }
    return 0;
}