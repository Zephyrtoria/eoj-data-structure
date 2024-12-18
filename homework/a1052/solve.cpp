#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

struct BiTreeNode {
    int data;
    BiTreeNode* left = nullptr;
    BiTreeNode* right = nullptr;
};

struct TreeNode {
    int data;
    vector<TreeNode*> son;
};

BiTreeNode* TreeBuilder(int* pre, int pl, int pr, int* inord, int il, int ir, unordered_map<int, int>& map);

class Tree {
private:
    BiTreeNode* root;

public:
    Tree(int* pre, int* inord, int n) {
        unordered_map<int, int> map;

        // 快速寻找下标
        for (int i = 0; i < n; i++) {
            map[inord[i]] = i;
        }

        root = TreeBuilder(pre, 0, n - 1, inord, 0, n - 1, map);
    }
    BiTreeNode* getRoot() {
        return root;
    }
    void leverTrav() {
        queue<BiTreeNode*> q;
        q.push(root);
        int size;
        while (!q.empty()) {
            size = q.size();
            while (size > 0) {
                size--;
                auto cur = q.front();
                q.pop();
                cout << cur->data << " ";
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
            }
        }
    }
};

BiTreeNode* TreeBuilder(int* pre, int pl, int pr, int* inord, int il, int ir, unordered_map<int, int>& map) {
    if (pl > pr || il > ir) {
        return nullptr;
    }

    BiTreeNode* cur = new BiTreeNode;
    cur->data = pre[pl];
    int i = map[pre[pl]] - il;

    cur->left = TreeBuilder(pre, pl + 1, pl + i, inord, il, il + i - 1, map);
    cur->right = TreeBuilder(pre, pl + i + 1, pr, inord, il + i + 1, ir, map);
    return cur;
}

TreeNode* convert(BiTreeNode* cur, TreeNode* pre) {
    if (cur == nullptr) {
        return nullptr;
    }

    TreeNode* tn = new TreeNode;
    tn->data = cur->data;

    if (cur->right != nullptr) {
        TreeNode* b = convert(cur->right, pre);
        pre->son.push_back(b);
    }
    if (cur->left != nullptr) {
        TreeNode* c = convert(cur->left, tn);
        tn->son.push_back(c);
    }

    return tn;
}

void TleverTrav(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();
        cout << cur->data << " ";
        for (int i = cur->son.size() - 1; i >= 0; i--) {
            q.push(cur->son[i]);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int* pre = new int[n];
    int* inord = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inord[i];
    }

    Tree t = Tree(pre, inord, n);
    cout << t.getRoot()->data << endl;
    ;
    t.leverTrav();
    cout << endl;
    TreeNode* tn = convert(t.getRoot(), nullptr);
    TleverTrav(tn);
    cout << endl;
    return 0;
}
