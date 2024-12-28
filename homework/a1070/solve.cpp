#include <iostream>
#include <vector>
using namespace std;

typedef struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int val_) {
        val = val_;
        left = nullptr;
        right = nullptr;
    }
} Node;

class Tree {
private:
    int n;
    Node* root;
    int* inorder;
    int end;

public:

    Node* builder(int *arr, int cur) {
        if (cur > n) {
            return nullptr;
        }
        
        Node* newNode = new Node(arr[cur]);
        newNode->left = builder(arr, cur * 2);
        newNode->right = builder(arr, cur * 2 + 1);
        return newNode;
    }

    Tree(int n, int* arr) {
        this->n = n;
        root = builder(arr, 1);
    }

    void inorderTraversal(Node* cur) {
        if (cur == nullptr) {
            return;
        }
        inorderTraversal(cur->left);
        inorder[end++] = cur->val;
        inorderTraversal(cur->right);
    }

    bool isBST() {
        inorder = new int[n + 1];
        end = 1;

        inorderTraversal(root);
        for (int i = 2; i <= n; i++) {
            if (inorder[i - 1] >= inorder[i]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    int n;
    cin >> n;

    while (n--) {
        int m;
        cin >> m;
        int* arr = new int[m];
        for (int i = 1; i <= m; i++) {
            cin >> arr[i];
        }
        Tree t(m, arr);

        if (t.isBST()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        delete arr;
    }
    return 0;
}