#include<iostream>

using namespace std;

class Node{
public:
	int data;
	Node *left;
	Node *right;
	Node(int id){
		data = id;
		left = NULL;
		right = NULL;
	}
	void insert(int value){
		if(value < data){
			if(left != NULL) left->insert(value);
			else if(left == NULL) left = new Node(value);
		}else {
			if(right != NULL) right->insert(value);
			else if(right == NULL) right = new Node(value);
		}
	}
	void preorder(){
		if(left != NULL) left->preorder();
		cout << data << " ";
		if(right != NULL) right->preorder();
	}
}; 

class BSTree{
public:
	Node *root;
	BSTree(){
		root = NULL;
	}
	void insert(int value){
		if(root == NULL) root = new Node(value);
		else root->insert(value);
	}
	void output(){
		if(root == NULL) cout << endl;
		else root->preorder();
	}
};

bool isEqual(Node *root1, Node *root2){
	if(root1 == NULL && root2 == NULL) return true;
	if((root1 == NULL && root2 != NULL) || (root1 != NULL && root2 == NULL)) return false;
	
	if( (root1->data != root2->data) && (root1 != NULL && root2 != NULL) ) return false;
	if( (root1->data == root2->data) && (root1 != NULL && root2 != NULL) ) return isEqual(root1->left, root2->left) && isEqual(root1->right, root2->right);
	
}

int main(){
	int N = 1, L;
	int value;
	bool jud;
	
	while(1){
		cin >> N;
		if(N == 0) break; 
		BSTree main_tree;
		cin >> L;
		for(int i=0;i<N;i++){
			cin >> value;
			main_tree.insert(value);
		}
		while(L--){
			BSTree tree;
			for(int i=0;i<N;i++){
				cin >> value;
				tree.insert(value);			
			}
			jud = isEqual(main_tree.root, tree.root);
			if(jud) cout << "Yes" << endl;
			else cout << "No" << endl;
		}	
	}

	return 0; 
}

