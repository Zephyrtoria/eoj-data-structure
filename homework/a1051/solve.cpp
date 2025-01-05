double solveExprTree(TreeNode* root) {
    // TODO
    if (root->data.isOp == false) {
        return root->data.oprand;
    }

    double a, b;
    a = solveExprTree(root->left);
    b = solveExprTree(root->right);
    switch (root->data.op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}
