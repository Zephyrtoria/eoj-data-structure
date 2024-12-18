#include <iostream>
using namespace std;

const int N = 100010;
typedef struct Node {
    int data;
    int parent;
} Node;

typedef struct TreeNode {
    int data;
    int *children;
    int count = 0;
} TreeNode;

Node arr[N];
TreeNode tree[N];
int n;
int nums[N];

int res = 0;
int result[N];

void post(int root) {
    for (int i = 0; i < tree[root].count; i++) {
        post(tree[root].children[i]);
    }
    result[res++] = root;
}

int main(void) {
    // 读入双亲结点
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i].parent;

    // nums[i]代表第i个结点有多少个子结点，如果使用vector可以免去
    for (int i = 1; i < n; i++)
        nums[arr[i].parent]++;

    // Node -> TreeNode
    for (int i = 0; i < n; i++) {
        tree[i].data = i;
        tree[i].children = new int[nums[i]];
    }

    // 建立父子关系
    for (int i = 1; i < n; i++) {
        int curParent = arr[i].parent;
        tree[curParent].children[tree[curParent].count++] = i;
    }
    post(0);

    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
        delete tree[i].children;
    }

    cout << endl;

    return 0;
}
