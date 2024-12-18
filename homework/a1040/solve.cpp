#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int arr[N];
int n;

void search(int a, int b) {
    if (arr[a] == 0) {
        cout << "ERROR: T[" << a << "] is NULL" << endl;
        return;
    } else if (arr[b] == 0) {
        cout << "ERROR: T[" << b << "] is NULL" << endl;
        return;
    }

    int prta = a;
    int prtb = b;
    while (prta > 0 && prtb > 0) {
        if (prta == prtb) {
            cout << prta << " " << arr[prta] << endl;
            return;
        } else if (prta > prtb) {
            prta /= 2;
        } else {
            prtb /= 2;
        }
    }
}

int main(void) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int a, b;
    cin >> a >> b;
    search(a, b);

    return 0;
}