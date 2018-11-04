#include <bits/stdc++.h>
using namespace std;

int adj[105][105];
int dp[105][105];

int f(int s, int e){
	if(~dp[s][e]) return dp[s][e];
	if(s > e) return 0;
	int ret = 0;
	if(adj[s][e]){
		ret = max(ret, 1 + f(s + 1, e - 1));
	}
	for(int i=s; i<e; i++){
		ret = max(ret, f(s, i) + f(i + 1, e));
	}
	return dp[s][e] = ret;
}

int main(){
	int n; cin >> n;
	for(int i=0; i<n;i++){
		int s, e; cin >> s >> e;
		if(s > e) swap(s, e);
		adj[s][e] = 1;
	}
	memset(dp, -1, sizeof(dp));
	cout << f(1, 100) << endl;
}
