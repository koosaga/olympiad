#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int col[1005], bad;
vector<int> gph[1005];

void dfs(int x, int c){
	if(col[x]){
		if(col[x] != c) bad = 1;
		return;
	}
	col[x] = c;
	for(auto &i : gph[x]) dfs(i, 3-c);
}

int main(){
	int t;
	cin >> t;
	while(t--){
		for(int i=0; i<=1000; i++){
			col[i] = 0;
			gph[i].clear();
		}
		bad = 0;
		int n, m;
		cin >> n >> m;
		while(m--){int s, e; cin >> s >> e; gph[s].push_back(e); gph[e].push_back(s);}
		for(int i=1; i<=n; i++){
			if(!col[i]) dfs(i,1);
		}
		if(bad) puts("impossible");
		else puts("possible");
	}
}
