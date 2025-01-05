#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1010;
const double INF = 10e9;
double p[MAXN];
double q[MAXN];
double e[MAXN][MAXN], w[MAXN][MAXN];
int n;
double cost;
double optimalBst() {
    // 初始化只包括虚拟键的子树
    for (int i = 1; i <= n + 1; i++) {
        w[i][i - 1] = q[i - 1];
        e[i][i - 1] = q[i - 1];
    }

    // 动态规划，从下到上，从左到右
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            e[i][j] = INF;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            // 求最小代价的子树的根
            for (int k = i; k <= j; k++) {
                double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
                e[i][j] = min(e[i][j], e[i][k - 1] + e[k + 1][j] + w[i][j]);
            }
        }
    }
    return e[1][n];
}

int main(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i <= n; i++) {
        cin >> q[i];
    }
    printf("%.6f\n", optimalBst());
    return 0;
}