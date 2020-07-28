// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco12p2
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20010;
typedef pair<int,int> ii;
vector<ii> grafo[MAXN];
int processado[MAXN][2],n,m;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	while(m--){
		int u,v,peso;
		cin >> u >> v >> peso;
		grafo[u].push_back(ii(v,peso));
	}
	set<ii> Dijkstra;
	Dijkstra.insert(ii(0,1));
	while(!Dijkstra.empty()){
		ii davez = *Dijkstra.begin();
		Dijkstra.erase(Dijkstra.begin());
		int v = davez.second,dist = davez.first;
		//cout << "V " << v << " D" << dist << " " << processado[v][0] << " " <<  processado[v][1] << endl;
		if(v == n && processado[v][0]){
			cout << dist << endl;
			return 0;
		} 
		if(processado[v][0]){
			if(processado[v][1]) continue;
			processado[v][1] = 1;
		}
		else{
			processado[v][0] = 1;
		}
		for(ii prox : grafo[v]){
			Dijkstra.insert(ii(dist + prox.second,prox.first));
		}
	}
	cout << -1 << endl;
	return 0;
}