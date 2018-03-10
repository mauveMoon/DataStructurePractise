#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<sstream>
using namespace std;

class Node{
public:
	int left, right, data;
	Node(int id, int il, int ir):data(id), left(il), right(ir){};
};

int trans(string x){
	int ans;
	if(x == "-") ans = -1;
	else{
		stringstream ss;
		ss << x;
		ss >> ans;
	}
	return ans;
}

class Tree{
public:
	vector<Node> tree;
	int nNode;
	Tree(int n):nNode(n){};
	
	int Insert(){
		string il, ir;
		int left, right;
		vector<bool> isRoot(nNode, 1);
		for(int i=0;i<nNode;i++){
			cin >> il >> ir;
			int left = trans(il);
			int right = trans(ir);
			Node t(i, left, right);
			tree.push_back(t);
			if(left != -1) isRoot[left] = 0;
			if(right != -1) isRoot[right] = 0;
		}
		for(int i=0;i<nNode;i++){
			if(isRoot[i]) return i;
		}
	}
	void levelorder(int root){
		deque<int> bfs;
		bfs.push_back(root);
		int cnt = 0;
		int end = root;
		while(!bfs.empty()){
			int front = bfs.front();
			bfs.pop_front();
			if(front == -1){
				if(cnt == nNode) cout << "YES " << end << endl;
				else cout << "NO " << root << endl;
				return ;
			}else{
				end = front;
				cnt++;
			}
			bfs.push_back(tree[front].left);
			bfs.push_back(tree[front].right);
		}
	}
};

int main(){
	int N;
	cin >> N;
	Tree t(N);
	int root = t.Insert();
	t.levelorder(root);
	return 0;
}
