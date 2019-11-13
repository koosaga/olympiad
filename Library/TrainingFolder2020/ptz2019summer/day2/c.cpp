#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)((v).size()))
const int MAXN = 13;
const int mod = 998244353;
int n, m, adj[MAXN][MAXN];
lint dp[1 << MAXN][MAXN];
lint prec[1 << MAXN][MAXN];
lint cact[1 << MAXN][MAXN][MAXN];
 
int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e;
		cin >> s >> e;
		adj[s-1][e-1] = adj[e-1][s-1] = 1;
	}
	for(int i=0; i<n; i++) dp[1 << i][i] = 1;
	for(int i=1; i<(1<<n); i++){
		vector<int> sub;
		vector<int> nie;
		for(int j=0; j<n; j++){
			if((i >> j) & 1) sub.push_back(j);
			else nie.push_back(j);
		}
		for(int v=0; v<sz(sub); v++){
			int submsk = i ^ (1 << sub[v]);
			int lsb = (submsk & -submsk);
			for(int msk = submsk; msk > 0; msk = (msk - 1) & submsk){
				if(msk & lsb){
					dp[i][sub[v]] += dp[i ^ msk][sub[v]] * prec[msk][sub[v]] % mod;
				}
			}
			dp[i][sub[v]] %= mod;
		}
		for(int v=0; v<sz(sub); v++){
			for(int w=0; w<sz(sub); w++){
				if(v == w){
					cact[i][sub[v]][sub[w]] = dp[i][sub[v]];
					continue;
				}
				for(int x=0; x<sz(sub); x++){
					if(adj[sub[v]][sub[x]] == 0) continue;
					int submsk = i & (~(1 << sub[x])) & (~(1 << sub[w]));
					for(int msk = submsk; msk > 0; msk = (msk - 1) & submsk){
						if((msk >> sub[v]) & 1){
							cact[i][sub[v]][sub[w]] += cact[i ^ msk][sub[x]][sub[w]] * dp[msk][sub[v]] % mod;
						}
					}
					cact[i][sub[v]][sub[w]] %= mod;
				}
			}
		}
		for(int v=0; v<sz(nie); v++){
			for(int w=0; w<sz(sub); w++){
				if(adj[nie[v]][sub[w]]){
					for(int x=w; x<sz(sub); x++){
						if(adj[nie[v]][sub[x]]){
							prec[i][nie[v]] += cact[i][sub[w]][sub[x]];
						}
					}
					prec[i][nie[v]] %= mod;
				}
			}
		}
	}
	cout << dp[(1 << n) - 1][0] << endl;
}