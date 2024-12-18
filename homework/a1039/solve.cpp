#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef char TElemSet;

struct BinaryTreeNode  // 定义二叉树节点的结构体
{
    TElemSet data;          // 节点的数据成员，类型为 TElemSet
    BinaryTreeNode *left;   // 指向左子节点的指针
    BinaryTreeNode *right;  // 指向右子节点的指针

    BinaryTreeNode(TElemSet val) : data(val), left(nullptr), right(nullptr) {}  // 构造函数，初始化节点数据，并将左右指针设为 nullptr
};

class BinaryTree  // 定义二叉树类
{
private:
    BinaryTreeNode *root;  // 指向二叉树根节点的指针

public:
    void CopyTree(BinaryTreeNode *&thisNode, BinaryTreeNode *otherNode);                  // 深拷贝二叉树的递归函数，将 otherNode 拷贝到 thisNode
    void DestroyTree(BinaryTreeNode *node);                                               // 递归销毁以 node 为根节点的二叉树，释放内存
    BinaryTreeNode *BuildTree(const TElemSet *preorder, const TElemSet *inorder, int n);  // 根据前序和中序遍历序列构建二叉树
    BinaryTree(const TElemSet *preorder, const TElemSet *inorder, int n);                 // 带参数的构造函数，用于从遍历序列构建二叉树
    BinaryTree(const BinaryTree &other);                                                  // 深拷贝构造函数，用于根据已有二叉树创建新二叉树
    ~BinaryTree();                                                                        // 析构函数，用于销毁二叉树并释放内存
    BinaryTree &operator=(const BinaryTree &other);                                       // 赋值操作符重载，用于将一个二叉树赋值给另一个二叉树
    BinaryTreeNode *getRoot();                                                            // 返回根节点的指针
    int Diameter(BinaryTreeNode *node);                                                   // 计算并返回以 node 为根节点的子树的直径
    int Height(BinaryTreeNode *node);                                                     // 计算并返回以 node 为根节点的子树的高度
};

void BinaryTree::CopyTree(BinaryTreeNode *&thisNode, BinaryTreeNode *otherNode) {
    if (!otherNode) {
        thisNode = nullptr;
    } else {
        thisNode = new BinaryTreeNode(otherNode->data);
        CopyTree(thisNode->left, otherNode->left);
        CopyTree(thisNode->right, otherNode->right);
    }
}

void BinaryTree::DestroyTree(BinaryTreeNode *node) {
    if (node) {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}

BinaryTreeNode *BinaryTree::BuildTree(const TElemSet *preorder, const TElemSet *inorder, int n) {
    if (n == 0)
        return nullptr;

    BinaryTreeNode *tree = new BinaryTreeNode(preorder[0]);

    int rootIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (inorder[i] == preorder[0]) {
            rootIndex = i;
            break;
        }
    }

    tree->left = BuildTree(preorder + 1, inorder, rootIndex);
    tree->right = BuildTree(preorder + rootIndex + 1, inorder + rootIndex + 1, n - rootIndex - 1);
    return tree;
}

// 带参数的构造函数
BinaryTree::BinaryTree(const TElemSet *preorder, const TElemSet *inorder, int n) {
    root = BuildTree(preorder, inorder, n);
}

// 深拷贝构造函数
BinaryTree::BinaryTree(const BinaryTree &other) {
    CopyTree(this->root, other.root);
}

// 析构函数
BinaryTree::~BinaryTree() {
    DestroyTree(root);
}

// 赋值操作符重载
BinaryTree &BinaryTree::operator=(const BinaryTree &other) {
    if (this != &other) {
        DestroyTree(root);                 // 释放当前对象的内存
        CopyTree(this->root, other.root);  // 复制新树
    }
    return *this;
}

// 获取树的根节点
BinaryTreeNode *BinaryTree::getRoot() {
    return root;
}

int BinaryTree::Height(BinaryTreeNode *node) {
    if (!node)
        return 0;
    int leftHeight = Height(node->left);
    int rightHeight = Height(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

/* 你的代码将会被嵌入在这个位置 */
int BinaryTree::Diameter(BinaryTreeNode *node) {
    // TODO
    if (node == nullptr) {
        return 0;
    }
    int leftD = Height(node->left);
    int rightD = Height(node->right);
    int result = leftD + rightD;
    result = std::max(result, Diameter(node->left));
    result = std::max(result, Diameter(node->right));
    return result;
}

int main() {
    int n;
    std::cin >> n;

    TElemSet *preorder = new TElemSet[n + 1];
    TElemSet *inorder = new TElemSet[n + 1];

    std::cin >> preorder >> inorder;

    BinaryTree tree(preorder, inorder, n);
    std::cout << tree.Diameter(tree.getRoot()) << std::endl;
    return 0;
}