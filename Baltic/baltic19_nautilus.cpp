#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;

int n, m, k;
bitset<MAXN> dp[MAXN], nxt[MAXN], grid[MAXN];
char str[MAXN][MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		for(int j=0; j<m; j++){
			if(str[i][j] == '.') grid[i].set(j);
		}
		dp[i] = grid[i];
	}
	string q; cin >> q;
	for(auto &i : q){
		for(int j=0; j<n; j++) nxt[j] = 0;
		if(i == 'W' || i == '?'){
			for(int j=0; j<n; j++) nxt[j] |= (dp[j] >> 1);
		}
		if(i == 'E' || i == '?'){
			for(int j=0; j<n; j++) nxt[j] |= (dp[j] << 1);
		}
		if(i == 'N' || i == '?'){
			for(int j=1; j<n; j++) nxt[j-1] |= dp[j];
		}
		if(i == 'S' || i == '?'){
			for(int j=1; j<n; j++) nxt[j] |= dp[j-1];
		}
		for(int j=0; j<n; j++) dp[j] = nxt[j] & grid[j];
	}
	int ret = 0;
	for(int j=0; j<n; j++) ret += dp[j].count();
	cout << ret << endl;
}

