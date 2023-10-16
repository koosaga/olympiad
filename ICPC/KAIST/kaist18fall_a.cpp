#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, c, q, dfn[MAXN], chn[MAXN], sz[MAXN], par[MAXN], piv;
vector<int> gph[MAXN];

void dfs0(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		par[i] = x;
		dfs0(i);
		sz[x] += sz[i];
	}
}

void dfs1(int x){
	dfn[x] = ++piv;
	if(gph[x].empty()) return;
	chn[gph[x][0]] = chn[x];
	dfs1(gph[x][0]);
	for(int i=1; i<gph[x].size(); i++){
		chn[gph[x][i]] = gph[x][i];
		dfs1(gph[x][i]);
	}
}

int has[MAXN], cnt[MAXN];
vector<pi> stk[MAXN];

void change_color(int col, int c){
	cnt[has[col]]--;
	has[col] += c;
	cnt[has[col]]++;
}

int main(){
	scanf("%d %d %d",&n,&c,&q);
	cnt[0] = c;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].emplace_back(e);
		gph[e].emplace_back(s);
	}
	dfs0(1);
	chn[1] = 1;
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end(), [&](const int &a, const int &b){
			return sz[a] > sz[b]; 
		});
	}
	dfs1(1);
	while(q--){
		int v, c;
		scanf("%d %d",&v,&c);
		while(v){
		    int ch = chn[v];
			int prv = dfn[ch] - 1;
			while(!stk[ch].empty() && stk[ch].back().first <= dfn[v]){
				auto val = stk[ch].back();
				stk[ch].pop_back();
				change_color(val.second, -(val.first - prv));
				prv = val.first;
			}
			if(!stk[ch].empty()){
				auto val = stk[ch].back();
				change_color(val.second, -(dfn[v] - prv));
			}
			change_color(c, dfn[v] - dfn[ch] + 1);
			stk[ch].emplace_back(dfn[v], c);
			v = par[ch];
		}
		int m;
		scanf("%d",&m);
		printf("%d\n", cnt[m] - (has[c] == m) + (has[c] == m + 1));
	}
}
