#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
 
int n, cnt[2005];
char str[3][2005];
lint dp1[2005][4005], dp2[2005][4005];
 
int solve(int st, int ed){
	int n = 0, a[2005], s[2005];
	for(int i=st; i<=ed; i++){
		a[n] = cnt[i];
		s[n] = a[n] + (n ? s[n-1] : 0);
		n++;
	}
	memset(dp1[0], 0, sizeof(dp1[0]));
	memset(dp2[0], 0, sizeof(dp2[0]));
	if(a[0] == 1){
		dp1[0][1] = 1;
	}
	if(a[0] == 2){
		dp1[0][2] = 1;
		dp2[0][1] = 1;
	}
	if(a[0] == 3){
		dp1[0][3] = 2;
		dp2[0][2] = 2;
		dp2[0][1] = 2;
	}
	for(int i=1; i<n; i++){
		memset(dp1[i], 0, sizeof(dp1[i]));
		memset(dp2[i], 0, sizeof(dp2[i]));
		for(int j=1; j<=s[i]; j++){
			dp1[i-1][j] += dp1[i-1][j-1];
			dp2[i-1][j] += dp2[i-1][j-1];
			dp1[i-1][j] %= mod;
			dp2[i-1][j] %= mod;
		}
		for(int j=1; j<=s[i]; j++){
			if(a[i] == 1){
				dp1[i][j] = (dp1[i-1][s[i-1]] + dp2[i-1][s[i-1]] - dp2[i-1][j-1] + mod) % mod;
				dp2[i][j] = 0;
			}
			if(a[i] == 2){
				dp1[i][j] = dp1[i-1][s[i-1]] * (j-1);
				if(s[i-1] > max(j-2, 0)){
					dp1[i][j] += (dp2[i-1][s[i-1]] - (j >= 2 ? dp2[i-1][j-2] : 0) + mod) * (j-1);
				}
				dp1[i][j] %= mod;
				dp2[i][j] = dp1[i-1][j-1] * (s[i] - j) % mod;
			}
			if(a[i] == 3){
				dp1[i][j] += dp1[i-1][s[i-1]] * (j-1) * (j-2) % mod;
				if(s[i-1] > max(j-3, 0)){
					dp1[i][j] += (dp2[i-1][s[i-1]] - (j >= 3 ? dp2[i-1][j-3] : 0) + mod) * (j-1) * (j-2) % mod;
				}
				dp1[i][j] %= mod;
				dp2[i][j] = dp1[i-1][j-1] * (s[i] - j) * (s[i] - j - 1) % mod;
				if(j >= 2) dp2[i][j] += dp1[i-1][j-2] * 2 * (j-1) * (s[i] - j) % mod;
				dp2[i][j] %= mod;
			}
		}
	}
	lint ret = 0;
	for(int i=1; i<=s[n-1]; i++){
		ret += dp1[n-1][i] + dp2[n-1][i];
	}
	ret %= mod;
	return ret;
}
 
int bino[4005][4005];
 
int main(){
	cin >> n;
	for(int i=0; i<=4000; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j-1] + bino[i-1][j]) % mod;
		}
	}
	for(int i=0; i<3; i++){
		cin >> str[i];
	}
	if(str[0][0] == 'x' || str[2][0] == 'x' || str[0][n-1] == 'x' || str[2][n-1] == 'x'){
		puts("0");
		return 0;
	}
	for(int i=0; i<=2; i+=2){
		for(int j=1; j<n; j++){
			if(str[i][j-1] == 'x' && str[i][j] == 'x'){
				puts("0");
				return 0;
			}
		}
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<n; j++){
			if(str[i][j] == 'x') cnt[j]++;
		}
	}
	lint dap = 1;
	int cur = 0;
	for(int i=0; i<n; i++){
		if(cnt[i] == 0) continue;
		if(str[1][i] != 'x'){
			for(int j=0; j<cnt[i]; j++){
				cur++;
				dap *= cur;
				dap %= mod;
			}
			continue;
		}
		int e = i+1, blk = 0;
		while(e < n && str[1][e] == 'x') e++;
		for(int j=i; j<e; j++) blk += cnt[j];
		dap *= solve(i, e-1);
		dap %= mod;
		dap *= bino[cur + blk][blk];
		cur += blk;
		dap %= mod;
		i = e-1;
	}
	cout << dap << endl;
}