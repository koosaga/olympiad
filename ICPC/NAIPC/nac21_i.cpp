#include <bits/stdc++.h>
using namespace std;
const int MAXN = 91005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 998244353;
const int offset = int(1e6);

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

int n, m, g;
vector<vector<edg>> route;
vector<pi> gph[MAXN];
bool foo[2][MAXN];
lint dist[MAXN];
int par[MAXN];
bool inq[MAXN];

vector<int> nxt[MAXN];
int tpar[MAXN], tpae[MAXN], dep[MAXN];

void dfs(int x, int p = -1){
	for(auto &[j, i] : gph[x]){
		if(i != p){
			tpar[i] = x;
			tpae[i] = j;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

void matroid_intersection(){
	vector<pi> v;
	vector<edg> eflat;
	for(int i = 0; i < sz(route); i++){
		for(int j = 0; j < sz(route[i]); j++){
			eflat.push_back(route[i][j]);
			v.emplace_back(i, j);
		}
	}
	vector<int> indep(sz(v));
	lint ret = 0;
	while(true){
		bool found = 0;
		disj.init(n);
		vector<int> i2(sz(route));
		vector<int> by(sz(route));
		vector<int> inds;
		for(int i=0; i<sz(v); i++){
			if(indep[i]){
				i2[v[i].first] = 1;
				by[v[i].first] = i;
				inds.push_back(i);
				disj.uni(eflat[i].s, eflat[i].e);
			}
		}
		for(int i=0; i<sz(v); i++){
			if(!indep[i]){
				edg ed = eflat[i];
				foo[0][i] = disj.find(ed.s) != disj.find(ed.e);
				foo[1][i] = !i2[v[i].first];
				if(foo[0][i] && foo[1][i] && ed.x == -offset){
					indep[i] = 1;
					found = 1;
					i2[v[i].first] = 1;
					disj.uni(ed.s, ed.e);
					ret += ed.x;
				}
			}
			else foo[0][i] = foo[1][i] = 0;
		}
		if(found) continue;
		for(int i = 0; i <= n; i++){
			gph[i].clear();
			dep[i] = 0;
		}
		for(int i = 0; i < MAXN; i++){
			nxt[i].clear();
		}
		vector<int> always; 
		for(int i=0; i<sz(v); i++){
			if(indep[i]){
				gph[eflat[i].s].emplace_back(i, eflat[i].e);
				gph[eflat[i].e].emplace_back(i, eflat[i].s);
			}
		}
		for(int i = 0; i <= n; i++){
			if(!dep[i]){
				dep[i] = 1;
				dfs(i, -1);
			}
		}
		for(int i = 0; i < sz(v); i++){
			if(!indep[i]){
				if(foo[0][i]) always.push_back(i);
				else{
					int p = eflat[i].s, q = eflat[i].e;
					if(dep[p] < dep[q]) swap(p, q);
					while(dep[p] > dep[q]){
						nxt[tpae[p]].push_back(i);
						p = tpar[p];
					}
					while(p != q){
						nxt[tpae[p]].push_back(i);
						nxt[tpae[q]].push_back(i);
						p = tpar[p];
						q = tpar[q];
					}
				}
			}
		}
		memset(dist, 0x3f, sizeof(dist));
		memset(par, -1, sizeof(par));
		queue<int> que;
		for(int i = 0; i < sz(v); i++){
			if(foo[0][i]){
				dist[i] = 0;
				que.push(i); inq[i] = 1;
			}
		}
		while(sz(que)){
			int x = que.front();
			que.pop();
			inq[x] = 0;
			int w = eflat[x].x * 1024 + 1;
			if(indep[x]) w = -w;
			auto qq = [&](int y){
				if(dist[y] > dist[x] + w){
					dist[y] = dist[x] + w;
					par[y] = x;
					if(!inq[y]){
						inq[y] = 1;
						que.push(y);
					}
				}
			};
			if(foo[1][x]){
				qq(sz(v));
			}
			if(x == sz(v)) continue;
			if(!indep[x]){
				if(i2[v[x].first]){
					qq(by[v[x].first]);
				}
			}
			if(indep[x]){
				for(auto &y : nxt[x]) qq(y);
			}
		}
		if(dist[sz(v)] > 1e17) break;
		ret += (dist[sz(v)] - (dist[sz(v)] & 1023)) / 1024;
		//cout << dist[sz(v)] / 1024 << endl;
		for(int j=sz(v); par[j]!=-1; j=par[j]){
		//	printf("reverse %d ", par[j]);
			indep[par[j]] ^= 1;
		}
		//cout << endl;
	}
	if(count(all(indep), 1) != n){
		puts("-1");
		return;
	}
	ret += g * offset;
	if(ret < 0 || ret > offset){
		puts("-1");
		return;
	}
	cout << ret << endl;
}


int main(){
	scanf("%d %d %d",&n,&m,&g);
	vector<edg> ed, mst;
	for(int i = 0; i < m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		ed.push_back({s, e, x});
	}
	sort(all(ed));
	disj.init(n);
	for(auto &i : ed){
		if(disj.uni(i.s, i.e)) mst.push_back(i);
	}
	route.resize(g);
	for(auto &v : route){
		int k; scanf("%d",&k);
		v.resize(k);
		for(auto &w : v){
			scanf("%d",&w.e);
			w.x = -offset;
		}
	}
	for(auto &i : mst){
		vector<edg> e = {i};
		route.push_back(e);
	}
	matroid_intersection();
}
