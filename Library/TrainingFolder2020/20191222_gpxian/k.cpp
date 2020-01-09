#include <bits/stdc++.h>
#include <any>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 998244353;
const int MAXN = 800005;

struct disj{
	int pa[MAXN];
	int sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;

struct edge{
	int s, e, x;
	bool operator<(const edge &e)const{
		return x < e.x;
	}
}ed[MAXN];

int n, m;
vector<pi> gph[MAXN];
lint dist[MAXN];

void dijkstra(int x){
	memset(dist, 0x3f, sizeof(dist));
	priority_queue<pi, vector<pi>, greater<pi>> pq;
	pq.emplace(0, x); dist[x] = 0;
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dist[i.second] > i.first + x.first){
				dist[i.second] = i.first + x.first;
				pq.emplace(dist[i.second], i.second);
			}
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&ed[i].s,&ed[i].e,&ed[i].x);
		gph[ed[i].s].emplace_back(2 * i, ed[i].e);
		gph[ed[i].e].emplace_back(2 * i + 1, ed[i].s);
	}
	disj.init(2 * m);
	vector<int> vtx;
	for(int i=1; i<=n; i++){
		sort(all(gph[i]), [&](const pi &a, const pi &b){
			int p1 = a.second - i + n;
			int p2 = b.second - i + n;
			return p1 % n < p2 % n;
		});
		for(int j=0; j+1<sz(gph[i]); j++){
			int l = gph[i][j].first ^ 1;
			int r = gph[i][j+1].first;
			disj.uni(l, r);
		}
		vtx.push_back(gph[i][0].first);
	}
	for(int i=1; i<=n; i++) gph[i].clear();
	vector<edge> spt;
	for(int i=0; i<m; i++){
		int l = disj.find(2 * i);
		int r = disj.find(2 * i + 1);
		spt.push_back({l, r, ed[i].x});
	}
	disj.init(2 * m);
	for(int i=0; i<n; i++){
		printf("%d ", vtx[i]);
		disj.sz[disj.find(vtx[i])]++;
	}
	puts("");
	sort(all(spt));
	lint ret = 0;
	for(auto &i : spt){
		int l = disj.find(i.s);
		int r = disj.find(i.e);
		if(l != r){
		printf("%d %d %d\n", i.s, i.e, i.x);
			ret += (1ll * disj.sz[l] * disj.sz[r] % mod) * i.x;
			ret %= mod;
			disj.uni(i.s, i.e);
		}
	}
	cout << ret % mod << endl;
}
