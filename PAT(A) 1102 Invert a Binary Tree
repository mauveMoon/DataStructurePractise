#include<iostream>
#include<vector>
#include<deque>
#include<sstream>
#include<string>

using namespace std;

int trans(string t){
	stringstream ss;
	int r;
	ss << t;
	ss >> r;
	return r;
}

class Node{
public:
	int Data;
	int left, right;
	Node(int V):Data(V),left(-1),right(-1){}
	
};

class Tree{
public:
	int nNode;
	vector<Node> tree;
	int root;
	Tree(int N){
		nNode = N;
		for(int i=0;i<N;i++){
			Node t(i);
			tree.push_back(t);
		}
		root = 0;
	}
	void Input(){
		vector<bool> isRoot(nNode, 1);
		string t1, t2;
		for(int i=0;i<nNode;i++){
			cin >> t1 >> t2;
			if(t1 == "-") tree[i].right = -1;
			else {
				int idx = trans(t1);
				tree[i].right = idx;
				isRoot[idx] = 0;	
			}
			if(t2 == "-") tree[i].left = -1;
			else {
				int idx = trans(t2);
				tree[i].left = idx;
				isRoot[idx] = 0;
			}
		}
		for(int i=0;i<nNode;i++){
			if(isRoot[i]){
				root = i;
				break;
			}
		}
		return ;
	}
	vector<int> level(){
		vector<int> ans;
		
		deque<Node> deq;
		deq.push_back(tree[root]);
		
		while(!deq.empty()){
			Node front = deq.front();
			deq.pop_front();
			ans.push_back(front.Data);
			
			if(front.left!=-1) deq.push_back(tree[front.left]);
			if(front.right!=-1) deq.push_back(tree[front.right]);
		}
		return ans;
	}
	
	void inorder(vector<int> &ans, int root){
		if(tree[root].left!=-1) inorder(ans, tree[root].left);
		ans.push_back(root);
		if(tree[root].right!=-1) inorder(ans, tree[root].right);
	}
	
	vector<int> inorder(){
		vector<int> ans;
		inorder(ans, root);
		return ans;
	}
	
	void solve(){
		vector<int> leo = level();
		vector<int> ino = inorder();
		for(int i=0;i<nNode-1;i++) cout << leo[i] << " ";
		cout << leo[nNode-1] << endl;
		
		for(int i=0;i<nNode-1;i++) cout << ino[i] << " ";
		cout << ino[nNode-1] << endl;
		return ;
	}
};

int main(){
	int N;
	cin >> N;
	Tree tree(N);
	tree.Input();
	tree.solve();
	return 0;
}
