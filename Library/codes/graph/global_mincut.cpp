int minimum_cut_phase(int n, int &s, int &t, vector<vector<int>> &adj, vector<int> vis){
	vector<int> dist(n);
	int mincut = 1e9;
	while(true){
		int pos = -1, cur = -1e9;
		for(int i=0; i<n; i++){
			if(!vis[i] && dist[i] > cur){
				cur = dist[i];
				pos = i;
			}
		}
		if(pos == -1) break;
		s = t;
		t = pos;
		mincut = cur;
		vis[pos] = 1;
		for(int i=0; i<n; i++){
			if(!vis[i]) dist[i] += adj[pos][i];
		}
	}
	return mincut; // optimal s-t cut here is, {t} and V \ {t}
}
int solve(int n, vector<vector<int>> adj){
	if(n <= 1) return 0;
	vector<int> vis(n);
	int ans = 1e9;
	for(int i=0; i<n-1; i++){
		int s, t;
		ans = min(ans, minimum_cut_phase(n, s, t, adj, vis));
		vis[t] = 1;
		for(int j=0; j<n; j++){
			if(!vis[j]){
				adj[s][j] += adj[t][j];
				adj[j][s] += adj[j][t];
			}
		}
		adj[s][s] = 0;
	}
	return ans;
}
