#include<iostream>
#include<vector>
#include<list>
#include<cstdio>
#define INF 10000

using namespace std;

class Edge{
public:
	int v, d, t;
	Edge(int iv, int id, int it){
		v = iv;
		d = id;
		t = it;
	}
};

class Graph{
public:
	int nNode;
	vector<list<Edge>> edge;
	Graph(int n){
		nNode = n;
		while(n--){
			list<Edge> t;
			edge.push_back(t);
		}
	}
	void add_edge(int v1, int v2, bool sd, int d, int t){
		if(sd){
			Edge e1(v2, d, t);
			edge[v1].push_back(e1);
		}else if(!sd){
			Edge e1(v2, d, t);
			Edge e2(v1, d, t);
			edge[v1].push_back(e1);
			edge[v2].push_back(e2);
		}
	}
	vector<int> dijkstra_dist(int v1, int v2, int &ans){
		vector<int> dist(nNode, INF);
		vector<int> time(nNode, 0);
		vector<int> front(nNode, -1);
		vector<bool> visited(nNode, 0);
		
		dist[v1] = 0;
		
		while(1){
			int minPos = -1, minDist = INF;
			for(int i=0;i<nNode;i++){
				if(dist[i] < minDist && !visited[i]){
					minDist = dist[i];
					minPos = i;
				}
			}
			if(minPos == -1) break;
			visited[minPos] = 1;
			
			for(auto x:edge[minPos]){
				if(dist[minPos] + x.d < dist[x.v] && !visited[x.v]){
					dist[x.v] = dist[minPos] + x.d;
					front[x.v] = minPos;
					time[x.v] = time[minPos] + x.t;
				}else if(dist[minPos] + x.d == dist[x.v] && !visited[x.v] && time[minPos] + x.t < time[x.v]){
					front[x.v] = minPos;
					time[x.v] = time[minPos] + x.t;
				}
			}
		}
		list<int> path;
		int end = v2;
		path.push_back(end);
		while(front[end] != -1){
			end = front[end];
			path.push_front(end);
		}
		ans = dist[v2];
		vector<int> vec_path;
		for(auto x:path) vec_path.push_back(x);
		return vec_path;
	}
	vector<int> dijkstra_time(int v1, int v2, int &ans){
		vector<int> pre(nNode, 0);
		vector<int> time(nNode, INF);
		vector<int> front(nNode, -1);
		vector<bool> visited(nNode, 0);
		
		time[v1] = 0;
		
		while(1){
			int minPos = -1, minTime = INF;
			for(int i=0;i<nNode;i++){
				if(time[i] < minTime && !visited[i]){
					minTime = time[i];
					minPos = i;
				}
			}
			if(minPos == -1) break;
			visited[minPos] = 1;
			
			for(auto x:edge[minPos]){
				if(time[minPos] + x.t < time[x.v] && !visited[x.v]){
					time[x.v] = time[minPos] + x.t;
					front[x.v] = minPos;
					pre[x.v] = pre[minPos] + 1;
				}else if(time[minPos] + x.t == time[x.v] && !visited[x.v] && pre[minPos] + 1 < pre[x.v]){
					front[x.v] = minPos;
					pre[x.v] = pre[minPos] + 1;
				}
			}
		}
		list<int> path;
		int end = v2;
		path.push_back(end);
		while(front[end] != -1){
			end = front[end];
			path.push_front(end);
		}
		ans = time[v2];
		
		vector<int> vec_path;
		for(auto x:path) vec_path.push_back(x);
		return vec_path;
	}
	void dijkstra(int v1, int v2){
		int minDist = 0, minTime = 0;
		vector<int> dist_path = dijkstra_dist(v1, v2, minDist);
		vector<int> time_path = dijkstra_time(v1, v2, minTime);

		bool same = true;
		int dps = dist_path.size(), tps = time_path.size();
		if(dps == tps){
			for(int i=0;i<dps;i++){
				if(dist_path[i] != time_path[i]){
					same = false;
					break;
				}
			}
		}else {
			same = false;
		}
		if(same){
			printf("Distance = %d; Time = %d: ", minDist, minTime);
			for(auto it=dist_path.begin();it!=dist_path.end()-1;it++) cout << *it << " -> ";
			cout << *(dist_path.end()-1) << endl;
		}else if(!same){
			printf("Distance = %d: ", minDist);
			for(auto it=dist_path.begin();it!=dist_path.end()-1;it++) cout << *it << " -> ";
			cout << *(dist_path.end()-1) << endl;
			printf("Time = %d: ", minTime);
			for(auto it=time_path.begin();it!=time_path.end()-1;it++) cout << *it << " -> ";
			cout << *(time_path.end()-1) << endl;
		}
	}
};

int main(){
	int N, M;
	cin >> N >> M;
	Graph g(N);
	int v1, v2, d, t;
	bool sd;
	for(int i=0;i<M;i++){
		cin >> v1 >> v2 >> sd >> d >> t;
		g.add_edge(v1, v2, sd, d, t);
	}
	cin >> v1 >> v2;
	g.dijkstra(v1, v2);
	return 0;
}
