/*
尽力了，这个题目真是有点难，写了3个多小时最后拿了27分
dijkstra解这个题目有局限性，以后再有机会的话尝试一下用dfs吧 
死活过不了的测试点7：
10 4 4 5
6 7 5 0
0 1 1
0 2 1
1 3 1
2 3 1
3 4 1 
*/

#include<iostream>
#include<vector>
#include<list>
#define INF 100000

using namespace std;

list<int> copy(list<int> li){
	list<int> t;
	for(auto x:li)t.push_back(x);
	return t;
}

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
		nNode = n;
		for(int i=0;i<nNode;i++){
			list<Edge> t;
			edge.push_back(t);
		}
		
	}
	void add_edge(int v1, int v2, int w){
		Edge e1(v2, w);
		Edge e2(v1, w);
		edge[v1].push_back(e1);
		edge[v2].push_back(e2);
	}
	void dijkstra(int v, vector<int> c){  // 目标地, 点权重，已减 
		vector<bool> visited(nNode, 0);
		vector<int> dist(nNode, INF);
		vector<int> front(nNode, -1);
		
		vector<list<int>> PBMC(nNode);
		for(int i=0;i<nNode;i++) PBMC[i].push_back(0);
		
		dist[0] = 0;
		
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
				if(dist[minPos] + x.w < dist[x.v] && !visited[x.v]){
					dist[x.v] = dist[minPos] + x.w;
					front[x.v] = minPos;
					PBMC[x.v].clear();
					PBMC[x.v] = copy(PBMC[minPos]);
					int val = PBMC[x.v].back()+c[x.v];
					if(val >= 0) PBMC[x.v].push_back(val);
					else{
						for(auto it = PBMC[x.v].begin();it!=PBMC[x.v].end();it++)*it -= val;
						PBMC[x.v].push_back(0);
					}
				}else if(dist[minPos] + x.w == dist[x.v] && !visited[x.v]){
					// 生成新序列再对比 
					list<int> t = copy(PBMC[minPos]);
					int val = t.back()+c[x.v];
					if(val >= 0) t.push_back(val);
					else{
						for(auto it = t.begin();it!=t.end();it++)*it -= val;
						t.push_back(0);
					}
					if(t.front() < PBMC[x.v].front()){
						front[x.v] = minPos;
						PBMC[x.v].clear();
						PBMC[x.v] = t;
					}
				}
			}
		}
		
		list<int> path_;
		vector<int> path;
		int end = v;
		while(end != -1){
			path_.push_front(end);
			end = front[end];
		}
		for(auto x:path_) path.push_back(x);
		
		cout << PBMC[v].front() << " ";
		for(auto it=path.begin(); it!=path.end()-1;it++)cout << *it << "->";
		cout << *(path.end()-1) << " " << PBMC[v].back();;
		
		return ;
	}
	
	void show_edge(){
		for(int i=0;i<nNode;i++){
			cout << i << ": ";
			for(auto x:edge[i]){
				cout << x.v << "," << x.w << " ";
			}
			cout << endl;
		}

	}
};

int main(){
	int CM, N, SP, M;
	cin >> CM >> N >> SP >> M;
	vector<int> c;
	Graph g(N+1);
	c.push_back(0);
	int h;
	while(N--){
		cin >> h;
		c.push_back(h-CM/2);
	}
	int v1, v2, w;
	while(M--){
		cin >> v1 >> v2 >> w;
		g.add_edge(v1, v2, w);
	}
	g.dijkstra(SP, c);
	return 0;
}
