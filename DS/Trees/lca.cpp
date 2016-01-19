/*
Node is defined as 

typedef struct node
{
   int data;
   node * left;
   node * right;
}node;

*/

#include <queue>

// given root, determine if the BST contains both v1 and v2  
bool BST_enumerate(node* root, int v1, int v2){
    
    queue<node*> Q;
    Q.push(root);
    bool T1 = false;
    bool T2 = false;
    
    if (root->data == v1){T1 = true;}
    if (root->data == v2){T2 = true;}
    
    while (!Q.empty()){
        node* cur = Q.front();
        Q.pop();
        if (cur->left){
            if (cur->left->data == v1){T1 = true;}
            if (cur->left->data == v2){T2 = true;}
            Q.push(cur->left);
        }   
        if (cur->right){
            if (cur->right->data == v1){T1 = true;}
            if (cur->right->data == v2){T2 = true;}
            Q.push(cur->right);
        }
        if (T1 && T2){return true;}
    }    
    return false;
}

// testing
void BST_print(node*root){
    queue<node*> Q;
    Q.push(root);
    while(!Q.empty()){
        node* cur = Q.front();
        Q.pop();
        cout << cur->data << " ";
        if (cur->left){Q.push(cur->left);}
        else{cout << "no left child for: " << cur->data << endl;}
        if (cur->right){Q.push(cur->right);}
        else{cout << "no right child for: " << cur->data << endl;}
    }
    return;
}


node * lca(node* root, int v1,int v2){
    node* ancestor = root;
    while(true){
        if (ancestor->left){ 
            if (BST_enumerate(ancestor->left, v1, v2)){ // left subtree contains v1 and v2
                ancestor = ancestor->left;
                continue;
            }
        } 
        if (ancestor->right){ 
            if (BST_enumerate(ancestor->right,v1,v2)){ // right subtree contains v1 and v2
                ancestor = ancestor->right;
                continue;
            }
        }
        break;
    }
    return ancestor;
}


