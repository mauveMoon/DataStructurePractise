#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>

using namespace std;

class Graph{
public:
	vector<vector<bool>> edge;
	bool *dfs;
	int Nv;
	Graph(int nv){
		Nv = nv;
		for(int i=0;i<nv;i++){
			vector<bool> t(nv, 0);
			edge.push_back(t);
		}
		dfs = new bool[nv];
	}
	void add_edge(int v1, int v2){
		edge[v1][v2] = 1;
		edge[v2][v1] = 1;
	}
	
	void showEdge(){
		for(auto x:edge){
			for(auto y:x)cout << y << " ";
			cout << endl;
		}
	}
	
	void DFS(int v){
		cout << v << " ";
		dfs[v] = 1;
		for(int i=0;i<Nv;i++){
			if(edge[v][i] && !dfs[i]) DFS(i);
		}
	}
	
	void freshDfs(){
		delete[] dfs;
		dfs = new bool[Nv];
	}
	
	void BFS(int v){
		deque<int> deq;
		deq.push_back(v);
		dfs[v] = 1;
		while(!deq.empty()){
			int tv = deq.front();
			deq.pop_front();
			cout << tv << " ";
			for(int i=0;i<Nv;i++){
				if(edge[tv][i] && !dfs[i]){
					deq.push_back(i);
					dfs[i] = 1;
				}
			}
		}
	}
};


int main(){
	int N=3;
	Graph g(N);
	g.add_edge(1, 2);
//	g.add_edge(2, 4);
//	g.add_edge(2, 0);
//	g.add_edge(4, 1);
//	g.add_edge(2, 4);
//	g.add_edge(3, 5);
	
//	int N, E;
//	cin >> N >> E;
//	int v1, v2;
//	Graph g(N);
//	for(int i=0;i<E;i++){
//		cin >> v1 >> v2;
//		g.add_edge(v1, v2);
//	}
	
	bool *dfs = g.dfs;
	for(int i=0;i<N;i++){
		if(dfs[i] == 0){
			cout << "{ ";
			g.DFS(i);
			cout <<"}"<< endl;
		}
	}
	g.freshDfs();
	dfs = g.dfs;
	for(int i=0;i<N;i++){
		if(dfs[i] == 0){
			cout << "{ ";
			g.BFS(i);
			cout <<"}"<< endl;
		}
	}

	return 0; 
}
