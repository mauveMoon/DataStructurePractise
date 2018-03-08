#include<iostream>
#include<vector>
#include<set>

using namespace std;

class UFSet{
public:
	vector<int> S;
	UFSet(){
		vector<int> *temp = new vector<int>(10005, -1);
		S = *temp;
	}

	int Find(int X){
		if(S[X] < 0) return X;
		else return S[X] = Find(S[X]);
	}
	void Union(int X1, int X2){
		int Root1 = Find(X1);
		int Root2 = Find(X2);
		if(S[Root1] < S[Root2]){
			S[Root1] += S[Root2];
			S[Root2] = Root1;
		}else{
			S[Root2] += S[Root1];
			S[Root1] = Root2;
		}
	}
	int components(set<int> rec){
		int cnt = 0;
		for(auto X:rec){
			if(S[X] < 0) cnt++;
		}
		return cnt;
	}
};


int main(){
	int N, k, v, w;
	cin >> N;
	UFSet uf;
	set<int> rec;
	while(N--){
		cin >> k;
		cin >> v;
		rec.insert(v);
		for(int i=1;i<k;i++){
			cin >> w;
			rec.insert(w);
			uf.Union(v, w);
		}
	}
	int comp = uf.components(rec);
	int nums = rec.size();
	cout << comp << " " << nums << endl;
	cin >> N;
	while(N--){
		cin >> v >> w;
		int Root1 = uf.Find(v);
		int Root2 = uf.Find(w);
		if(Root1 == Root2) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
