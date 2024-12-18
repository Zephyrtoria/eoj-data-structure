#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

const int N = 1010;

typedef struct Node {
    int data_;  // index;
    vector<Node*> son_;
} Node;

class Tree {
private:
    Node* root_;
    int size_;
    int leaves_;
    int height_;
    void getLeaves(Node* root);

public:
    Tree();
    ~Tree();
    int getRoot();
    void preOrder();
    void postOrder();
    void layerOrder();
    int getSize();
    int getLeaves();
    int getHeight();
};

Tree::Tree() {
    size_ = 0;

    vector<int> prts[N];
    int v, prt;
    while (cin >> v >> prt) {
        if (prt == -1) {
            root_ = new Node{v};
        } else {
            prts[prt].push_back(v);
        }
        size_++;
    }

    queue<Node*> q;
    q.push(root_);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        prt = cur->data_;
        for (int i = 0; i < prts[prt].size(); i++) {
            Node* newNode = new Node{prts[prt][i]};
            cur->son_.push_back(newNode);
            q.push(newNode);
        }
    }
}

Tree::~Tree() {
    vector<Node*> result;
    queue<Node*> q;

    q.push(root_);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        result.push_back(cur);

        for (int i = 0; i < cur->son_.size(); i++) {
            q.push(cur->son_[i]);
        }
    }

    for (int i = 0; i < result.size(); i++) {
        delete result[i];
    }
    delete root_;
}
int Tree::getRoot() { return root_->data_; }
void Tree::preOrder() {
    vector<int> result;
    stack<Node*> s;
    s.push(root_);
    while (!s.empty()) {
        Node* cur = s.top();
        s.pop();
        if (cur == nullptr) {
            continue;
        }
        result.push_back(cur->data_);
        for (int i = cur->son_.size() - 1; i >= 0; i--) {
            s.push(cur->son_[i]);
        }
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
void Tree::postOrder() {
    vector<int> result;
    stack<Node*> s;
    s.push(root_);
    while (!s.empty()) {
        Node* cur = s.top();
        s.pop();
        if (cur == nullptr) {
            continue;
        }
        result.push_back(cur->data_);
        for (int i = 0; i < cur->son_.size(); i++) {
            s.push(cur->son_[i]);
        }
    }
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << endl;
}
void Tree::layerOrder() {
    vector<int> result;
    queue<Node*> q;

    q.push(root_);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        result.push_back(cur->data_);

        for (int i = 0; i < cur->son_.size(); i++) {
            q.push(cur->son_[i]);
        }
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
int Tree::getSize() { return size_; }
int Tree::getLeaves() {
    getLeaves(root_);
    cout << endl;
    return leaves_;
}

void Tree::getLeaves(Node* cur) {
    if (cur->son_.size() == 0) {
        cout << cur->data_ << " ";
        leaves_++;
        return;
    }

    for (int i = 0; i < cur->son_.size(); i++) {
        getLeaves(cur->son_[i]);
    }
}

int Tree::getHeight() {
    height_ = 0;
    queue<pair<Node*, int>> q;
    q.push({root_, 1});
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        height_ = (height_ > cur.second) ? height_ : cur.second;
        for (int i = 0; i < cur.first->son_.size(); i++) {
            q.push({cur.first->son_[i], cur.second + 1});
        }
    }
    return height_;
}

int main(void) {
    Tree t;

    cout << t.getRoot() << endl;
    t.preOrder();
    t.postOrder();
    t.layerOrder();
    cout << t.getSize() << endl;
    cout << t.getLeaves() << endl;
    cout << t.getHeight() << endl;

    return 0;
}