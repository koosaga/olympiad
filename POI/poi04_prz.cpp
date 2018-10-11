#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int wei, n;
int t[17], w[17];

int maxt[1<<16], wsum[1<<16];
int dp[1<<16];

int main(){
	cin >> wei >> n;
	for(int i=0; i<n; i++){
		cin >> t[i] >> w[i];
	}
	for(int i=1; i<(1<<n); i++){
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				wsum[i] += w[j];
				maxt[i] = max(maxt[i], t[j]);
			}
		}
	}
	for(int i=1; i<(1<<n); i++){
		dp[i] = 1e9;
		for(int j=i; j; j=(j-1)&i){
			if(wsum[j] <= wei) dp[i] = min(dp[i], dp[i^j] + maxt[j]);
		}
	}
	cout << dp[(1<<n)-1];
}
