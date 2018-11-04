#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a, b, d2[10005];
short dp[10005][10005];
char str[10005];

bool ok(int s, int e){
	int m = dp[s][e];
	return 2 * m * b >= a * (e-s+1);
}
int main(){
	cin >> n >> a >> b >> str;
	for(int i=1; i<n; i++){
		for(int j=0; j+i<n; j++){
			if(str[j] == str[j+i]) dp[j][j+i] = dp[j+1][j+i-1] + 1;
		}
	}
	for(int i=1; i<=n; i++){
		d2[i] = 1e9;
		for(int j=0; j<i; j++){
			if(ok(j, i-1)) d2[i] = min(d2[i], d2[j] + 1);
		}
	}
	if(d2[n] > 1e8) d2[n] = 0;
	cout << d2[n];
}
