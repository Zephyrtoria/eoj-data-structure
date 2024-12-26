#include <iostream>
#include <vector>
using namespace std;

bool isBST(int* arr, int l, int r) {
    
}

int main() {
    int n;
    cin >> n;

    while (n--) {
        int m;
        cin >> m;
        int* arr = new int[m];
        for (int i = 0; i < m; i++) {
            cin >> arr[i];
        }

        if (isBST(arr, 1, 2)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}