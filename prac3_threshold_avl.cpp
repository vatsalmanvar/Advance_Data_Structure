#include<bits/stdc++.h>
using namespace std;

int threshold = 7, no_of_insertion = 0;

class node{
public: 
    int key, value;
    node *left;
    node* right;
    int height;
};

node* createNode(int _key, int _value, node* root);
int getHeight(node * n);
node* leftRotate(node * x);
node* rightRotate(node * x);
int getHeightDiff(node *n);
node* insertNode(node* n, int key, int value, node* root);
void balanceTree(node* root, int key, int value);
node* deleteNode(node* root, int key);
void printTree(node * root);

node* createNode(int _key, int _value, node* root){
    node * n = new node();
    n->key = _key;
    n->value = _value;
    n->left = n->right = NULL;
    n->height = 1;

    no_of_insertion++;
    if(no_of_insertion == threshold){
        balanceTree(root, _key, _value);
        no_of_insertion = 0;
    }
    return n;
}

int getHeight(node * n){
    if(n == NULL) return 0;
    return n->height;
}

node* leftRotate(node * x){
    node* y = x->right;
    node* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

node* rightRotate(node * x){
    node* y = x->left;
    node* temp = y->right;
    y->right = x;
    x->left = temp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
} 

int getHeightDiff(node *n){
    if(n == NULL) return 0;
    return (getHeight(n->left) - getHeight(n->right));
}

node* insertNode(node* n, int key, int value, node* root){
    if(n == NULL) return createNode(key, value, root);
    if(key < n->key) n->left = insertNode(n->left, key, value, root);
    else if(key > n->key) n->right = insertNode(n->right, key, value, root);
    else return n;
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    return n;
}

void balanceTree(node* root, int key, int value){
    if(root == NULL) return;
    balanceTree(root->left, key, value);
    balanceTree(root->right, key, value);
    int heightDiff = getHeightDiff(root);
    if(heightDiff > 1){
        if(root->key < root->left->key) rightRotate(root);
        else if(root->key < root->left->key){
            root->left = leftRotate(root->left);
            rightRotate(root);
        }
    }

    if(heightDiff < -1){
        if(root->key > root->right->key) leftRotate(root);
        else if(root->key < root->right->key){
            root->right = rightRotate(root->right);
            leftRotate(root);
        }
    }
}

node* deleteNode(node* root, int key){
    if (root == NULL) return root;

    if(key < root->key ) root->left = deleteNode(root->left, key);
    else if(key > root->key) root->right = deleteNode(root->right, key);
    else{
        if(root->left==NULL || root->right==NULL){
            node *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else *root = *temp;
        }
        else
        {
            node * temp = root->right;
            while(temp->left!=NULL) temp = temp->left;
            
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;
 
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    int balance = getHeightDiff(root);

    if (balance > 1 && getHeightDiff(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getHeightDiff(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getHeightDiff(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getHeightDiff(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void printTree(node * root){
    // bfs traversal of tree is printed
	cout<<endl<<endl<<"displayed as this formate: (key, value)"<<endl<<endl;
    if(root == NULL) return;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        int s = q.size();
		cout<<"-new level-"<<endl;
        while(s--){
            auto p = q.front();
            q.pop();
            cout<<"("<<p->key<<" "<<p->value<<")"<<endl;
            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
    }
}

void inorder(node * node){
    if(node == NULL) return;
    inorder(node->left);
    cout<<node->key<<" ";
    inorder(node->right);
    return;
}

int main(){
    int i, j, c;
    int repeat = 1;

    node * root;
    root=NULL;
    ifstream datafile("prac3_avl_datainput.txt");
    string line="";
    while (getline (datafile, line)) {
        vector <string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ' ')){
            tokens.push_back(intermediate);
        }
        root = insertNode(root,stoi(tokens[0]),stoi(tokens[1]), root);
    }
    datafile.close();

    while(repeat == 1){
        cout<<"\n\n---Choose option---\n";
        cout<<"\n1.Insert";
        cout<<"\n2.Display";
        cout<<"\n3.Delete";
        cout<<"\n4.Exit";
        cout<<"\nChoice: ";
        cin>>c;
        switch (c)
        {
            case 1:
                int x,y;
                cout<<"Enter key and value: "<<endl;
                cin>>x>>y;
                root = insertNode(root,x,y, root);
                break;
            case 2:
                printTree(root);
                break;
            case 3:
                cout<<"\nEnter a key to delete : ";
                cin>>x;
                root = deleteNode(root,x);
                break;
            case 4:
                repeat = 0;
                break;
        }
    }
    return 0;
}   