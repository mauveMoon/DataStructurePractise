#include<iostream>
#include<vector>
#define INF 100000

using namespace std;

class Graph{
public:
	int nNode;
	vector<vector<int>> edge;
	Graph(int n){
		nNode = n;
		for(int i=0;i<nNode;i++){
			vector<int> t(n ,0);
			edge.push_back(t);
		}
	}
	void add_edge(int v1, int v2, int weight){
		edge[v1][v2] = weight;
		edge[v2][v1] = weight;
	}
	int prim(int v){
		vector<int> dist(nNode, INF);
		vector<int> collected(nNode, 0);
		
		collected[v] = 1;
		dist[v] = 0;
		for(int i=0;i<nNode;i++){
			if(edge[v][i] > 0){
				dist[i] = edge[v][i];
			}
		}
		
		while(1){
			int minDist = INF, minPos = -1;
			for(int i=0;i<nNode;i++){
				if(dist[i] < minDist && collected[i] == 0){
					minDist = dist[i];
					minPos = i;
				}
			}
			if(minPos == -1) break;
			collected[minPos] = 1;
			for(int i=0;i<nNode;i++){
				if(edge[minPos][i] > 0 && collected[i] == 0 && edge[minPos][i] < dist[i]){
					dist[i] = edge[minPos][i];
				}
			}
		}
		int ans = 0;
		for(int i=1;i<nNode;i++){
			if(collected[i] == 0) return -1;
			ans += dist[i];
		}
		return ans;
	}
};

int main(){
	int N, M;
	cin >> N >> M;
	int v1, v2, weight;
	Graph g(N+1);
	for(int i=0;i<M;i++){
		cin >> v1 >> v2 >> weight;
		g.add_edge(v1, v2, weight);
	}
	int ans = g.prim(1);
	cout << ans << endl;
	return 0;
}
