// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c3p6
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

const ll MOD = 1e9 + 7;
const int MAXN = 1510;
const int MAXM = 5010;

vector<int> grafo[MAXN];
int N,M,processado[MAXN],dist[MAXN],e1[MAXM],e2[MAXM],e3[MAXM];
ll dp1[MAXN],dp2[MAXN],dp3[MAXM];

void processa(int s){
	memset(processado,0,sizeof(processado));
	memset(dist,0,sizeof(dist));
	memset(dp1,0,sizeof(dp1));
	memset(dp2,0,sizeof(dp2));
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0,s));
	while(!pq.empty()){
		int d = pq.top().first, v = pq.top().second;
		pq.pop();
		if(processado[v]) continue;
		processado[v] = 1;
		dist[v] = d;
		for(int i : grafo[v]){
			int u = e2[i],w = e3[i];
			if(!processado[u]) pq.push(ii(d+w,u));
		}
	}
	vector<ii> ordenado;
	for(int i = 1;i<=N;i++){
		ordenado.push_back(ii(dist[i],i));
	}
	sort(ordenado.begin(),ordenado.end());
	dp1[s] = 1;
	for(ii par : ordenado){
		int v = par.second;
		for(int i : grafo[v]){
			int u = e2[i],w = e3[i];
			if(dist[v] + w == dist[u]){
				dp1[u] = (dp1[u] + dp1[v]) % MOD;
			}
		}
	}
	reverse(ordenado.begin(),ordenado.end());
	for(ii par : ordenado){
		int v = par.second;
		dp2[v]++;
		for(int i : grafo[v]){
			int u = e2[i],w = e3[i];
			if(dist[v] + w == dist[u]){
				dp2[v] = (dp2[v] + dp2[u]) % MOD;
			}
		}
	}
	for(int i = 1;i<=M;i++){
		if(dist[e1[i]] + e3[i] != dist[e2[i]]) continue;
		dp3[i] += (dp1[e1[i]]*dp2[e2[i]]);
		dp3[i] %= MOD;
	}
}

int main(){
	cin >> N >> M;
	for(int i = 1;i<=M;i++){
		cin >> e1[i] >> e2[i] >> e3[i];
		grafo[e1[i]].push_back(i);
	}
	for(int i = 1;i<=N;i++) processa(i);
	for(int i = 1;i<=M;i++) cout << dp3[i] << endl;
	return 0;
}