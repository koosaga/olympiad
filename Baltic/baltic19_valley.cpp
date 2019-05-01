#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

struct edg{
	int s, e, x;
}ed[MAXN];

vector<pi> gph[MAXN];
int n, m, q, r, din[MAXN], dout[MAXN], lvl[MAXN], piv;
lint dp[MAXN], dep[MAXN];
int par[17][MAXN];
lint spt[17][MAXN];

bool sub(int s, int e){
	return din[s] <= din[e] && dout[e] <= dout[s];
}

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dep[i.second] = dep[x] + i.first;
		lvl[i.second] = lvl[x] + 1;
		par[0][i.second] = x;
		dfs(i.second, x);
		dp[x] = min(dp[x], dp[i.second] + i.first);
	}
	dout[x] = piv;
}

int main(){
	scanf("%d %d %d %d",&n,&m,&q,&r);
	for(int i=1; i<n; i++){
		scanf("%d %d %d",&ed[i].s,&ed[i].e,&ed[i].x);
		gph[ed[i].s].emplace_back(ed[i].x, ed[i].e);
		gph[ed[i].e].emplace_back(ed[i].x, ed[i].s);
	}
	memset(dp, 0x3f, sizeof(dp));
	while(m--){
		int x; scanf("%d",&x); dp[x] = 0;
	}
	dfs(r, -1);
	for(int i=1; i<n; i++){
		if(par[0][ed[i].s] == ed[i].e) swap(ed[i].s, ed[i].e);
	}
	for(int i=1; i<=n; i++){
		spt[0][i] = dp[i] - dep[i];
	}
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
			spt[i][j] = min(spt[i-1][j], spt[i-1][par[i-1][j]]);
		}
	}
	while(q--){
		int idx, pos;
		scanf("%d %d",&idx,&pos);
		idx = ed[idx].e;
		if(!sub(idx, pos)){
			puts("escaped");
			continue;
		}
		lint ret = 1e18;
		int step = lvl[pos] - lvl[idx] + 1;
		int opo = pos;
		for(int i=0; i<17; i++){
			if((step >> i) & 1){
				ret = min(ret, spt[i][pos]);
				pos = par[i][pos];
			}
		}
		ret += dep[opo];
		if(ret > 1e17) puts("oo");
		else printf("%lld\n", ret);
	}
}
