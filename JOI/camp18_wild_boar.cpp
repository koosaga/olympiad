#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
const int MAXL = 100005;
const int MAXT = 270000;
using lint = long long;
using pi = pair<lint, int>;

struct edg{
	int pos, idx, cost;
};

int n, m, q, l;
vector<edg> gph[MAXN];
lint dist[MAXN * 2][MAXN * 2];

struct path_info{
	int midl, midr;
	lint cost;
	bool operator<(const path_info &p)const{
		return cost < p.cost;
	}
};

vector<path_info> plist[MAXN][MAXN];
int ed[MAXN * 2], cost[MAXN * 2];

void preprocess(){
	for(int i=0; i<m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		ed[2 * i] = e; ed[2 * i + 1] = s;
		cost[2 * i] = cost[2 * i + 1] = x;
		gph[s].push_back({e, i*2, x});
		gph[e].push_back({s, i*2+1, x});
	}
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<2*m; i++){
		dist[i][i] = cost[i];
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		pq.emplace(cost[i], i);
		int vis[MAXN] = {};
		while(!pq.empty()){
			auto x = pq.top(); pq.pop();
			if(dist[i][x.second] != x.first) continue;
			vis[ed[x.second]]++;
			if(vis[ed[x.second]] > 2) continue;
			for(auto &j : gph[ed[x.second]]){
				if((j.idx ^ x.second) == 1) continue;
				if(dist[i][j.idx] > x.first + j.cost){
					dist[i][j.idx] = x.first + j.cost;
					pq.emplace(dist[i][j.idx], j.idx);
				}
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i != j){
				vector<path_info> pth;
				for(auto &k : gph[i]){
					for(auto &l : gph[j]){
						lint cost = dist[k.idx][l.idx ^ 1];
						pth.push_back({k.pos, l.pos, cost});
					}
				}
				sort(pth.begin(), pth.end());
				if(pth.size() <= 2){
					plist[i][j] = pth;
					continue;
				}
				plist[i][j].push_back(pth[0]);
				plist[i][j].push_back(pth[1]);
				if(pth[0].midl != pth[1].midl && pth[0].midr != pth[1].midr){
					plist[i][j].push_back(pth[2]);
					pi nxt_punkty = pi(-1, -1);
					if(pth[2].midl == pth[1].midl){
						nxt_punkty = pi(pth[2].midl, pth[0].midr);
					}
					else if(pth[2].midl == pth[0].midl){
						nxt_punkty = pi(pth[2].midl, pth[1].midr);
					}
					else if(pth[2].midr == pth[1].midr){
						nxt_punkty = pi(pth[0].midl, pth[2].midr);
					}
					else if(pth[2].midr == pth[0].midr){
						nxt_punkty = pi(pth[1].midl, pth[2].midr);
					}
					for(int k = 3; k < pth.size(); k++){
						if(nxt_punkty.first != pth[k].midl && nxt_punkty.second != pth[k].midr){
							plist[i][j].push_back(pth[k]);
							break;
						}
					}
				}
				else if(pth[0].midl == pth[1].midl){
					for(int x = 0; x < pth.size(); x++){
						if(pth[x].midl != pth[0].midl){
							plist[i][j].push_back(pth[x]);
							pi nxt_punkty = pi(pth[0].midl, pth[x].midr);
							for(int k = x + 1; k < pth.size(); k++){
								if(nxt_punkty.first != pth[k].midl && nxt_punkty.second != pth[k].midr){
									plist[i][j].push_back(pth[k]);
									break;
								}
							}
							break;
						}
					}
				}
				else if(pth[0].midr == pth[1].midr){
					for(int x = 0; x < pth.size(); x++){
						if(pth[x].midr != pth[0].midr){
							plist[i][j].push_back(pth[x]);
							pi nxt_punkty = pi(pth[x].midl, pth[0].midr);
							for(int k = x + 1; k < pth.size(); k++){
								if(nxt_punkty.first != pth[k].midl && nxt_punkty.second != pth[k].midr){
									plist[i][j].push_back(pth[k]);
									break;
								}
							}
							break;
						}
					}
				}
				else assert(0);
			//	for(auto &k : plist[i][j]) printf("(%d -> %d), (%d -> %d), %lld\n", i, k.midl, k.midr, j, k.cost);
			}
		}
	}
}

int a[MAXL], lim;
struct seg{
	int l[4], r[4];
	lint cost[4][4];
}tree[MAXT];

seg merge(seg &a, seg &b){
	seg c;
	for(int i=0; i<4; i++){
		c.l[i] = a.l[i];
		c.r[i] = b.r[i];
	}
	memset(c.cost, 0x3f, sizeof(c.cost));
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				for(int l=0; l<4; l++){
					if(!a.r[k] || !b.l[i] || a.r[k] != b.l[l]) c.cost[i][j] = min(c.cost[i][j], a.cost[i][k] + b.cost[l][j]);
				}
			}
		}
	}
	return c;
}

void upd(int v){
	memset(tree[v + lim].cost, 0x3f, sizeof(tree[v + lim].cost));
	for(int i=0; i<plist[a[v-1]][a[v]].size(); i++){
		tree[v + lim].l[i] = plist[a[v-1]][a[v]][i].midl;
		tree[v + lim].r[i] = plist[a[v-1]][a[v]][i].midr;
		tree[v + lim].cost[i][i] = plist[a[v-1]][a[v]][i].cost;
	}
	v += lim;
	while(v > 1){
		v >>= 1;
		tree[v] = merge(tree[2*v], tree[2*v+1]);
	}
}

int main(){
	scanf("%d %d %d %d",&n,&m,&q,&l);
	preprocess();
	for(int i=0; i<l; i++) scanf("%d",&a[i]);
	for(lim = 1; lim <= l; lim <<= 1);
	for(int i=1; i<l; i++) upd(i);
	for(int i=0; i<q; i++){
		int x, v; scanf("%d %d",&x,&v);
		x--;
		a[x] = v;
		if(x > 0) upd(x);
		if(x + 1 < l) upd(x + 1);
		lint ret = 1e18;
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++) ret = min(ret, tree[1].cost[j][k]);
		}
		if(ret > 9e17) ret = -1;
		printf("%lld\n", ret);
	}
}
