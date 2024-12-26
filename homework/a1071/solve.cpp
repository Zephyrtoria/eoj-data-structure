#include <iostream>
#include <vector>
using namespace std;

typedef struct Node {
    int val;
    Node* left;
    Node* right;
} Node;

class Tree {
private:
    Node* root;
    vector<int> nums;
    int n;

public:
    Tree(vector<int> nums) {
        this->nums = nums;
        this->n = nums.size();
        root = TreeBuilder(0, n - 1);
    }

    Node* TreeBuilder(int l, int r) {
        if (l > r) {
            return nullptr;
        }
        Node* cur = new Node;
        cur->val = nums[l];
        int i = l + 1;
        while (i < n && nums[i] < cur->val) {
            i++;
        }
        cur->left = TreeBuilder(l + 1, i - 1);
        cur->right = TreeBuilder(i, r);
        return cur;
    }

    void solve() {
        postTraversal(root);
    }

    void postTraversal(Node* cur) {
        if (cur == nullptr) {
            return;
        }
        postTraversal(cur->left);
        postTraversal(cur->right);
        cout << cur->val << endl;
    }
};

int main(void) {
    vector<int> nums;
    int a;
    while (cin >> a) {
        nums.push_back(a);
    }
    Tree t(nums);
    t.solve();
    return 0;
}