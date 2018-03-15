#include<iostream>
#include<vector>

using namespace std;

vector<int> pre;
vector<int> post;
vector<int> in;
bool unique = true;

class Node{
public:
	int Data;
	Node *left;
	Node *right;
	Node(int X):Data(X),left(NULL),right(NULL){}
	
	void inorder(){
		if(left!=NULL) left->inorder();
		in.push_back(Data);
		if(right!=NULL) right->inorder();
	}
};


Node *buildTree(int preL, int preR, int postL, int postR){
	if(preL > preR) return NULL;
	if(preL == preR) {
		Node *T = new Node(pre[preL]);
		return T;
	}
	Node *T = new Node(pre[preL]);
	int obj;
	for(int i = postL;i<postR;i++){
		if(post[i] == pre[preL+1]){
			obj = i;
			break;
		}
	}
	
	if(preR-preL-1 == obj - postL){
		unique = false;
		T->right = buildTree(preL+1, preL+obj-postL+1, postL, obj);
	}else{
		T->left = buildTree(preL+1, preL+obj-postL+1, postL, obj);
		T->right = buildTree(preL+obj-postL+2, preR, obj+1, postR-1);
	}
	return T;
}


int main(){
	int N, X;
	cin >> N;
	for(int i=0;i<N;i++){
		cin >> X;
		pre.push_back(X);
	}
	for(int i=0;i<N;i++){
		cin >> X;
		post.push_back(X);
	}
	Node *tree = buildTree(0, pre.size()-1, 0, post.size()-1);
	if(unique) cout << "Yes" << endl;
	else cout << "No" << endl;
	tree->inorder();
	for(auto it=in.begin();it!=in.end()-1;it++) cout << *it << " ";
	cout << *(in.end()-1) << endl;
	return 0;
}
