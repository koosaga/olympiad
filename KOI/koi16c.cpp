#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, q, par[18][200005];
int dep[200005], dfn[200005], sz[200005], piv;
vector<int> gph[200005];

struct bit{
	int tree[200005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

void dfs(int x){
	sz[x] = 1;
	dfn[x] = ++piv;
	for(auto &i : gph[x]){
		dep[i] = dep[x] + 1;
		dfs(i);
		sz[x] += sz[i];
	}
}

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=17; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int main(){
	cin >> n >> q;
	for(int i=2; i<=n; i++){
		scanf("%d",&par[0][i]);
		gph[par[0][i]].push_back(i);
	}
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	dfs(1);
	while(q--){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		int w = bit.query(dfn[s]) + bit.query(dfn[e]) - 2 * bit.query(dfn[lca(s, e)]);
		puts(w == 0 ? "YES" :  "NO");
		if(x){
			int k = (w == 0 ? s : e);
			if(k){
				bit.add(dfn[k], 1);
				bit.add(dfn[k] + sz[k], -1);
			}
		}
	}
}
