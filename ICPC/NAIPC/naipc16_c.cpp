#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

lint prec[1<<15], dp[1<<15], prv[1<<15];
int n, k;
int w[15], h[15], q[15];

void bktk(int pos, int m1, int m2){
	if(pos == n){
		dp[m1 | m2] = min(dp[m1 | m2], prv[m1] + prec[m2]);
		return;
	}
	bktk(pos + 1, m1, m2);
	bktk(pos + 1, m1 | (1<<pos), m2);
	bktk(pos + 1, m1, m2 | (1<<pos));
}

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> w[i] >> h[i] >> q[i];
	for(int i=0; i<(1<<n); i++){
		int wm = 0, hm = 0;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				wm = max(wm, w[j]);
				hm = max(hm, h[j]);
			}
		}
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				prec[i] += 1ll * (wm * hm - w[j] * h[j]) * q[j];
			}
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for(int i=1; i<=k; i++){
		memcpy(prv, dp, sizeof(prv));
		memset(dp, 0x3f, sizeof(dp));
		bktk(0, 0, 0);
	}
	cout << dp[(1<<n)-1];
}
