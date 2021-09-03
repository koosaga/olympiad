#include <bits/stdc++.h>
using namespace std;

string s1, s2;
int dp[3005][3005];
int nxt[3005][3005];
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

int track(int x, int y, int e, string &ans){ // use this routine to find LCS as string
	int ret = 0;
	while(y != 0 && x != e){
		if(nxt[x][y] == 1) y--;
		else if(nxt[x][y] == 2){
			if(s1[x] == s2[y]) ans.push_back(s1[x]);
			x--; y--;
		}
		else if(nxt[x][y] == 3) x--;
	}
	return ans.size();
}

void solve(string a){
	n = m = a.size();
	s1 = "#" + a;
	s2 = "#" + a;
	for(int i=0; i<=n; i++){
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
	int ret = 0;
	string tmp;
	for(int i=0; i<n; i++){	
		if(i) reroot(i);
		string dap;
		int foo = track(n, i, i, dap);
		if(ret < 2 * foo){
			ret = 2 * foo;
			tmp = dap;
		}
	}
	reverse(tmp.begin(), tmp.end());
	tmp = tmp + tmp;
    printf("%d\n", n-ret);
}

int main(){
		string s; cin >> s; cin >> s;
		solve(s);
}
