/*PTA的编译器上会报warning，应该跟使用了c++11的特性有关，不过能正常运行，不管了*/
#include<iostream>

using namespace std;

class AVLNode{
public:
	int Data;
	AVLNode *left;
	AVLNode *right;
	int height;
	AVLNode(int X):Data(X), height(0), left(NULL), right(NULL){};
};

class AVLTree{
private:
	AVLNode *root;
	AVLNode *Insert(AVLNode *&T, int X){
		if(T == NULL) T = new AVLNode(X);
		else if(X < T->Data){
			T->left = Insert(T->left, X);
			if(getHeight(T->left) - getHeight(T->right) >= 2){
				if(X < T->left->Data) T = LL(T);
				else if(X > T->left->Data) T = LR(T);
			}
		}else if(X > T->Data){
			T->right = Insert(T->right, X);
			if(getHeight(T->right) - getHeight(T->left) >= 2){
				if(X > T->right->Data) T = RR(T);
				else if(X < T->right->Data) T = RL(T);
			}
		}
		T->height = max(getHeight(T->left), getHeight(T->right))+1;
		return T;
	}
	AVLNode *RR(AVLNode *A){
		AVLNode *B = A->right;
		A->right = B->left;
		B->left = A;
		
		A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
		B->height = max(getHeight(B->left), A->height) + 1;
		return B;
	}
	AVLNode *LL(AVLNode *A){
		AVLNode *B = A->left;
		A->left = B->right;
		B->right = A;
		
		A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
		B->height = max(getHeight(B->left), A->height) + 1;
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
	int getHeight(AVLNode *T){
		if(T == NULL) return 0;
		else if(T != NULL && T->left == NULL && T->right == NULL) return 1;
		else return max(getHeight(T->left), getHeight(T->right))+1;
	}
public:
	AVLTree():root(NULL){}
	~AVLTree(){};
	
	void Insert(){
		int X;
		cin >> X;
		Insert(root, X);
	}
	void getRoot(){
		cout << root->Data << endl;
	}
};

int main(){
	int N;
	cin >> N;
	AVLTree T;
	while(N--) T.Insert();
	T.getRoot();
	return 0;
}
