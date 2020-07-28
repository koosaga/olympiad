// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco11p2
#include <bits/stdc++.h>
#define MT make_tuple
#define PB push_back
#define MAXN 1601
#define MAXS 3600
using namespace std;
typedef pair<int,int> ii;
typedef tuple<int,int,int> tripla;
vector<ii> above[MAXN],under[MAXN];
int S,N,M,s,t;
int processado[MAXN][MAXS];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> S >> N >> M;
	while(M--){
		int u,v,p,tipo;
		cin >> u >> v >> p >> tipo;
		if(tipo == 0){
			under[u].PB(ii(v,p));
			under[v].PB(ii(u,p));
		}
		else{
			above[u].PB(ii(v,p));
			above[v].PB(ii(u,p));
		}
	}
	priority_queue<tripla, vector<tripla>, greater<tripla> > pq;
	pq.push(MT(0,0,0));
	while(!pq.empty()){
		tripla davez = pq.top();
		pq.pop();
		int dist = get<0>(davez),tempo = get<1>(davez),v = get<2>(davez);
		if(v == N - 1){
			cout << dist << endl;
			return 0;
		}
		if(processado[v][tempo]) continue;
		processado[v][tempo] = 1;
		for(ii prox : above[v]){
			if(tempo + prox.second <= S) pq.push(MT(dist + prox.second,tempo + prox.second, prox.first));
		}
		for(ii prox : under[v]){
			pq.push(MT(dist + prox.second,tempo, prox.first));
		}
	}
	cout << -1 << endl;
	return 0;
}