#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, adj[105][105];
int dp[205][205];

int fight(int s, int e){
	if(e - s == 1) return 1;
	if(~dp[s][e]) return dp[s][e];
	for(int i=s+1; i<e; i++){
		if(fight(s, i) && fight(i, e) && (adj[s%n][i%n] || adj[e%n][i%n])){
			return dp[s][e] = 1;
		}
	}
	return dp[s][e] = 0;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			scanf("%1d",&adj[i][j]);
		}
	}
	memset(dp, -1, sizeof(dp));
	vector<int> v;
	for(int i=0; i<n; i++){
		bool ok = 0;
		for(int j=i+1; j<n+i; j++){
			if(fight(i, j) && fight(j, n+i) && adj[i][j%n]){
				ok = 1;
				break;
			}
		}
		if(ok) v.push_back(i+1);
	}
	cout << v.size() << endl;
	for(int i=0; i<v.size(); i++) printf("%d\n", v[i]);
}
