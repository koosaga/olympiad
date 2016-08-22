#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int wei, n;
int t[17], w[17];

int maxt[1<<16], wsum[1<<16];
int dp[1<<16];

int bktk(int cur, int bset, int pos){
	if(pos == n){
		if(wsum[cur] <= wei) return maxt[cur] + dp[bset^cur];
		return 1e9;
	}
	if((bset >> pos) & 1){
		return min(bktk(cur ^ (1<<pos), bset, pos+1), bktk(cur, bset, pos+1));
	}
	else return bktk(cur, bset, pos+1);
}

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
		dp[i] = bktk(0, i, 0);
	}
	cout << dp[(1<<n)-1];
}
