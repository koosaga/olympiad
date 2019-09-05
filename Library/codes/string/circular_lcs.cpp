string s1, s2;
int dp[4005][2005];
int nxt[4005][2005];
int n, m;
void reroot(int px){
	int py = 1;
	while(py <= m && nxt[px][py] != 2) py++;
	nxt[px][py] = 1;
	while(px < 2 * n && py < m){
		if(nxt[px+1][py] == 3){
			px++;
			nxt[px][py] = 1;
		}
		else if(nxt[px+1][py+1] == 2){
			px++;
			py++;
			nxt[px][py] = 1;
		}
		else py++;
	}
	while(px < 2 * n && nxt[px+1][py] == 3){
		px++;
		nxt[px][py] = 1;
	}
}

int track(int x, int y, int e){ // use this routine to find LCS as string
	int ret = 0;
	while(y != 0 && x != e){
		if(nxt[x][y] == 1) y--;
		else if(nxt[x][y] == 2) ret += (s1[x] == s2[y]), x--, y--;
		else if(nxt[x][y] == 3) x--;
	}
	return ret;
}

int solve(string a, string b){
	n = a.size(), m = b.size();
	s1 = "#" + a + a;
	s1 = '#' + b;
	for(int i=0; i<=2*n; i++){
		for(int j=0; j<=m; j++){
			if(j == 0){
				nxt[i][j] = 3;
				continue;
			}
			if(i == 0){
				nxt[i][j] = 1;
				continue;
			}
			dp[i][j] = -1;
			if(dp[i][j] < dp[i][j-1]){
				dp[i][j] = dp[i][j-1];
				nxt[i][j] = 1;
			}
			if(dp[i][j] < dp[i-1][j-1] + (s1[i] == s2[j])){
				dp[i][j] = dp[i-1][j-1] + (s1[i] == s2[j]);
				nxt[i][j] = 2;
			}
			if(dp[i][j] < dp[i-1][j]){
				dp[i][j] = dp[i-1][j];
				nxt[i][j] = 3;
			}
		}
	}
	int ret = dp[n][m];
	for(int i=1; i<n; i++){
		reroot(i), ret = max(ret, track(n+i, m, i));
	}
	return ret;
}