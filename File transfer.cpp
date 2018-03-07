#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

class UFSet{
public:
	vector<int> S;
	int nNode;
	UFSet(int n){
		nNode = n;
		while(n--) S.push_back(-1);
	}
	int Find(int X){
		if(S[X]<0) return X;
		else return S[X] = Find(S[X]);
	}
	void Union(int X1, int X2){
		int root1 = Find(X1);
		int root2 = Find(X2);
		if(S[root2] < S[root1]){
			S[root2] += S[root1];
			S[root1] = root2;
		}else {
			S[root1] += S[root2];
			S[root2] = root1;	
		}
	}
	int components(){
		int cnt=0;
		for(int i=1;i<nNode;i++){
			if(S[i]<0) cnt++;
		}
		return cnt;
	}
};

int main(){
	int N, v1, v2;
	char op;
	cin >> N;
	UFSet uf(N+1);
	while(1){
		cin >> op;
		if(op == 'C') {
			cin >> v1 >> v2;
			int r1 = uf.Find(v1), r2 = uf.Find(v2);
			if(r1 != r2) cout << "no" << endl;
			else cout << "yes" << endl;
		}else if(op == 'I'){
			cin >> v1 >> v2;
			uf.Union(v1, v2);
		}else if(op == 'S'){
			int comp = uf.components();
			if(comp==1) cout << "The network is connected." << endl;
			else printf("There are %d components.", comp);
			break;
		}
	}
	return 0;
}
