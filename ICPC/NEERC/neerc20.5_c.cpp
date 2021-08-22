#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
using lint = long long;
 
vector<pi> ans;
vector<int> gph[MAXN];
vector<int> tr[MAXN];
int n, dfn[MAXN], low[MAXN], piv;
bool vis[MAXN];
 
int solve(int x, int p){
	vis[x] = 1;
	vector<int> mtch;
	for(auto &i : tr[x]){
		if(i == p) continue;
		mtch.push_back(solve(i, x));
	}
	if(sz(mtch) % 2){
		for(int i = 0; i < sz(mtch) / 2; i++) ans.emplace_back(mtch[2*i], mtch[2*i+1]);
		return mtch.back();
	}
	else{
		int wildcard = -10;
		for(int i = 0; i < sz(mtch); i++){
			if(binary_search(all(tr[x]), mtch[i])){
				wildcard = i;
			}
		}
		for(int i = 0; i < sz(mtch); i += 2){
			if(i / 2 != wildcard / 2){
				ans.emplace_back(mtch[i], mtch[i+1]);
			}
		}
		if(wildcard != -10) return mtch[wildcard ^ 1];
		else return x;
	}
}
 
void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!dfn[i]){
			dfs(i, x);
			low[x] = min(low[x], low[i]);
			if(low[i] > dfn[x]){
				tr[i].push_back(x);
				tr[x].push_back(i);
			}
		}
		else low[x] = min(low[x], dfn[i]);
	}
}
 
void solve(){
	int k;
	scanf("%d %d",&n,&k);
	if(n + k == 0){
		exit(0);
	}
	while(k--){
		int x, y; scanf("%d %d",&x,&y);
		for(int i=0; i<x-1; i++){
			int z; scanf("%d",&z);
			gph[y].push_back(z);
			gph[z].push_back(y);
			y = z;
		}
	}
	dfs(1, 0);
	for(int i = 0; i <= n; i++) sort(all(tr[i]));
	for(int i = 1; i <= n; i++){
		if(!vis[i] && sz(tr[i]) == 1){
			int val = solve(i, -1);
			if(val != tr[i][0]) ans.emplace_back(i, val);
		}
	}
    printf("%d\n", sz(ans));
	for(auto &[x, y] : ans) printf("%d %d\n", x, y);
	piv = 0;
	for(int i = 0; i <= n + 2; i++){
		gph[i].clear(); tr[i].clear();
		vis[i] = 0;
		dfn[i] = low[i] = 0;
	}
	ans.clear();
}
 
int main(){
	while(1){
		solve();
	}
}
