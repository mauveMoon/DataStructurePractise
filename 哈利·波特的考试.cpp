#include<iostream>
#include<vector>
#define INF 10000000
#include<algorithm>
#include<deque>

using namespace std;

class Graph{
public:
	int nNode;
	vector<vector<int>> edge;
	Graph(int n){
		nNode = n;
		for(int i=0;i<nNode;i++){
			vector<int> t(nNode, 0);
			edge.push_back(t);
		}
	}
	void add_edge(int v1, int v2, int weight){
		edge[v1][v2] = weight;
		edge[v2][v1] = weight;
	}
	
	int dijkstra(int v1){    // 返回dist中的最大值 
		vector<int> dist(nNode, INF);
		vector<int> path(nNode, -1);
		vector<bool> collected(nNode, 0);
		collected[v1] = 1;
		for(int i=0;i<nNode;i++){
			if(edge[v1][i] > 0) dist[i] = edge[v1][i];
		}
		while(1){
			int minDist = INF;
			int minPos = -1;
			for(int i=0;i<nNode;i++){
				if(dist[i] < minDist && collected[i]==0){
					minDist = dist[i];
					minPos = i;
				}
			}
			if(minPos == -1) break;
			collected[minPos] = 1;
			for(int i=0;i<nNode;i++){
				if(edge[minPos][i] > 0 && collected[i] == 0 && dist[i] > dist[minPos] + edge[minPos][i]){
					dist[i] = dist[minPos] + edge[minPos][i];
					path[i] = minPos;
				}
			}
		}
		int ans = -1;
		for(int i=0;i<nNode;i++){
			if(dist[i] != INF && dist[i] > ans){
				ans = dist[i];
			}
		}
		return ans;

	}
	void show_edge(){
		for(int i=0;i<nNode;i++){
			for(int j=0;j<nNode;j++){
				cout << edge[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	bool isConnectGraph(){
		deque<int> bfs;
		vector<bool> pass(nNode, 0);
		bfs.push_back(1);
		while(!bfs.empty()){
			int top = bfs.front();
			bfs.pop_front();
			pass[top] = 1;
			for(int i=0;i<nNode;i++){
				if(edge[top][i] > 0 && pass[i] == 0) bfs.push_back(i);
			}
		}
		bool jud = false;
		for(int i=1;i<nNode;i++){
			if(pass[i]==0) jud = true;  
		}
		return jud;
	}
};

int main(){
	int N, M;
	cin >> N >> M;
	Graph g(N+1);
	int v1, v2, w;
	for(int i=0;i<M;i++){
		cin >> v1 >> v2 >> w;
		g.add_edge(v1, v2, w);
	}
	
	if(g.isConnectGraph()){
		cout << 0 << endl;
		return 0;
	}
	
	int minValue = INF;
	int t;
	int minPos;
	for(int i=1;i<=N;i++){
		t = g.dijkstra(i);
		if(t < minValue && t!=-1){
			minValue = t;
			minPos = i;
		}
	}
	cout << minPos << " " << minValue << endl;

	return 0;
}
