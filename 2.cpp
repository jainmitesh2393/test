#include<bits/stdc++.h>

using namespace std;

class Node{
    public:
        int data;
        Node* left;
        Node* right;
        Node(int d){
            this -> data = d;
            this -> left = NULL;
            this -> right = NULL;
        }
};

Node* createBST(Node* root,int data){
    if(root == NULL){
        root = new Node(data);
        return root;
    }
    if(root-> data < data){
        root -> right = createBST(root->right,data);
    }
    else{
        root -> left = createBST(root->left,data);
    }
    return root;
}

void levelorderTraversal(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout << endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout << temp -> data << " ";
            if(temp -> left) q.push(temp->left);
            if(temp -> right) q.push(temp->right);
        }
    }
}

void Inorder(Node* root) {
    if (root == NULL) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true;
    if (root->data < key) return search(root->right, key);
    return search(root->left, key);
}

int findHeight(Node* root){
    if(root == NULL) return 0;

    int left = findHeight(root->left);
    int right = findHeight(root->right);

    int ans = max(left,right) + 1;
    return ans;
}

Node* minVal(Node* root){
    Node* temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node* deleteNode(Node* root,int val){
    if(root == NULL){
        return NULL;
    }
    if(root->data == val){
        // 0 child
        if(root -> left == NULL && root -> right == NULL){
            delete root;
            return NULL;
        }

        //1child
        //left child
        if(root->left != NULL && root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //right child
        if(root->left == NULL && root->right != NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // 2 child;
        if(root->left != NULL && root->right != NULL){
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteNode(root->right,mini);
            return root;
        }
    }
    else if(root->data > val){
        root->left = deleteNode(root->left,val);
    }
    else{
        root->right = deleteNode(root->right,val);
    }
}

Node* mirror(Node* root) {
    if (root == NULL) return NULL;
    Node* left = mirror(root->left);
    Node* right = mirror(root->right);
    root->left = right;
    root->right = left;
    return root;
}

void takeinput(Node* &root){
    int data;
    cin >> data;

    while(data != -1){
        root = createBST(root,data);
        cin >> data;
    }
}

int main(){
    Node* root = NULL;
    //Insert element 
    cout << "Enter data to be insert in BST" << endl;
    takeinput(root);

    // print levelwise 
    cout << "printing BST(level wise display)" << endl;
    levelorderTraversal(root);

    //print inorder 
    cout << "print inorder" << endl;
    Inorder(root);
    cout << endl;

    //Height of Tree
    cout << "Height of Tree" << endl;
    int height = findHeight(root);
    cout << height << endl;

    //search element 
    cout << "Seaching element" << endl;
    int ele;
    cin >> ele;
    if (search(root, ele))
        cout << "Element found in the BST." << endl;
    else
        cout << "Element not found in the BST." << endl;

    // delete element 
    int del;
    cin >> del;
    root = deleteNode(root,del);
    cout << endl;
    cout << "printing BST(level wise display)" << endl;
    levelorderTraversal(root);

    // mirror
    cout << "Mirror of the BST:" << endl;
    root = mirror(root);
    cout << "Level-order traversal of the mirror BST: " << endl;
    levelorderTraversal(root);
    cout << endl;

    return 0;
}
