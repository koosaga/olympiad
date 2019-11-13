#include <bits/stdc++.h>
using namespace std;
const int MAXN = 82;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

struct disj{
	int pa[MAXN], comp;
	void init(int n){
		comp = n;
		iota(pa, pa + n, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		comp--;
		pa[q] = p; return 1;
	}
}disj;

struct edge{
	int s, e, x, idx;
};

int main(){
	int t; scanf("%d",&t);
	while(t--){
		int n, m;
		scanf("%d %d",&n,&m);
		n++;
		vector<edge> edg;
		vector<int> cnt(MAXN), indep(MAXN);
		int ans = 0;
		disj.init(n);
		for(int i=0; i<m; i++){
			int x, y; scanf("%d %d",&x,&y);
			cnt[i] = x - y;
			for(int j=0; j<x; j++){
				int s, e, x; scanf("%d %d %d",&s,&e,&x);
				s--;
				edg.push_back({s, e, x, i});
				disj.uni(s, e);
				ans += x;
			}
		}
		if(disj.comp != 1){
			puts("-1");
			continue;
		}
		int tot_edge = accumulate(cnt.begin(), cnt.end(), 0);
		if(sz(edg) - tot_edge < n - 1){
			puts("-1");
			continue;
		}
		for(int i=0; i<tot_edge; i++){
			bool X1[MAXN] = {};
			bool X2[MAXN] = {};
			vector<int> gph[MAXN];
			int vtx_cost[MAXN];
			for(int j=0; j<sz(edg); j++){
				if(indep[j]){
					vtx_cost[j] = -edg[j].x;
					continue;
				}
				vtx_cost[j] = edg[j].x;
				disj.init(n);
				for(int k=0; k<sz(edg); k++){
					if(j != k && !indep[k]) disj.uni(edg[k].s, edg[k].e);
				}
				if(disj.comp == 1) X1[j] = 1;
				else{
					for(int k=0; k<sz(edg); k++){
						if(indep[k] && disj.find(edg[k].s) != disj.find(edg[k].e)){
							gph[k].push_back(j);
						}
					}
				}
				if(cnt[edg[j].idx] > 0) X2[j] = 1;
				else{
					for(int k=0; k<sz(edg); k++){
						if(indep[k] && edg[j].idx == edg[k].idx){
							gph[j].push_back(k);
						}
					}
				}
			}
			pi dist[MAXN]; int par[MAXN];
			fill(dist, dist + MAXN, pi(-1e9, 1e9));
			memset(par, -1, sizeof(par));
			queue<int> que;
			bool inq[MAXN] = {};
			for(int j=0; j<sz(edg); j++){
				if(X1[j]){
					dist[j] = pi(vtx_cost[j], 0);
					que.push(j);
					inq[j] = 1;
				}
			}
			while(sz(que)){
				auto x = que.front(); que.pop();
				inq[x] = 0;
				for(auto &i : gph[x]){
					if(dist[i] < pi(dist[x].first + vtx_cost[i], -dist[x].second - 1)){
						dist[i] = pi(dist[x].first + vtx_cost[i], -dist[x].second - 1);
						par[i] = x;
						if(!inq[i]){
							inq[i] = 1;
							que.push(i);
						}
					}
				}
			}
			int snk = -1;
			pi valSnk = pi(-9e8, 9e8);
			for(int j=0; j<sz(edg); j++){
				if(X2[j] && valSnk < dist[j]){
					valSnk = dist[snk = j];
				}
			}
			if(snk == -1){
				ans = 1e9;
				break;
			}
			ans -= valSnk.first;
			while(~snk){
				if(indep[snk]) cnt[edg[snk].idx]++;
				else cnt[edg[snk].idx]--;
				indep[snk] ^= 1;
				snk = par[snk];
			}
		}
		if(ans > 1e8) puts("-1");
		else cout << ans << endl;
	}
}

