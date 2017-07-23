#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

vector<int> gph[MAXN];
vector<int> ord;
int par[MAXN];

int n, v, a[MAXN];
lint adj[MAXN];
lint dp[MAXN][105]; 
lint lo[MAXN][105];

void dfs(int x, int p){
	ord.push_back(x);
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d %d",&n,&v);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
		adj[s] += a[e];
		adj[e] += a[s];
	}
	lint ans = 0;
	dfs(1, 0);
	reverse(ord.begin(), ord.end());
	for(auto &j : ord){
		lo[j][1] = adj[j];
		for(auto &k : gph[j]){
			if(k == par[j]) continue;
			for(int l=1; l<=v; l++){
				dp[j][l] = max({dp[j][l], dp[k][l], dp[k][l-1] + adj[j] - a[par[j]]});
				lo[j][l] = max({lo[j][l], lo[k][l], lo[k][l-1] + adj[j] - a[k]});
				ans = max(ans, dp[k][l-1] + adj[j]);
				ans = max(ans, lo[k][l-1] + adj[j] - a[k]);
			}
		}
		for(int l=0; l<=v; l++){
			int mx = 0, mxp = -1;
			int smx = 0, smxp = -1;
			for(auto &k : gph[j]){
				if(k == par[j]) continue;
				if(dp[k][l] > mx){
					smx = mx;
					smxp = mxp;
					mx = dp[k][l];
					mxp = k;
				}
				else if(dp[k][l] > smx){
					smx = dp[k][l];
					smxp = k;
				}
			}
			for(auto &k : gph[j]){
				if(k == par[j]) continue;
				if(k != mxp) ans = max(ans, mx + lo[k][v-l]);
				else ans = max(ans, smx + lo[k][v-l]);
			}
		}
		for(int l=1; l<=v; l++){
			int mxp = -1;
			lint mx = 0, smx = 0;
			for(auto &k : gph[j]){
				if(k == par[j]) continue;
				if(dp[k][l-1] > mx){
					smx = mx;
					mx = dp[k][l-1];
					mxp = k;
				}
				else if(dp[k][l-1] > smx){
					smx = dp[k][l-1];
				}
			}
			for(auto &k : gph[j]){
				if(k == par[j]) continue;
				if(k != mxp) ans = max(ans, mx + lo[k][v-l] + adj[j] - a[k]);
				else ans = max(ans, smx + lo[k][v-l] + adj[j] - a[k]);
			}
		}
	}
	cout << ans;
}
