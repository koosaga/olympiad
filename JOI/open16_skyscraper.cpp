#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, l, a[105], d[105];
int dp[105][105][1005][3];

lint f(int x, int c, int k, int l){
	if(k < 0) return 0;
	if(x == n-1){
		if(c == 2) return l == 2;
		if(c == 1) return l == 1;
		return 0;
	}
	if(~dp[x][c][k][l]) return dp[x][c][k][l];
	lint ret = 0;
	if(l < 2){
		ret += f(x+1, c+1, k - (2*(c+1) - l - 1) * d[x], l+1) * (2 - l);
		if(2*c - l - 1 > 0) ret += f(x+1, c, k - (2*c - l - 1) * d[x], l+1) * (2 - l);
	}
	if(c-1+2-l > 0) ret += f(x+1, c+1, k - (2*(c+1) - l) * d[x], l) * (c-1+2-l);
	if(c > 0) ret += f(x+1, c-1, k - (2*(c-1) - l) * d[x], l) * (c-1);
	if(2*c - l > 0) ret += f(x+1, c, k - (2*c - l) * d[x], l) * (2 * c - l);
	ret %= mod;
	return dp[x][c][k][l] = ret;
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> l;
	for(int i=0; i<n; i++){
		cin >> a[i];
	}
	if(n == 1){
		cout << 1;
		return 0;
	}
	sort(a, a+n);
	for(int i=0; i<n-1; i++){
		d[i] = a[i+1] - a[i];
	}
	cout << f(0, 0, l, 0);
}

