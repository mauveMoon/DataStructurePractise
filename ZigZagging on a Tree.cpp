#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;

class Node{
public:
	int Data;
	Node *left;
	Node *right;
	Node(int V):Data(V),left(NULL),right(NULL){}
};

Node *buildTree(vector<int> in, int iL, int iR, vector<int> post, int pL, int pR){
	if(iL > iR) return NULL;
	Node *T = new Node(post[pR]);
	int mid;
	for(int i=iL;i<=iR;i++){
		if(in[i] == post[pR]){
			mid = i;
			break;
		}
	}
	T->left = buildTree(in, iL, mid-1, post, pL, pL+mid-iL-1);
	T->right = buildTree(in, mid+1, iR, post, pL+mid-iL, pR-1);
	return T;
}

class Tree{
public:
	Node *root;
	Tree():root(NULL){}
	~Tree(){}
	Tree(vector<int> in, vector<int> post){
		root = buildTree(in, 0, in.size()-1, post, 0, post.size()-1);
	}
	void solve(){
		vector<int> ans;   // 最终结果 
		deque<Node*> deq1;
		deque<Node*> deq2;
		deque<Node*> *temp1;
		deque<Node*> *temp2;
		vector<vector<int>> ord; // 层序遍历
		
		deq1.push_back(root);
		
		while(!deq1.empty() || !deq2.empty()){
			vector<int> t;
			
			if(!deq1.empty() && deq2.empty()) {
				temp1 = &deq1;
				temp2 = &deq2;
			}else if(!deq2.empty() && deq1.empty()){
				temp1 = &deq2;
				temp2 = &deq1;
			}
			
			while(!temp1->empty()){
				Node* front = temp1->front();
				temp1->pop_front();
				t.push_back(front->Data);
				if(front->left!=NULL) temp2->push_back(front->left);
				if(front->right!=NULL) temp2->push_back(front->right);
			}
			ord.push_back(t);
		} 
		
		int size = ord.size();
		for(int i=0;i<size;i++){
			vector<int> t = ord[i];
			if(i%2 == 0){  // 逆序 
				reverse(t.begin(), t.end());
				for(auto it=t.begin();it!=t.end();it++) ans.push_back(*it);
			}else{         // 正序 
				for(auto it=t.begin();it!=t.end();it++)	ans.push_back(*it);
			}
		}
		for(auto it=ans.begin();it!=ans.end()-1;it++) cout << *it << " ";
		cout << *(ans.end()-1) << endl;
		return ;
	}
};

int main(){
	int N, X;
	vector<int> in;
	vector<int> post;
	cin >> N;
	for(int i=0;i<N;i++){
		cin >> X;
		in.push_back(X);
	}
	for(int i=0;i<N;i++){
		cin >> X;
		post.push_back(X);
	}
	Tree test(in, post);
	test.solve();
	return 0;
}
