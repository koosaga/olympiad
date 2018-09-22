#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 100005;

struct query{
	int s, t;
	lint l;
};

int n, m, s, t;
vector<pi> gph[MAXN];
lint dist[MAXN], lim[MAXN];
int par[17][MAXN], dep[MAXN];
int pa[MAXN];

int paint(int s, int e, lint x){
	if(pa[s] != s) return pa[s] = paint(pa[s], e, x);
	if(dep[s] <= dep[e]) return s;
	if(lim[s] > 1e18) lim[s] = x - dist[s];
	return pa[s] = paint(par[0][s], e, x);
}

bool trial(lint L){
	if(L < lim[s]) return false;
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	pq.push(pi(0, s));
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > x.first + i.first && x.first + i.first + lim[i.second] <= L){
				dist[i.second] = x.first + i.first;
				pq.push(pi(dist[i.second], i.second));
			}
		}
	}
	return dist[t] <= L;
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int main(){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	memset(dist, 0x3f, sizeof(dist));
	pq.push(pi(0, t));
	dist[t] = 0;
	while(!pq.empty()){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > x.first + i.first){
				dist[i.second] = x.first + i.first;
				dep[i.second] = dep[x.second] + 1;
				par[0][i.second] = x.second;
				pq.push(pi(dist[i.second], i.second));
			}
		}
	}
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	vector<query> evt;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			int u = i, v = j.second;
			if(par[0][u] == v || par[0][v] == u) continue;
			int l = lca(u, v);
			lint dis = dist[u] + j.first + dist[v];
			if(dis > 1e18) continue;
			evt.push_back({l, v, dis});
		}
	}
	sort(evt.begin(), evt.end(), [&](const query &a, const query &b){
		return a.l < b.l;
	});
	memset(lim, 0x3f, sizeof(lim));
	lim[t] = 0;
	iota(pa, pa + n + 1, 0);
	for(auto &i : evt){
		paint(i.t, i.s, i.l);
	}
	lint s = 0, e = 1e15;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	if(e > 9e14) e = -1;
	cout << e << endl;
}

