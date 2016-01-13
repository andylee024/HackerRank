/*
 Code for Tree Traversals
 1. Preorder
 2. Inorder
 3.
*/

struct node{
    int data;
    node* left;
    node* right;
};


/*
 Preorder : root, left, right
 */
void Preorder(node *root) {
    if (root == NULL){return;}
    cout << root->data << " "; // root
    if (root->left){Preorder(root->left);} // left
    if (cur->right){Preorder(cur->right);} // right
}

/*
 Inorder: left, root, right
 */
void Inorder(node *root) {
    if (root == NULL){return;}
    if (root->left){Inorder(root->left);} // left
    cout << root->data << " "; // root
    if (root->right){Inorder(root->right);} // right
}

/*
 Postorder: left, right, root
 */

void Postorder(node *root) {
    if (!root){return;}
    if (root->left){Postorder(root->left);}
    if (root->right){Postorder(root->right);}
    cout << root->data << " ";
}


