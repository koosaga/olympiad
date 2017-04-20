#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
bool con[605][605];
int adj[605][605];

int main(){
	int m1, m2;
	memset(adj, 0x3f, sizeof(adj));
	scanf("%d %d %d",&n,&m1,&m2);
	for(int i=0; i<m1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		adj[s][e] = min(adj[s][e], 1);
		adj[e][s] = min(adj[e][s], -1);
		con[s][e] = con[e][s] = 1;
	}
	for(int i=0; i<m2; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		adj[e][s] = min(adj[e][s], 0);
		con[e][s] = 1;
	}
	for(int i=1; i<=n; i++) adj[i][i] = 0, con[i][i] = 1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
				con[j][k] |= (con[j][i] & con[i][k]);
			}
		}
	}
	int ret = 0, vis[666] = {};
	for(int i=1; i<=n; i++){
		if(adj[i][i] < 0){
			puts("NIE");
			return 0;
		}
		if(!vis[i]){
			vector<int> v;
			for(int j=1; j<=n; j++){
				if(con[i][j] && con[j][i]){
					vis[j] = 1;
					v.push_back(j);
				}
			}
			int ans = -1e9;
			for(auto &i : v){
				for(auto &j : v){
					ans = max(ans, adj[i][j]);
				}
			}
			ret += ans + 1;
		}
	}
	cout << ret << endl;
}

