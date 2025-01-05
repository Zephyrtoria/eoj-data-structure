Node* createBinarySearchTree(vector<int> &v, int l, int r)
{
    if (l > r) {
        return nullptr;
    }
    
    Node *root = new Node;
    int mid = (l + r) / 2;
    root->val = v[mid];
    root->l = createBinarySearchTree(v, l, mid - 1);
    root->r = createBinarySearchTree(v, mid + 1, r);
    return root;
}