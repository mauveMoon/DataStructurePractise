#include<iostream>
#include<deque>
#include<vector>
#include<list>
#define INF 100000

using namespace std;

class Edge{
public:
	int v, w;
	Edge(int iv, int iw){
		v = iv;
		w = iw;
	}
};

class Graph{
public:
	int nNode;
	vector<list<Edge>> edge;
	Graph(int n){
		nNode =  n;
		for(int i=0;i<nNode;i++){
			list<Edge> t;
			edge.push_back(t);
		}
	}
	
	void add_edge(int v1, int v2, int w){
		Edge e1 = Edge(v2, w);
		Edge e2 = Edge(v1, w);
		edge[v1].push_back(e1);
		edge[v2].push_back(e2);
	}
	
	vector<int> dijkstra(int v1, int v2, vector<int> nTeam){
		vector<int> dist(nNode, INF);
		vector<int> nPath(nNode, 0);
		vector<bool> visited(nNode, 0);
		vector<int> team(nNode, 0);
		
		dist[v1] = 0;
		team[v1] = nTeam[v1];
		nPath[v1] = 1;
		
		while(1){
			int minPos = -1, minDist = INF;
			for(int i=0;i<nNode;i++){
				if(dist[i] < minDist && !visited[i]){
					minPos = i;
					minDist = dist[i];
				}
			}
			if(minPos == -1) break;
			visited[minPos] = 1;
			for(auto x:edge[minPos]){
				if(dist[minPos] + x.w < dist[x.v] && !visited[x.v]){
					nPath[x.v] = nPath[minPos];
					dist[x.v] = dist[minPos] + x.w;
					team[x.v] = team[minPos] + nTeam[x.v];
				}else if(dist[minPos] + x.w == dist[x.v] && !visited[x.v]){
					nPath[x.v] = nPath[minPos] + nPath[x.v];
					if(team[x.v] < team[minPos] + nTeam[x.v]) team[x.v] = team[minPos] + nTeam[x.v];
				}
			}
		}
		vector<int> arr(2, 0);
		arr[0] = nPath[v2];
		arr[1] = team[v2];
		return arr;
	}
};

int main(){
	int N, M, v1, v2;
	cin >> N >> M >> v1 >> v2;
	vector<int> nTeam(N, 0);
	Graph g(N);
	int iv1, iv2, iw;
	for(int i=0;i<N;i++) cin >> nTeam[i];
	for(int i=0;i<M;i++) {
		cin >> iv1 >> iv2 >> iw;
		g.add_edge(iv1, iv2, iw);
	}
	vector<int> arr = g.dijkstra(v1, v2, nTeam);
	cout << arr[0] <<" " << arr[1] << endl;
	return 0;
}
