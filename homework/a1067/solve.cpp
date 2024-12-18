#include <iostream>
#include <vector>
using namespace std;

class QuickSort {
private:
    int n;
    int* nums;

public:
    QuickSort(int n) {
        this->n = n;
        nums = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
    }

    void sort(int l, int r, int cutOff) {
        if (l >= r) {
            return;
        }
        if (cutOff < 100) {
            for (int i = l + 1; i <= r; i++) {
                for (int j = i; j > l; j--) {
                    if (nums[j - 1] > nums[j]) {
                        swap(nums[j - 1], nums[j]);
                    }
                }
            }
            return;
        }

        int i = l - 1, j = r + 1;
        int x = nums[l + r >> 1];
        while (i < j) {
            do {
                i++;
            } while (nums[i] < x);
            do {
                j--;
            } while (nums[j] > x);
            if (i < j) {
                swap(nums[i], nums[j]);
            }
        }
        sort(l, j, j - l + 1);
        sort(j + 1, r, r - j);
    }

    int* sort() {
        sort(0, n - 1, n);
        return nums;
    }
};

int main(void) {
    int n;
    cin >> n;
    QuickSort qs(n);
    int* res = qs.sort();
    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}