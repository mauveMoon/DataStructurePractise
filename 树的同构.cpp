#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

class Node{
public:
	char data;
	int left, right;
	Node(char id, int ileft, int iright){
		data = id;
		left = ileft;
		right = iright;
	}	
};

vector<Node> buildTree(int n, int &root){
	vector<Node> tree;
	vector<int> check(n, 0);
	if(n == 0) return tree;
	
	char id, icleft, icright;
	int ileft, iright;
	for(int i=0;i<n;i++){
		cin >> id >> icleft >> icright;
		ileft = (icleft == '-')?-1:icleft-'0';
		iright = (icright == '-')?-1:icright-'0';
		Node t(id, ileft, iright);
		tree.push_back(t);
		if(ileft != -1) check[ileft] = 1;
		if(iright != -1)check[iright] = 1;
	}
	for(int i=0;i<n;i++){
		if(check[i] == 0){
			root = i;
			break;
		}
	}
	return tree;
}

bool isOmorphic(vector<Node> tree1, int &root1, vector<Node> tree2, int &root2){
	bool jud;
	
//	if (root1!=-1 && root2!=-1) cout << "root:" << " " << tree1[root1].data << " " << tree2[root2].data  << endl;
	
	if(root1 == -1 && root2 == -1) jud = true;
	else if((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1)) jud = false;
	
	else if(tree1[root1].data == tree2[root2].data){
		if(isOmorphic(tree1, tree1[root1].left, tree2, tree2[root2].left) && isOmorphic(tree1, tree1[root1].right, tree2, tree2[root2].right)){
			jud = true;
		}else if(isOmorphic(tree1, tree1[root1].left, tree2, tree2[root2].right) && isOmorphic(tree1, tree1[root1].right, tree2, tree2[root2].left)){
			jud = true;
		}else jud = false;
	}else jud = false;
	return jud;
}

int main(){
	int m, n;
	int root1, root2;
	cin >> m;
	vector<Node> tree1 = buildTree(m, root1);
	cin >> n;
	vector<Node> tree2 = buildTree(n, root2);
	
	if(m == 0 && n==0){
		cout << "Yes" << endl;
		return 0;
	}else if((m==0 && n!=0) || (m!=0 && n==0)){
		cout << "No" << endl;
		return 0;
	}
	
	bool jud;
	if(m!=n) jud = false;
	else jud = isOmorphic(tree1, root1, tree2, root2);
	
	if(jud) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
