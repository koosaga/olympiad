#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int dp[100005], nxt[100005];
int n, v;

int main(){
	cin >> n >> v;
	for(int i=0; i<n; i++){
		int p, c;
		cin >> p >> c;
		memcpy(nxt, dp, sizeof(dp));
		for(int j=0; j<c; j++){
			int cst, val;
			cin >> cst >> val;
			for(int k=v; k>=cst; k--){
				nxt[k] = max(nxt[k], nxt[k - cst] + val);
			}
		}
		for(int i=p; i<=v; i++){
			dp[i] = max(dp[i], nxt[i-p]);
		}
	}
	cout << dp[v];
}

