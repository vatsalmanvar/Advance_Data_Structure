#include<bits/stdc++.h>
using namespace std;

static int const log32(int n){
	double const log23 = 2.4663034623764317;
	return (int)ceil(log23 * log(n));
}

class node{
public:
	node *left, *right, *parent;
	float value;
	node(){
		value = 0;
		left = right = parent = NULL;
	}
	node (float v){
		value = v;
		left = right = parent = NULL;
	}
};

int toarray(node *ptr, node *arr[], int i){
	if (ptr == NULL) return i;

	i = toarray(ptr->left, arr, i);
	arr[i++] = ptr;
	return toarray(ptr->right, arr, i);
}

class scapgoattree{
private:
	node *root;
	int n;
public:
	void printTree(node *);
	int size(node *);
	bool insert(float x);
	void rebuildTree(node *u);
	scapgoattree()	 { root = NULL; n = 0; }
	void printTree() {printTree(root);}

	node *build_again(node **a, int i, int n);

	int bst_insert_find_depth(node *u);
};

void scapgoattree::printTree(node *root){
    if(root == NULL) return;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        int s = q.size();
		cout<<"-new level-"<<endl;
        while(s--){
            auto p = q.front();
            q.pop();
            cout<<p->value<<endl;
            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
    }
}

int scapgoattree::size(node *node){
	if (node == NULL) return 0;
	return 1 + size(node->left) + size(node->right);
}

bool scapgoattree::insert(float x){
	node *no = new node(x);

	int h = bst_insert_find_depth(no);
	if (h > log32(n)){
		node *p = no->parent;
		while (3*size(p) <= 2*size(p->parent))
			p = p->parent;
		rebuildTree(p->parent);
	}
	return h >= 0;
}

void scapgoattree::rebuildTree(node *u){
	int n = size(u);
	node *p = u->parent;
	node **a = new node* [n];
	toarray(u, a, 0);
	if (p == NULL){
		root = build_again(a, 0, n);
		root->parent = NULL;
	}
	else if (p->right == u){
		p->right = build_again(a, 0, n);
		p->right->parent = p;
	}
	else{
		p->left = build_again(a, 0, n);
		p->left->parent = p;
	}
}

node * scapgoattree::build_again(node **a,int i, int n){
	if (n== 0) return NULL;
	int m = n / 2;

	a[i+m]->left = build_again(a, i, m);

	if (a[i+m]->left != NULL) a[i+m]->left->parent = a[i+m];

	a[i+m]->right = build_again(a, i+m+1, n-m-1);
	if (a[i+m]->right != NULL) a[i+m]->right->parent = a[i+m];

	return a[i+m];
}

int scapgoattree::bst_insert_find_depth(node *u){
	node *w = root;
	if (w == NULL){
		root = u;
		n++;
		return 0;
	}

	bool done = false;
	int d = 0;
	do{
		if (u->value < w->value){
			if (w->left == NULL){
				w->left = u;
				u->parent = w;
				done = true;
			}
			else
				w = w->left;
		}
		else if (u->value > w->value){
			if (w->right == NULL){
				w->right = u;
				u->parent = w;
				done = true;
			}
			else w = w->right;
		}
		else
			return -1;
		d++;
	}
	while (!done);
	n++;
	return d;
}

int main(){

	scapgoattree tree;
	int repeat = 1, c;

	while(repeat == 1){
        cout<<"\n\n---Choose option---\n";
        cout<<" 1) Insert";
        cout<<" 2) Display";
        cout<<" 3) Exit";
        cout<<"\n Enter Choice: ";
        cin>>c;
        switch (c)
        {
            case 1:
                int x,y;
                cout<<"Enter data: "<<endl;
                cin>>x;
                tree.insert(x);
                break;
            case 2:
                tree.printTree();
                break;
            case 3:
                repeat = 0;
                break;
        }
    }
	return 0;
}

