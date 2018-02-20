#include<iostream>
#include<vector>
#include<deque>
#include<cstdio>
using namespace std;

class Graph{
public:
	int nNode;
	vector<vector<bool>> edge;
	Graph(int n){
		nNode = n;
		for(int i=0;i<n;i++){
			vector<bool> t(n, 0);
			edge.push_back(t);
		}
	}
	void add_edge(int v1, int v2){
		edge[v1][v2] = 1;
		edge[v2][v1] = 1;
	}
	
	int six_degree(int v){
		vector<int> nodes(nNode, 0);
		deque<int> bfs;
		bfs.push_back(v);
		nodes[v] = 1;
		
//		vector<int> record;
		int record = 1;
		
		while(!bfs.empty()){
			int top = bfs.front();
			bfs.pop_front();
			if(nodes[top] == 7) break;
			for(int i=0;i<nNode;i++){
				if(edge[top][i] == 1 && nodes[i] == 0){
					bfs.push_back(i);
//					record.push_back(i);
					record ++ ;
					nodes[i] = nodes[top] + 1;
				}
			}
		}
		return record;
	}
	
	
	void show_edge(){
		for(int i=0;i<nNode;i++){
			for(int j=0;j<nNode;j++){
				cout << edge[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main(){
	int N, M;
	cin >> N >> M;
	Graph g(N+1);
	int v1, v2;
	for(int i=0;i<M;i++){
		cin >> v1 >> v2;
		g.add_edge(v1, v2);
	}
	for(int i=1;i<=N;i++){
		int rec = g.six_degree(i);
		printf("%d: %.2f%%\n", i, rec*100.0/N);
	}
	return 0;
}
