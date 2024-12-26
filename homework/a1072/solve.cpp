#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 1024
using namespace std;

/**
 * 二叉查找树结点结构
 */
typedef struct binarySortTree {
    int data;                       /**<结点键值 */
    struct binarySortTree *lchild;  /**<左子节点 */
    struct binarySortTree *rchild;  /**<右子节点 */
} BSTNODE;


BSTNODE *buildTree(int *, int);
bool isBalance(BSTNODE *) ;
void printAVG(BSTNODE *) ;

/*************************************************************************/
/**
 * 建立一颗以nodeArr作为结点键值的一棵查找树
 * 数组下标从0开始
 * @param nodeArr   [大小为arrSize的数组]
 * @param arrSize   [数组大小]
 *nodeArr[]为一组未排序的结点序列（类型为整数，用做结点的键值），现在你需要依次将这些结点键值插入一棵初始状态为空二叉树，并保证整棵树是二叉查找树。
 * @return          [树的根节点root的指针]
 */
BSTNODE *buildTree(int *nodeArr, int arrSize) {
    /** TODO **/
}



/**
 * 判断这棵查找树是否平衡
 *  * @param root      [树的根节点]
 */
bool isBalance(BSTNODE *root) {
    /** TODO **/
}

/**
 * 输出这颗查找树查找结点的平均比较次数, 结果保留2位小数
 * 具体参考样例
 * AVG（二叉查找法）= ∑_树中的k▒〖p(k)(1+λk)〗
 * @param root      [树的根节点]
 */
void printAVG(BSTNODE *root) {
    /** TODO 需要输出**/
}