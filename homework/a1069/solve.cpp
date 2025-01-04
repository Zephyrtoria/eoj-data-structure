#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

void quickSort(int* arr, int l, int r, int k) {
    if (l >= r) {
        return;
    }
    int x = arr[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do {
            i++;
        } while (arr[i] > x);
        do {
            j--;
        } while (arr[j] < x);
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    int sl = j - l + 1;
    if (k <= sl) {
        quickSort(arr, l, j, k);
    } else {
        quickSort(arr, j + 1, r, k - sl);
    }
}

int main(void) {
    int n, m;
    cin >> n >> m;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (n <= m) {
        sort(arr, arr + n, cmp);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return 0;
    }

    quickSort(arr, 0, n - 1, m);
    sort(arr, arr + m, cmp);
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}