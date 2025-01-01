#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1024
using namespace std;

/**
 * 二叉查找树结点结构
 */
typedef struct binarySortTree {
    int data;                      /**<结点键值 */
    struct binarySortTree *lchild; /**<左子节点 */
    struct binarySortTree *rchild; /**<右子节点 */
} BSTNODE;

BSTNODE *buildTree(int *, int);
bool isBalance(BSTNODE *);
void printAVG(BSTNODE *);

int main() {
    int nodeArr[MAXN];
    /*处理输入，你不需要关心*/
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nodeArr[i]);
    }

    BSTNODE *root = buildTree(nodeArr, n);
    printAVG(root);

    /*函数调用，判题，你不需要关心*/
    if (isBalance(root)) {
        printf("Is balance\n");
    } else {
        printf("Not balance\n");
    }


    return 0;
}

/*************************************************************************/
/**
 * 建立一颗以nodeArr作为结点键值的一棵查找树
 * 数组下标从0开始
 * @param nodeArr   [大小为arrSize的数组]
 * @param arrSize   [数组大小]
 *nodeArr[]为一组未排序的结点序列（类型为整数，用做结点的键值），现在你需要依次将这些结点键值插入一棵初始状态为空二叉树，并保证整棵树是二叉查找树。
 * @return          [树的根节点root的指针]
 */

BSTNODE *insertNode(int val, BSTNODE *root) {
    if (root == nullptr) {
        return new BSTNODE{val, nullptr, nullptr};
    }
    if (val > root->data) {
        root->rchild = insertNode(val, root->rchild);
    } else {
        root->lchild = insertNode(val, root->lchild);
    }
    return root;
}

BSTNODE *buildTree(int *nodeArr, int arrSize) {
    /** TODO **/
    BSTNODE *root = nullptr;
    for (int i = 0; i < arrSize; i++) {
        root = insertNode(nodeArr[i], root);
    }
    return root;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(BSTNODE *root) {
    if (root == nullptr) {
        return 0;
    }
    return max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

/**
 * 判断这棵查找树是否平衡
 *  * @param root      [树的根节点]
 */
bool isBalance(BSTNODE *root) {
    /** TODO **/
    if (root == nullptr) {
        return true;
    }
    return (abs(getHeight(root->rchild) - getHeight(root->lchild)) <= 1) && isBalance(root->lchild) && isBalance(root->rchild);
}

void traversal(BSTNODE *cur, int u, int &sum, int &count) {
    if (cur == nullptr) {
        return;
    }
    sum += u;
    count++;
    traversal(cur->lchild, u + 1, sum, count);
    traversal(cur->rchild, u + 1, sum, count);
}

/**
 * 输出这颗查找树查找结点的平均比较次数, 结果保留2位小数
 * 具体参考样例
 * AVG（二叉查找法）= ∑_树中的k▒〖p(k)(1+λk)〗
 * @param root      [树的根节点]
 */
void printAVG(BSTNODE *root) {
    /** TODO 需要输出**/
    int sum = 0, count = 0;
    traversal(root, 1, sum, count);
    printf("%.2f\n", (double)sum / count);
}