#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

typedef struct {
    LL id;
    int score;
    int totalRank;
    int number;
    int partRank;
} Stu;
const int N = 110;

int main(void) {
    int n;
    cin >> n;
    vector<Stu> vs[n];
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            LL a;
            int b;
            cin >> a >> b;
            
            vs[i].push_back()
        }
    }
}