#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>

using namespace std;

class Record{
public:
	int ID, members;
	double avg_m, avg_a;
	Record(int iID, int im, int itm, int ita){
		ID = iID;
		members = -1*im;
		avg_m = 1.0*itm/members;
		avg_a = 1.0*ita/members;
	}
	void output(){
		printf("%04d %d %.3lf %.3lf\n", ID, members, avg_m, avg_a);
	}
};

bool cmp(Record rec1, Record rec2){
	if(rec1.avg_a > rec2.avg_a) return true;
	else if(rec1.avg_a == rec2.avg_a && rec1.ID < rec2.ID) return true;
	else return false;
}

class UFSet{
public:
	map<int, int> S;   
	map<int, int> M;     
	map<int, int> A;  
	
	UFSet(){
		
	}
	
	int Find(int X){
		auto it = S.find(X);
		if(it == S.end()) {
			S[X] = -1;
			M[X] = 0;
			A[X] = 0;
			return X;
		}else if(S[X] < 0) return X;
		else return S[X] = Find(S[X]); 
	}
	
	void Union(int X1, int X2){
		if(X1 == -1 || X2 == -1) return ;
		int Root1 = Find(X1), Root2 = Find(X2);
		if(Root1 == Root2) return ;
		else if(Root1 < Root2){
			S[Root1] += S[Root2];
			S[Root2] = Root1;
			M[Root1] += M[Root2];
			A[Root1] += A[Root2];
		}else {
			S[Root2] += S[Root1];
			S[Root1] = Root2;
			A[Root2] += A[Root1];
			M[Root2] += M[Root1]; 
		}
	}
	void addM(int X, int tM){
		int Root = Find(X);
		M[Root] += tM;
		return ;
	}
	void addA(int X, int tA){
		int Root = Find(X);
		A[Root] += tA;
		return ;
	}

	void output(){
		int cnt = 0;
		vector<int> roots;
		for(auto it=S.begin();it!=S.end();it++){
			if(it->second < 0) {
				cnt++;
				roots.push_back(it->first);
			}
		}
		cout << cnt << endl; 
		vector<Record> records;
		for(auto x:roots) {
			Record t(x, S[x], M[x], A[x]);
			records.push_back(t);
		}
		sort(records.begin(), records.end(), cmp);
		for(auto x:records){
			x.output();
		}
	}
	
	void Input(){
		int ID, F, M, k, C, tM, tA;
		cin >> ID >> F >> M >> k;
		int idR = Find(ID);
		Union(ID, F);
		Union(ID, M);
		while(k--){
			cin >> C;
			Union(ID, C);
		}
		cin >> tM >> tA;
		addM(ID, tM);
		addA(ID, tA);
		return ;
	}
};

int main(){
	UFSet uf;
	int N;
	cin >> N;
	while(N--){
		uf.Input();
	}
	uf.output();
	return 0;
}
