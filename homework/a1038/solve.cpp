#include <bits/stdc++.h>
using namespace std;

class BiNODE {
public:
    char data;       // 结点值，字符类型，可以按字典序比较大小
    BiNODE* lchild;  // 左子节点
    BiNODE* rchild;  // 右子节点

    BiNODE(char d = '\0');  // 构造函数
    ~BiNODE();              // 析构函数
};

BiNODE::BiNODE(char d) : data(d), lchild(nullptr), rchild(nullptr) {}

BiNODE::~BiNODE() {
    delete lchild;
    delete rchild;
}

class BinaryTree {
public:
    BinaryTree(BiNODE* r = nullptr);  // 构造函数
    ~BinaryTree();                    // 析构函数

    BiNODE* BuildTree();                        // 构建二叉树的函数
    void Recursion_Pre_Order(BiNODE* node);     // 递归前序遍历函数
    void NoRecursion_Pre_Order(BiNODE* node);   // 非递归前序遍历函数
    void Recursion_In_Order(BiNODE* node);      // 递归中序遍历函数
    void NoRecursion_In_Order(BiNODE* node);    // 非递归中序遍历函数
    void Recursion_Post_Order(BiNODE* node);    // 递归后序遍历函数
    void NoRecursion_Post_Order(BiNODE* node);  // 非递归后序遍历函数
    void Hierachicalorder(BiNODE* node);        // 层次遍历函数

    int Size_Of_Tree(BiNODE* node);       // 计算二叉树大小的函数
    int Height_Of_Tree(BiNODE* node);     // 计算二叉树高度的函数
    bool Is_Full_Tree(BiNODE* node);      // 判断是否为满二叉树的函数
    bool Is_Complete_Tree(BiNODE* node);  // 判断是否为完全二叉树的函数
    bool Is_Perfect_Tree(BiNODE* node);   // 判断是否为完美二叉树的函数
    BiNODE* GetRoot();                    // 获取根节点的函数
    void SetRoot(BiNODE* node);           // 修改根节点的函数

private:
    BiNODE* root;                 // 二叉树的根节点
    void freeTree(BiNODE* node);  // 释放二叉树节点的函数
};

BinaryTree::BinaryTree(BiNODE* r) : root(r) {}

BinaryTree::~BinaryTree() {
    freeTree(root);
}

void BinaryTree::freeTree(BiNODE* node) {
    if (node) {
        delete node;
    }
}

BiNODE* BinaryTree::GetRoot() {
    return root;
}

void BinaryTree::SetRoot(BiNODE* node) {
    root = node;
}

int main(void) {
    BinaryTree tree;
    tree.BuildTree();

    tree.Recursion_Pre_Order(tree.GetRoot());
    printf("\n");

    tree.NoRecursion_Pre_Order(tree.GetRoot());
    printf("\n");

    tree.Recursion_In_Order(tree.GetRoot());
    printf("\n");

    tree.NoRecursion_In_Order(tree.GetRoot());
    printf("\n");

    tree.Recursion_Post_Order(tree.GetRoot());
    printf("\n");

    tree.NoRecursion_Post_Order(tree.GetRoot());
    printf("\n");

    tree.Hierachicalorder(tree.GetRoot());
    printf("\n");

    printf("%d\n", tree.Size_Of_Tree(tree.GetRoot()));
    printf("%d\n", tree.Height_Of_Tree(tree.GetRoot()));
    printf("%c\n", tree.Is_Full_Tree(tree.GetRoot()) ? 'T' : 'F');
    printf("%c\n", tree.Is_Complete_Tree(tree.GetRoot()) ? 'T' : 'F');
    printf("%c\n", tree.Is_Perfect_Tree(tree.GetRoot()) ? 'T' : 'F');

    return 0;
}

/* 你写的函数将会被嵌入在这个部分 */
// 构建二叉树的函数
BiNODE* BuildTreeFactory(string preorder, int pl, int pr, string inorder, int il, int ir) {
    if (pl > pr || il > ir) {
        return nullptr;
    }

    BiNODE* curRoot = new BiNODE(preorder[pl]);
    int i = 0;
    while (preorder[pl] != inorder[il + i]) {
        i++;
    }

    curRoot->lchild = BuildTreeFactory(preorder, pl + 1, pl + i, inorder, il, il + i - 1);
    curRoot->rchild = BuildTreeFactory(preorder, pl + i + 1, pr, inorder, il + i + 1, ir);
    return curRoot;
}
BiNODE* BinaryTree::BuildTree() {
    int n;
    cin >> n;
    if (n == 0) {
        return nullptr;
    }
    string preorder, inorder;
    cin >> preorder >> inorder;

    root = BuildTreeFactory(preorder, 0, preorder.length() - 1, inorder, 0, inorder.length() - 1);
    return root;
}

// 递归前序遍历函数
void BinaryTree::Recursion_Pre_Order(BiNODE* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->data << " ";
    Recursion_Pre_Order(node->lchild);
    Recursion_Pre_Order(node->rchild);
}
// 非递归前序遍历函数
void BinaryTree::NoRecursion_Pre_Order(BiNODE* node) {
    stack<BiNODE*> s;
    s.push(node);

    while (!s.empty()) {
        BiNODE* cur = s.top();
        s.pop();
        if (cur == nullptr) {
            continue;
        }
        cout << cur->data << " ";
        s.push(cur->rchild);
        s.push(cur->lchild);
    }
}
// 递归中序遍历函数
void BinaryTree::Recursion_In_Order(BiNODE* node) {
    if (node == nullptr) {
        return;
    }
    Recursion_In_Order(node->lchild);
    cout << node->data << " ";
    Recursion_In_Order(node->rchild);
}
// 非递归中序遍历函数
void BinaryTree::NoRecursion_In_Order(BiNODE* node) {
    stack<BiNODE*> s;

    BiNODE* cur = node;
    while (cur != nullptr || !s.empty()) {
        if (cur != nullptr) {
            s.push(cur);
            cur = cur->lchild;
        } else {
            cur = s.top();
            s.pop();
            cout << cur->data << " ";
            cur = cur->rchild;
        }
    }
}
// 递归后序遍历函数
void BinaryTree::Recursion_Post_Order(BiNODE* node) {
    if (node == nullptr) {
        return;
    }
    Recursion_Post_Order(node->lchild);
    Recursion_Post_Order(node->rchild);
    cout << node->data << " ";
}
// 非递归后序遍历函数
void BinaryTree::NoRecursion_Post_Order(BiNODE* node) {
    vector<char> result;
    stack<BiNODE*> s;
    s.push(node);

    while (!s.empty()) {
        BiNODE* cur = s.top();
        s.pop();
        if (cur == nullptr) {
            continue;
        }
        result.push_back(cur->data);
        s.push(cur->lchild);
        s.push(cur->rchild);
    }
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
}

// 层次遍历函数
void BinaryTree::Hierachicalorder(BiNODE* node) {
    queue<BiNODE*> q;
    q.push(node);

    while (!q.empty()) {
        BiNODE* cur = q.front();
        q.pop();
        if (cur == nullptr) {
            continue;
        }
        cout << cur->data << " ";
        q.push(cur->lchild);
        q.push(cur->rchild);
    }
}
// 计算二叉树大小的函数
int BinaryTree::Size_Of_Tree(BiNODE* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + Size_Of_Tree(node->lchild) + Size_Of_Tree(node->rchild);
}
// 计算二叉树高度的函数
int BinaryTree::Height_Of_Tree(BiNODE* node) {
    if (node == nullptr) {
        return 0;
    }
    queue<pair<BiNODE*, int>> q;
    int height = 1;
    q.push({node, height});

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (cur.first == nullptr) {
            continue;
        }
        height = (height > cur.second) ? height : cur.second;
        q.push({cur.first->lchild, cur.second + 1});
        q.push({cur.first->rchild, cur.second + 1});
    }
    return height;
}
// 判断是否为满二叉树的函数
bool BinaryTree::Is_Full_Tree(BiNODE* node) {
    if (node == nullptr) {
        return false;
    }
    queue<BiNODE*> q;
    q.push(node);
    while (!q.empty()) {
        BiNODE* cur = q.front();
        q.pop();
        if (cur == nullptr) {
            continue;
        }
        if (cur->lchild == nullptr && cur->rchild != nullptr || cur->rchild == nullptr && cur->lchild != nullptr) {
            return false;
        }
        q.push(cur->lchild);
        q.push(cur->rchild);
    }
    return true;
}
// 判断是否为完全二叉树的函数
bool BinaryTree::Is_Complete_Tree(BiNODE* node) {
    if (node == nullptr) {
        return false;
    }
    queue<BiNODE*> q;
    q.push(node);
    bool noChild = false;
    while (!q.empty()) {
        BiNODE* cur = q.front();
        q.pop();
        if (cur == nullptr) {
            continue;
        }
        if (cur->lchild == nullptr && cur->rchild != nullptr) {
            return false;
        }

        if (noChild && cur->lchild != nullptr) {
            return false;
        }
        if (cur->lchild == nullptr || cur->rchild == nullptr) {
            noChild = true;
        }

        q.push(cur->lchild);
        q.push(cur->rchild);
    }
    return true;
}
// 判断是否为完美二叉树的函数
bool BinaryTree::Is_Perfect_Tree(BiNODE* node) {
    if (node == nullptr) {
        return false;
    }
    int size = Size_Of_Tree(GetRoot());
    int height = Height_Of_Tree(GetRoot());
    int a = 1;
    int sum = 0;
    for (int i = 0; i < height; i++) {
        sum += a;
        a *= 2;
    }
    return size == sum;
}