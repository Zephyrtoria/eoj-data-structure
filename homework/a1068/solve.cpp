#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 30001;
const int MAX_GROUP = 101;
typedef long long LL;

typedef struct Student {
    LL number;
    int score;
    int court;
    int generalRank;
    int courtRank;
} Student;
Student stu[MAXN];
int courtsRank[MAX_GROUP];
int courtsMax[MAX_GROUP];
int courtsRemain[MAX_GROUP];
bool cmp(const Student& a, const Student& b) {
    if (a.score == b.score) {
        return a.number < b.number;
    }
    return a.score > b.score;
}

int main(void) {
    int n, k;
    int end = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> stu[end].number >> stu[end].score;
            stu[end].court = i;
            end++;
        }
    }

    sort(stu, stu + end, cmp);
    int generalMax = 0, generalRank = 0;
    int remain = 1;
    for (int i = 1; i <= n; i++) {
        courtsRemain[i] = 1;
    }
    for (int i = 0; i < end; i++) {
        int score = stu[i].score;
        if (generalMax != score) {
            generalMax = score;
            generalRank += remain;
            remain = 1;
        } else {
            remain++;
        }
        stu[i].generalRank = generalRank;
        int court = stu[i].court;
        if (courtsMax[court] != score) {
            courtsMax[court] = score;
            courtsRank[court] += courtsRemain[court];
            courtsRemain[court] = 1;
        } else {
            courtsRemain[court]++;
        }
        stu[i].courtRank = courtsRank[court];
    }

    cout << end << endl;
    for (int i = 0; i < end; i++) {
        cout << stu[i].number << " " << stu[i].generalRank << " " << stu[i].court << " " << stu[i].courtRank << endl;
    }
    return 0;
}