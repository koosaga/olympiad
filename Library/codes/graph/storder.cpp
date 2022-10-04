namespace STOrder{
	int n;
	vector<pi> gph[MAXN];
	vector<pi> backedg[MAXN];
	int par[MAXN], ord[MAXN], stk[MAXN], piv;

	void dfs(int x, int p){
		stk[x] = 1;
		ord[x] = ++piv;
		for(auto &i : gph[x]){
			if(i.first == p) continue;
			if(!ord[i.second]){
				par[i.second] = x;
				dfs(i.second, i.first);
			}
			else if(stk[i.second]){
				backedg[ord[i.second]].emplace_back(x, i.second);
			}
		}
		stk[x] = 0;
	}

	void clear(){
		for(int i=1; i<=n; i++){
			gph[i].clear();
			backedg[i].clear();
			ord[i] = 0;
		}
		piv = 0;
	}
	vector<int> solve(int _n, int s, int t, vector<pi> E){
		n = _n;
		gph[s].emplace_back(sz(E), t);
		gph[t].emplace_back(sz(E), s);
		for(int i=0; i<sz(E); i++){
			gph[E[i].first].emplace_back(i, E[i].second);
			gph[E[i].second].emplace_back(i, E[i].first);
		}
		dfs(s, -1);
		if(piv != n) return {};
		vector<vector<int>> ears;
		vector<int> mark(n + 1);
		for(int i=1; i<=n; i++){
			for(auto &j : backedg[i]){
				vector<int> v = {j.second, j.first};
				for(int k=j.first; k!=j.second; k=par[k]){
					if(mark[k]) break;
					mark[k] = 1;
					v.push_back(par[k]);
				}
				ears.push_back(v);
			}
		}
		if(sz(ears) == 0 || ears[0].front() != ears[0].back()) return {};
		for(int i=1; i<sz(ears); i++){
			if(ears[i].front() == ears[i].back()) return {};
		}
		for(int i=1; i<=n; i++){
			if(i != s && !mark[i]) return {};
		}
		vector<int> dp(n + 1);
		vector<pi> intv(n + 1);
		for(int i=sz(ears)-1; i>=1; i--){
			for(int j=1; j+1<sz(ears[i]); j++){
				dp[ears[i][0]] += 1 + dp[ears[i][j]];
			}
		}
		for(int j=0; j+1<sz(ears[0]); j++){
			intv[ears[0][j]].second = intv[ears[0][j]].first + dp[ears[0][j]] + 1;
			if(j + 2 < sz(ears[0])) intv[ears[0][j+1]].first = intv[ears[0][j]].second;
		}
		for(int i=1; i<sz(ears); i++){
			if(intv[ears[i][0]] < intv[ears[i].back()]){
				pi curIntv = intv[ears[i][0]];
				for(int j=sz(ears[i])-2; j>=1; j--){
					intv[ears[i][j]] = pi(curIntv.second - dp[ears[i][j]] - 1, curIntv.second);
					curIntv.second -= dp[ears[i][j]] + 1;
				}
				intv[ears[i][0]] = curIntv;
			}
			else{
				pi curIntv = intv[ears[i][0]];
				for(int j=sz(ears[i])-2; j>=1; j--){
					intv[ears[i][j]] = pi(curIntv.first, curIntv.first + dp[ears[i][j]] + 1);
					curIntv.first += dp[ears[i][j]] + 1;
				}
				intv[ears[i][0]] = curIntv;
			}
		}
		vector<int> dap(n);
		for(int i=1; i<=n; i++){
			assert(intv[i].first + 1 == intv[i].second);
			dap[intv[i].first] = i;
		}
		return dap;
	}
}
