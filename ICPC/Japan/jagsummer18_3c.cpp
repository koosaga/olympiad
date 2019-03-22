#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;

int c, n, q;
int dp[MAXN];

int main(){
	cin >> c >> n >> q;
	while(n--){
		int x, y; cin >> x >> y;
		for(int i=MAXN-1; i>=x; i--){
			dp[i] = max(dp[i], dp[i-x] + y);
		}
	}
	for(int i=1; i<=q; i++){
		printf("%lld\n",1ll*dp[c/i]*i);
	}
}
