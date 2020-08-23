#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 505;

int n, m;
int adj[MAXN][MAXN];

int main(){
	scanf("%d %d",&n,&m);
	memset(adj, 0x3f, sizeof(adj));
	for(int i=1; i<=n; i++) adj[i][i] = 0;
	for(int i=0; i<m; i++){
		int k, v; scanf("%d %d",&k,&v);
		for(int j=1; j<k; j++){
			int w; scanf("%d",&w);
			adj[v][w] = adj[w][v] = 1;
			v = w;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	for(int i=0; i<n; i++){
		vector<int> cnd(n); iota(all(cnd), 1);
		while(true){
			pi ret(1e9, 1e9);
			for(int j=1; j<=n; j++){
				int foo = 0;
				for(auto &k : cnd) foo += adj[j][k];
				ret = min(ret, pi(foo, j));
			}
			cout << ret.second << endl;
			string s; cin >> s;
			if(s == "FOUND") break;
			else{
				int w; cin >> w;
				vector<int> ncnd;
				for(auto &j : cnd){
					if(adj[j][ret.second] > adj[j][w]) ncnd.push_back(j);
				}
				cnd = ncnd;
			}
		}
	}
}
