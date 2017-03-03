#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int inf = 36501;

vector<int> gph[1000005], rev[1000005];
vector<int> dfn;
int head[1000005], ccnt[1000005];
int vis[1000005], comp[1000005], piv;

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]) dfs(i);
	dfn.push_back(x);
}

void rdfs(int x, int p){
	if(comp[x]) return;
	comp[x] = p;
	head[p] = x;
	ccnt[p]++;
	for(auto &i : rev[x]) rdfs(i, p);
}

int n, m, dp[1000005], chk[1000005];

void ddfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : rev[x]) ddfs(i);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s == e) chk[s] = 1;
		else{
			gph[s].push_back(e);
			rev[e].push_back(s);
		}
	}
	n++;
	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i);
	}
	reverse(dfn.begin(), dfn.end());
	for(auto &i : dfn){
		if(!comp[i]) rdfs(i, ++piv);
	}
	memset(vis, 0, sizeof(vis));
	ddfs(n);
	dp[comp[n]] = 1;
	int ans = 0;
	for(int i=comp[n]; i; i--){
		if(!vis[head[i]]) continue;
		if(ccnt[i] > 1 || chk[head[i]]) dp[i] = inf;
		else{
			for(auto &j : gph[head[i]]){
				dp[i] += dp[comp[j]];
				dp[i] = min(dp[i], inf);
			}
		}
		ans = max(ans, dp[i]);
	}
	if(ans == inf) puts("zawsze");
	else printf("%d\n", ans);
	vector<int> v;
	for(int i=1; i<n; i++){
		if(dp[comp[i]] == ans) v.push_back(i);
	}
	printf("%d\n", v.size());
	for(auto &i : v) printf("%d ", i);
}

