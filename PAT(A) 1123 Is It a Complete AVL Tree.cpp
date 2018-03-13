#include<iostream>
#include<queue>
#define Node AVLNode
#define height Height
using namespace std;

class AVLNode{
public:
	int Data;
	AVLNode *left;
	AVLNode *right;
	int Height;
	AVLNode(int V):Data(V), left(NULL), right(NULL), Height(0){}
	
	void preorder(){
		cout << Data << " ";
		if(left != NULL) left->preorder();
		if(right != NULL) right->preorder();
	}
};

class AVLTree{
public:
	AVLNode *root;
	int nNode;
	AVLTree():root(NULL),nNode(0){}
	~AVLTree(){}
	
	int getHeight(AVLNode *T){
		if(T == NULL) return 0;
		return max(getHeight(T->left), getHeight(T->right))+ 1;
	}
	
	AVLNode *Insert(AVLNode *&T, int X){
		
		if(T == NULL){
			T = new AVLNode(X);
		}else if(X < T->Data){
			T->left = Insert(T->left, X);
			if(getHeight(T->left) - getHeight(T->right) >= 2){
				if(X < T->left->Data) T = LL(T);
				else T = LR(T);
			}
		}else if(X > T->Data){
			T->right = Insert(T->right, X);
			if(getHeight(T->right) - getHeight(T->left) >= 2){
				if(X > T->right->Data) T = RR(T);
				else T = RL(T);
			}
		}
		T->Height = max(getHeight(T->left), getHeight(T->right)) + 1;
		
		return T;
	}
	
	AVLNode* LL(AVLNode *A){
		AVLNode *B = A->left;
		A->left = B->right;
		B->right = A;
		
		A->Height = max(getHeight(A->left), getHeight(A->right)) + 1;
		B->Height = max(getHeight(B->left), A->Height) + 1;
		return B;
	}	
	AVLNode* RR(AVLNode *A){
		AVLNode *B = A->right;
		A->right = B->left;
		B->left = A;
		
		A->Height = max(getHeight(A->left), getHeight(A->right)) + 1;
		B->Height = max(getHeight(B->right), A->Height) + 1;
		return B;
	}	
	AVLNode *RL(AVLNode *A){
		A->right = LL(A->right);
		return RR(A);
	}
	
	AVLNode *LR(AVLNode *A){
		A->left = RR(A->left);
		return LL(A);
	}
	
	void Insert(int X){
		Insert(root, X);
		nNode ++;
	}
	void preorder(){
		root->preorder();
	}
	
	void solve(){
		queue<AVLNode*> dfs;
		vector<int> temp;
		temp.push_back(root->Data);
		dfs.push(root);
		
		int cnt = 1;
		bool isComplete = true;
		while(!dfs.empty()){
			AVLNode *front = dfs.front();
			dfs.pop();
		
			if(front->left!=NULL) {
				dfs.push(front->left);
				temp.push_back(front->left->Data);
				cnt++;
			}else {
				if(cnt != nNode) isComplete = false;
			}
			
			if(front->right!=NULL) {
				dfs.push(front->right);
				temp.push_back(front->right->Data);
				cnt++;
			}else {
				if(cnt != nNode) isComplete = false;
			}
			
		}
		for(auto it=temp.begin();it!=temp.end()-1;it++) cout << *it << " ";
		
		cout << *(temp.end()-1) << endl;
		if(isComplete) cout << "YES" << endl;
		else cout << "NO" << endl;
		return ;
	}
};

int main(){
	AVLTree avl;
	int N, X;
	cin >> N;
	while(N--){
		cin >> X;
		avl.Insert(X);
	}
	avl.solve();
	return 0;
}
