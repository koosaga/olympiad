#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
using lint = long long;
using pi = pair<int, int>;

int n, m, s, t;
bool vis[MAXN];
bool in_path[MAXN];
vector<pi> gph[2][MAXN];

void dfs(int v){
	vis[v] = 1;
	for(auto &i : gph[1][v]){
		if(!vis[i.second]) dfs(i.second);
	}
}

int main(){
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=0; i<m; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		gph[0][s].emplace_back(x, e);
		gph[1][e].emplace_back(x, s);
	}
	dfs(t);
	if(!vis[s]){
		puts("IMPOSSIBLE");
		return 0;
	}
	vector<int> dap;
	vector<int> seq = {s};
	while(seq.back() != t && !in_path[seq.back()]){
		in_path[seq.back()] = 1;
		int v = seq.back();
		pi minv(1e9, 1e9);
		for(auto &i : gph[0][v]){
			if(!vis[i.second]) continue;
			minv = min(minv, i);
		}
		dap.push_back(minv.first);
		seq.push_back(minv.second);
	}
	if(seq.back() != t) puts("TOO LONG");
	else{
		for(auto &i : dap) printf("%d ", i);
	}
}
