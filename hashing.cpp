#include<iostream>
#include<vector>

#define Index int

using namespace std;

class HashTable{
public:
	int TSize;
	vector<int> Data;
	HashTable(int n){
		TSize = n;
		for(int i=0;i<n;i++){
			Data.push_back(-1);
		}
	}
	
	Index push(int X){
		for(int j=0;j<TSize;j++){
			int pos = (X+j*j) % TSize;
			if(Data[pos] == -1){
				Data[pos] = X;
				return pos;
			}
		}
		
		return -1;
	}
};

bool isPrime(int n){
	if(n <= 1) return false;
	for(int i=2;i<n;i++){
		if(n%i == 0) return false;
	}
	return true;
}

int leastPrime(int n){
	do{
		if(isPrime(n)) break;
	}while(n++);
	return n;
}


int main(){
	int M, N;
	cin >> M >> N;
	int TSize = leastPrime(M);
	HashTable ht(TSize);
	int X;
	vector<int> index;
	for(int i=0;i<N;i++){
		cin >> X;
		int ind = ht.push(X);
		index.push_back(ind);
	}
	for(int i=0;i<N-1;i++){
		if(index[i]==-1) cout << "- ";
		else cout << index[i] << " ";
	}
	if(index[N-1] == -1) cout << "-" << endl;
	else cout << index[N-1] << endl;
	return 0;
}
