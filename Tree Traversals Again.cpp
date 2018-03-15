#include<iostream>
#include<vector>
#include<stack>
#include<string>

using namespace std;

vector<int> pre;
vector<int> in;
vector<int> post;

class Node{
public:
	int Data;
	Node *left;
	Node *right;
	Node(int V):Data(V),left(NULL),right(NULL){}
	void postorder(){
		if(left!=NULL) left->postorder();
		if(right!=NULL)right->postorder();
		post.push_back(Data);
	}
};


Node* buildTree(int pL, int pR, int iL, int iR){
	if(pL > pR) return NULL;
	Node *T = new Node(pre[pL]);
	
	int mid;
	for(int i=iL;i<=iR;i++){
		if(in[i] == pre[pL]){
			mid = i;
			break;
		}
	}
	int n = mid - iL;
	T->left = buildTree(pL+1, pL+n, iL, mid-1);
	T->right = buildTree(pL+n+1, pR, mid+1, iR);
	return T;
}

int main(){

	int N, X;
	cin >> N;
	string mark;
	stack<int> sta;
	for(int i=0;i<2*N;i++){
		cin >> mark;
		if(mark == "Push"){
			cin >> X;
			pre.push_back(X);
			sta.push(X);
		}else if(mark == "Pop"){
			X = sta.top();
			sta.pop();
			in.push_back(X);
		}
	}
	Node *root = buildTree(0, N-1, 0, N-1);
	root->postorder();
	for(int i=0;i<N-1;i++) cout << post[i] << " ";
	cout << post[N-1] << endl;
	return 0;
}
