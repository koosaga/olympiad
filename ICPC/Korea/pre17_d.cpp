#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n, s, t, par[MAXN], chk[MAXN];
vector<int> gph[MAXN], ans;

void dfs(int x, int p){
	par[x] = p;
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
		}
	}
}

void dfs2(int x, int p, int d){
	if(!d) ans.push_back(x);
	for(auto &i : gph[x]){
		if(i != p && !chk[i]){
			dfs2(i, x, 1 - d);
		}
	}
	if(d) ans.push_back(x);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	scanf("%d %d",&s,&t);
	dfs(s, -1);
	for(int j=t; j!=-1; j=par[j]){
		chk[j] = 1;
	}
	for(int j=t; j!=-1; j=par[j]){
		dfs2(j, -1, j != t);
	}
	reverse(ans.begin(), ans.end());
	for(auto &i : ans) printf("%d\n", i);
}
