#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 10005;
const int mod = 1e9 + 7;

int n, l, q, a[MAXN];
int v[105], ans[105][MAXN];
int cnt[MAXN];

bool ok(int x){
	return x >= 0 && x + l - 1 < n;
}

int main(){
	cin >> n >> l;
	for(int i=0; i<n; i++) cin >> a[i];
	cin >> q;
	for(int i=0; i<q; i++){
		cin >> v[i];
		cnt[v[i]]++;
	}
	for(int i=n-1; i>=0; i--) cnt[i] += cnt[i+1];
	for(int i=-n+1; i<=n-1; i++){
		if(i == 0) continue;
		int dx[MAXN] = {};
		for(int j=0; j<n; j++){
			int x = j, y = j + i;
			if(min(x, y) < 0 || max(x, y) >= n || a[x] == a[y]) continue;
			int st = max({-i, 0, j-l+1});
			int ed = min({n-l, n-l-i, j});
			if(st <= ed){
				dx[st] += 1;
				dx[ed + 1] -= 1;
			}
		}
		for(int j=1; j<=n; j++) dx[j] += dx[j-1];
		for(int j=0; j<n; j++){
			if(ok(j) && ok(j + i)){
				int l = cnt[dx[j]];
				ans[l][j]++;
			}
		}
	}
	for(int i=q-1; i>=0; i--){
		for(int j=0; j<n; j++) ans[i][j] += ans[i+1][j];
	}
	for(int i=0; i<q; i++) {
		int w = cnt[v[i]];
		for(int j=0; j<n-l+1; j++) printf("%d ", ans[w][j]);
		puts("");
	}
}
