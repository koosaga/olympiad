#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
const int MAXT = 1050000;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())

int dp[2];

int main(){
	int n;
	scanf("%d",&n);
	dp[1] = -2e9;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		if(x % 2){
			tie(dp[0], dp[1]) = make_pair(
			max(dp[0], dp[1] + x),
			max(dp[1], dp[0] + x));
		}
		else{
			dp[0] += x; dp[1] += x;
		}
	}
	if(dp[0] <= 0) cout << "NIESTETY" << endl;
	else cout << dp[0] << endl;
}
