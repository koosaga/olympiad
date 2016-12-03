#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
const int mod = 1e9 + 7;

char str[300005];
int n, m, s[300005], t[300005];
int cnt[1000005];
int dp[300005];
int p10 = 1;

int main(){
	cin >> n >> m >> (str + 1);
	s[0] = t[0] = 0;
	for(int i=1; i<=n; i++){
		p10 *= 10;
		p10 %= m;
		s[i] = s[i-1] * 10 + (str[i] - '0');
		s[i] %= m;
		t[i] = (1ll * s[i] * p10 % m);
	}
	cnt[0]++;
	dp[0] = 1;
	for(int i=1; i<=n; i++){
		dp[i] = cnt[s[i]];
		cnt[t[i]] += dp[i];
		cnt[t[i]] %= mod;
	}
	cout << dp[n];
}
