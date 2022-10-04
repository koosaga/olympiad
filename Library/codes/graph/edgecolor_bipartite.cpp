struct edge_color{ // must use 1-based
	int deg[2][MAXN];
	pi has[2][MAXN][MAXN];
	int color[MAXM];
	int c[2];
	void clear(int n){
		for(int t=0; t<2; t++){
			for(int i=0; i<=n; i++){
				deg[t][i] = 0;
				for(int j=0; j<=n; j++){
					has[t][i][j] = pi(0, 0);
				}
			}
		}
	}
	void dfs(int x, int p) {
		auto i = has[p][x][c[!p]];
		if (has[!p][i.first][c[p]].second) dfs(i.first,!p);
		else has[!p][i.first][c[!p]] = pi(0,0);
		has[p][x][c[p]] = i;
		has[!p][i.first][c[p]] = pi(x,i.second);
		color[i.second] = c[p];
	}
	int solve(vector<pi> v, vector<int> &cv){
		int m = sz(v);
		int ans = 0;
		for (int i=1;i<=m;i++) {
			int x[2];
			x[0] = v[i-1].first;
			x[1] = v[i-1].second;
			for (int d=0;d<2;d++) {
				deg[d][x[d]]+=1;
				ans = max(ans,deg[d][x[d]]);
				for (c[d]=1;has[d][x[d]][c[d]].second;c[d]++);
			}
			if (c[0]!=c[1]) dfs(x[1],1);
			for (int d=0;d<2;d++) has[d][x[d]][c[0]] = pi(x[!d],i);
			color[i] = c[0];
		}
		cv.resize(m);
		for(int i=1; i<=m; i++){
			cv[i-1] = color[i];
			color[i] = 0;
		}
		return ans;
	}
}EC;
