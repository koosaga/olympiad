#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, lint> pi;

int n, adj[1005][1005], indeg[1005], outdeg[1005];

bool vis[1005], chk[1005];
vector<int> v;
void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	v.push_back(x);
	for(int j=1; j<=n; j++){
		if(adj[x][j]) dfs(j);
	}
}

int main(){
	int m;
	cin >> m;
	while(m--){
		int s, e;
		scanf("%d %d",&s,&e);
		chk[s] = chk[e] = 1;
		adj[s][e] = adj[e][s] = 1;
		outdeg[s]++;
		indeg[e]++;
	}
	n = 1000;
	int dap = 0;
	for(int i=1; i<=n; i++){
		if(chk[i] && !vis[i]){
			dfs(i);
			int ret = 0, tmp = 0;
			for(auto &i : v){
				ret += indeg[i];
				tmp += abs(indeg[i] - outdeg[i]);
			}
			tmp = max(tmp, 2);
			dap += ret + abs(tmp / 2 - 1) + 1;
			v.clear();
		}
	}
	cout << dap;
}
