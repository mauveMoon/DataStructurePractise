#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Node{
public:
	int Data;
	int nums; // 节点数
	Node *left;
	Node *right;
	Node(int id):Data(id), left(NULL),right(NULL){
		if(Data > 0) nums=1;
		else nums = 0;
	}
	void preorder(){
		if(left != NULL) left->preorder();
		cout << nums << " ";
		if(right != NULL) right->preorder();
	}

};

Node *buildTree(vector<int> pre, int L, int R){
	if(L > R) return NULL;
	Node *T = new Node(pre[L]);
	int cnt = 0;
	for(int i=L+1;i<=R;i++){
		if(pre[i] > 0) cnt ++;
	}
	T->nums = cnt;
	int i=L+1;
	for(;i<=R;i++){
		if(abs(pre[i]) > abs(pre[L])) break; 
	}
	T->left = buildTree(pre, L+1, i-1);
	T->right = buildTree(pre, i, R);
	return T;
}

class Tree{
public:
	Node *root;
	vector<int> leaves;
	vector<int> redNodeChildren;
	Node* Insert(Node *&T, int id){
		if(T == NULL) {
			T = new Node(id);
		}else{
			if(abs(id)>abs(T->Data)){
				T->right = Insert(T->right, id);
			}else if(abs(id) < abs(T->Data)){
				T->left = Insert(T->left, id);
			}
			if(id>0) T->nums ++;
		}
		return T;
	}
	void getLeaves(Node *T){
		if(T->left == NULL && T->right == NULL && T!=NULL) {
			int v = T->Data;
			leaves.push_back(v);
		}
		 else {
			if(T->left!=NULL) getLeaves(T->left);
			if(T->right!=NULL)getLeaves(T->right);
		}
	}
	void getRedNodeChildren(Node *T){
		if(T==NULL) return ;
		if(T->Data<0) {
			if(T->left!=NULL) redNodeChildren.push_back(T->left->Data);
			if(T->right!=NULL) redNodeChildren.push_back(T->right->Data);
		}
		getRedNodeChildren(T->left);
		getRedNodeChildren(T->right);
	}
	bool samePath(Node *T){
		if(T == NULL) return true;
		if(T->left != NULL && T->right != NULL) return (T->left->nums == T->right->nums) && samePath(T->left) && samePath(T->right);
		else if(T->left == NULL && T->right != NULL) return (0 == T->right->nums);
		else if(T->left != NULL && T->right == NULL) return (T->left->nums == 0);
		else if(T->left == NULL && T->right == NULL) return true;
	}
public:
	Tree():root(NULL){};
	Tree(vector<int> pre){
		int R = pre.size()-1;
		root = buildTree(pre, 0, R);
	}
	~Tree(){}
	
	void Insert(int id){
		Insert(root, id);
	}
	
	void preorder(){
		root->preorder();
	}
	bool rootIsBlack(){
		return root->Data > 0;
	}
	bool leavesAreBlack(){
		leaves.clear();
		getLeaves(root);
		bool areBlack = true;
		for(int x:leaves){
			if(x < 0) areBlack = false;
		}
		return areBlack;
	}
	bool redNodeChildrenAreBlack(){
		redNodeChildren.clear();
		getRedNodeChildren(root);
		bool areBlack = true;
		for(int x:redNodeChildren){
			if(x < 0) areBlack = false;
		}
		return areBlack;
	}
	bool samePath(){
		return samePath(root);
	}
	void solve(){
		bool jud = rootIsBlack() && redNodeChildrenAreBlack() && samePath();
		if(jud) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
};

int main(){
	int k, N, X;
	cin >> k;
	while(k--){
		vector<int> temp;
		cin >> N;
		while(N--){
			cin >> X;
			temp.push_back(X);
		}
		Tree tree(temp);
		tree.solve();
	}
	return 0;
}
