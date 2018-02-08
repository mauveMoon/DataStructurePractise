#include<iostream>
#include<vector>
#include<deque>
#define Null -1

using namespace std;

class Node{
public:
	int data;
	int left, right;
	Node(int id, int il, int ir){
		data = id;
		left = il;
		right = ir;
	}
};

vector<Node> buildTree(int N, int &root){
	vector<Node> tree;
	char icleft, icright;
	int ileft, iright;
	vector<int> check(N, 0);
	for(int i=0;i<N;i++){
		cin >> icleft >> icright;
		ileft = (icleft == '-')?Null:icleft-'0';
		iright = (icright == '-')?Null:icright-'0';
		Node t(i, ileft, iright);
		tree.push_back(t);
		if(ileft != Null) check[ileft] = 1;
		if(iright != Null )check[iright] = 1;
	}
	for(int i=0;i<N;i++){
		if(check[i] == 0) root = i;
	}
	return tree;
}

vector<int> listLeaves(vector<Node> tree, int root){
	deque<Node> deq;
	vector<int> list;
	deq.push_back(tree[root]);
	while(!deq.empty()){
		Node t = deq.front();
		deq.pop_front();
		if(t.left == Null && t.right == Null) list.push_back(t.data);
		if(t.left != Null) deq.push_back(tree[t.left]);
		if(t.right != Null) deq.push_back(tree[t.right]);
	}
	return list;
}

int main(){
	int n;
	cin >> n;
	int root;
	vector<Node> tree =  buildTree(n, root);
	vector<int> list = listLeaves(tree, root);
	for(auto it=list.begin(); it!=list.end()-1;it++){
		cout << *it << " ";
	}
	cout << *(list.end() - 1) << endl;
	return 0;
}
