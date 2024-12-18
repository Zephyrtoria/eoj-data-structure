#include <iostream>
#include <queue>
using namespace std;

const int N = 200010;

typedef struct Node {
    int val = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = -1;
} Node;

typedef pair<int, int> PII;
PII *arr;
int idx;
int res[N];

int getHeight(Node *cur) {
    if (cur == nullptr) {
        return 0;
    }
    if (cur->height != -1) {
        return cur->height;
    }
    cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
    return cur->height;
}

void isBalanced(Node *cur) {
    if (abs(getHeight(cur->left) - getHeight(cur->right)) > 1) {
        res[idx++] = cur->val;
    }

    if (cur->left != nullptr) {
        isBalanced(cur->left);
    }
    if (cur->right != nullptr) {
        isBalanced(cur->right);
    }
}

Node *createTree() {
    queue<Node *> q;

    Node *root = new Node{};
    root->val = 1;
    q.push(root);

    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        int index = cur->val;
        if (arr[index].first != 0) {
            cur->left = new Node;
            cur->left->val = arr[index].first;
            q.push(cur->left);
        }
        if (arr[index].second != 0) {
            cur->right = new Node;
            cur->right->val = arr[index].second;
            q.push(cur->right);
        }
    }

    return root;
}

int main(void) {
    int n;
    cin >> n;
    arr = new PII[n + 1];

    for (int i = 1; i <= n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    Node *root = createTree();
    int maxHeight = getHeight(root);

    isBalanced(root);

    int result = res[0];
    for (int i = 1; i < idx; i++) {
        result = min(result, res[i]);
    }
    if (idx != 0) {
        cout << "No" << endl;
        cout << result << endl;
    } else {
        cout << "Yes" << endl;
        cout << maxHeight << endl;
    }
    return 0;
}