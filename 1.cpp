#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        char data;
        Node* left;
        Node* right;
        Node(char d){
            this -> data = d;
            this -> left = NULL;
            this -> right = NULL;
        }
};

bool isop(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Node* BuildTree(string post){
    stack<Node*> st;

    for(char ch : post){
        if(isop(ch)){
            Node* node = new Node(ch);
            node -> right = st.top();
            st.pop();
            node -> left = st.top();
            st.pop();
            st.push(node);
        }
        else{
            st.push(new Node(ch));
        }
    }
    return st.top();
}

void print_levelorder(Node* root){
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
            if(temp -> left){
                q.push(temp->left);
            }
            if(temp -> right){
                q.push(temp->right);
            }
        }
    }
}
void print_inorder(Node* root){
    if(root == NULL) return;
    print_inorder(root->left);
    cout << root->data << " ";
    print_inorder(root->right);
}

void print_preorder(Node* root){
    if(root == NULL) return;
    cout << root->data << " ";
    print_preorder(root -> left);
    print_preorder(root -> right);
}

void print_postorder(Node* root){
    if(root == NULL) return;
    print_postorder(root -> left);
    print_postorder(root -> right);
    cout << root -> data << " ";
}

vector<char> Inorder(Node* root){
    vector<char> ans;
    stack<Node*> s;
    while(true){
        if(root != NULL){
            s.push(root);
            root = root -> left;
        }
        else{
            if(s.empty()) break;
            root = s.top();
            ans.push_back(root->data);
            s.pop();
            root = root -> right;
        }
    }
    return ans;
}

vector<char> Preorder(Node* root){
    vector<char> ans;
    stack<Node*> s;
    s.push(root);

    while(!s.empty()){
        Node* curr = s.top();
        s.pop();
        if(curr != NULL){
            ans.push_back(curr -> data);

            if(curr -> right){
                s.push(curr->right);
            }
            if(curr -> left){
                s.push(curr->left);
            }
        }
    }
    return ans;
}

vector<char> Postorder(Node* root){
    vector<char> ans;
    stack<Node*> s;
    s.push(root);

    while(!s.empty()){
        Node* curr = s.top();
        s.pop();
        if(curr != NULL){
            ans.push_back(curr -> data);
            if(curr -> left){
                s.push(curr->left);
            }

            if(curr -> right){
                s.push(curr->right);
            }
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

int main(){
    string postfix = "345*+"; 
    Node* root = BuildTree(postfix);  
    print_levelorder(root);
    //print inorder
    cout << "Recursive Inorder" << endl;
    print_inorder(root);
    cout << endl;

    //print preorder
    cout << "Recursive Preorder" << endl;
    print_preorder(root);
    cout << endl;

    // print postorder;
    cout << "Recursive Postorder" << endl;
    print_postorder(root);
    cout << endl;
    
    // print non-recursive inorder
    cout << "Non-Recursive Inorder" << endl;
    vector<char> result = Inorder(root);
    for(char ch : result){
        cout << ch << " ";
    }
    cout << endl;

    // print non-recursive Preorder
    cout << "Non-Recursive Preorder" << endl;
    vector<char> result2 = Preorder(root);
    for(char ch : result2){
        cout << ch << " ";
    }
    cout << endl;

    //print non-recursive PostOrder
    cout << "Non-Recursive Postorder" << endl;
    vector<char> result3 = Postorder(root);
    for(char ch : result3){
        cout << ch << " ";
    }
    cout << endl;

    return 0; 
}
