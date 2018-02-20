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
	vector<vector<int>> fee;
	Graph(int n){
		nNode = n;
		for(int i=0;i<nNode;i++){
			vector<int> t(nNode, 0);
			vector<int> r(nNode, 0);
			edge.push_back(t);
			fee.push_back(r);
		}
	}
	void add_edge(int v1, int v2, int d, int f){
		edge[v1][v2] = d;
		edge[v2][v1] = d;
		fee[v1][v2] = f;
		fee[v2][v1] = f;
	}
	
	vector<vector<int>> dijkstra(int v1){    // 返回dist中的最大值 
		vector<int> dist(nNode, INF);
		vector<int> money(nNode, 0);
		vector<bool> collected(nNode, 0);
		collected[v1] = 1;
		for(int i=0;i<nNode;i++){
			if(edge[v1][i] > 0){
				dist[i] = edge[v1][i];
				money[i] = fee[v1][i];
			}
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
				if(edge[minPos][i] > 0 && collected[i] == 0){
					if(dist[i] > dist[minPos] + edge[minPos][i]){
						dist[i] = dist[minPos] + edge[minPos][i];
						money[i] = money[minPos] + fee[minPos][i];
					}else if(dist[i] == dist[minPos] + edge[minPos][i] && money[i] > money[minPos] + fee[minPos][i]){
						money[i] = money[minPos] + fee[minPos][i];
					}
				}
			}
		}
		vector<vector<int>> ans;
		ans.push_back(dist);
		ans.push_back(money);
		return ans;

	}
};

int main(){
	int N, M, S, D;
	cin >> N >> M >> S >> D;
	Graph g(N);
	int v1, v2, d, f;
	for(int i=0;i<M;i++){
		cin >> v1 >> v2 >> d >> f;
		g.add_edge(v1, v2, d, f);
	}
	auto ans = g.dijkstra(S);
	vector<int> dist = ans[0];
	vector<int> money = ans[1];

	cout << dist[D] << " " << money[D] << endl;
	return 0;
}
