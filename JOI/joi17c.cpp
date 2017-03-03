#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int n, m, a[2005][2005], mn = 1e9, mx = -1e9;

int a1[2005], a2[2005];

bool ok(int x){
	memset(a1, 0, sizeof(a1));
	memset(a2, 0x3f, sizeof(a2));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j] > mn + x){
				a1[i] = max(a1[i], j+1);
			}
			if(a[i][j] < mx - x){
				a2[i] = min(a2[i], j+1);
			}
		}
	}
	for(int i=n-1; i>=0; i--){
		a1[i] = max(a1[i], a1[i+1]);
	}
	for(int i=0; i<n; i++){
		if(i > 0) a2[i] = min(a2[i], a2[i-1]);
		if(a1[i] >= a2[i]) return 0;
	}
	return 1;
}

int solve(){
	int s = 0, e = 1e9;
	while(s != e){
		int m = (s+e)/2;
		if(ok(m)) e = m;
		else s = m+1;
	}
	return s;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d",&a[i][j]);
			mn = min(mn, a[i][j]);
			mx = max(mx, a[i][j]);
		}
	}
	int ans = solve();
	for(int i=0; i<n; i++) reverse(a[i], a[i] + m);
	ans = min(ans, solve());
	for(int i=0; i<m; i++){
		for(int j=0; j<n-1-j; j++){
			swap(a[j][i], a[n-1-j][i]);
		}
	}
	ans = min(ans, solve());
	for(int i=0; i<n; i++) reverse(a[i], a[i] + m);
	ans = min(ans, solve());
	cout << ans;
}
