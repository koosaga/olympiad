#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, m, a[37];
int adj[37][37];
int nadj[37][37];
bool vis[37];

int dfs(int x){
	if(x == 2){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(adj[i][j] == 1) nadj[i][j] = (vis[i] ? a[i] : 0) + (vis[j] ? a[j] : 0);
				else nadj[i][j] = 1e9;
			}
		}
		int dist[37], vis[37] = {};
		fill(dist, dist + 37, 1e9);
		dist[1] = 0;
		for(int i=1; i<=n; i++){
			int key = 2e9, pos = -1;
			for(int j=1; j<=n; j++){
				if(!vis[j] && dist[j] < key){
					key = dist[j];
					pos = j;
				}
			}
			vis[pos] = 1;
			for(int j=1; j<=n; j++){
				dist[j] = min(dist[j], dist[pos] + nadj[pos][j]);
			}
		}
		return -dist[2] / 2;
	}
	int ret = -1e9;
	for(int i=1; i<=n; i++){
		if(adj[x][i] == 1 && adj[i][2] == adj[x][2] - 1){
			vis[i] = 1;
			ret = max(ret, dfs(i) + a[x]);
			vis[i] = 0;
		}
	}
	return ret;
}

void Do(){
	cin >> n >> m;
	if(n + m == 0) exit(0);
	for(int i=3; i<=n; i++){
		cin >> a[i];
	}
	memset(adj, 0x3f, sizeof(adj));
	for(int i=1; i<=n; i++) adj[i][i] = 0;
	for(int i=0; i<m; i++){
		int s, e; cin >> s >> e;
		adj[s][e] = adj[e][s] = 1;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	cout << dfs(1) << endl;
}

int main(){
	while(1) Do();
}
