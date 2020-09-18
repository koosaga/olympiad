#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 250005;

int n;
vector<int> gph[MAXN];
vector<int> dfn;
char str[MAXN];
int par[MAXN], dp[MAXN], up[MAXN];

void dfs(int x, int p = -1){
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	scanf("%s", str + 1);
	for(int i=1; i<=n; i++) str[i] -= '0';
	int ans = min(2, (int)count(str + 1, str + n + 1, 1));
	dfs(1);
	reverse(all(dfn));
	for(auto &v : dfn){
		dp[v] = -str[v];
		for(auto &w : gph[v]){
			if(w != par[v]) dp[v] += dp[w];
		}
		dp[v] = max(dp[v], (int)str[v]);
	}
	reverse(all(dfn));
	for(auto &v : dfn){
		int kappa = -str[v];
		for(auto &w : gph[v]){
			if(w == par[v]){
				kappa += up[v];
			}
			else{
				kappa += dp[w];
			}
		}
		for(auto &w : gph[v]){
			if(w == par[v]) continue;
			up[w] = max((int)str[v], kappa - dp[w]);
		}
	}
	for(int i=1; i<=n; i++){
		int tmp = -str[i];
		for(auto &j : gph[i]){
			if(j == par[i]) tmp += up[i];
			else tmp += dp[j];
		}
		ans = max(ans, tmp);
	}
	cout << ans << endl;
}
