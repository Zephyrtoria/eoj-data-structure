#include <stdio.h>
#include <stdlib.h>

typedef int TElemSet;
#define NIL -1 /* 假设数据为为正整数，NIL定义为非法数据，表示空 */

int Width(TElemSet levelorder[], int n);

int main(void) {
    TElemSet *levelorder;
    int n, i;

    scanf("%d\n", &n);
    levelorder = (TElemSet *)malloc(sizeof(TElemSet) * n);
    for (i = 0; i < n; i++) {
        scanf("%d", &levelorder[i]);
    }
    printf("%d\n", Width(levelorder, n));

    return 0;
}

int search(TElemSet l[], int left, int right, int n) {
    int result = 0;
    for (int i = left; i < n && i <= right; i++) {
        if (l[i] != -1) {
            result++;
        }
    }
    return result;
}

int Width(TElemSet levelorder[], int n) {
    if (n == 1) {
        return (levelorder[0] == -1) ? 0 : 1;
    }

    int width = 1;
    int left = 1, right = 2;
    int count = 2;
    while (left < n) {
        int a = search(levelorder, left, right, n);
        width = (width > a) ? width : a;
        count *= 2;
        left = right + 1;
        right += count;
    }

    return width;
}