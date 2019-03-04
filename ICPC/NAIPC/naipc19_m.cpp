#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
const int mod = 1e9 + 7;

int n, m;
int a[MAXN], chk[MAXN];

bool cross(int l1, int r1, int l2, int r2){
	bool crs = 0;
	for(int i=l1; i<=r1; i++) chk[a[i]] = 1;
	for(int i=l2; i<=r2; i++) if(chk[a[i]]) crs = 1;
	for(int i=l1; i<=r1; i++) chk[a[i]] = 0;
	return crs;
}

lint solve(int l, int r){
	if(l == r) return 1;
	int m = (l + r) / 2;
	if(cross(l, m, m + 1, r)){
		bool bad = 0;
		for(int i=l; i<=m; i++){
			if(a[m + 1 - l + i] != a[i]) bad = 1;
		}
		return bad ? 0 : (solve(l, m) * 2) % mod;
	}
	return solve(l, m) * solve(m + 1, r) % mod;
}

int main(){
	scanf("%d %d",&m,&n);
	for(int i=(1<<m)-1; i>=0; i--) scanf("%d",&a[i]);
	cout << solve(0, (1<<m) - 1) << endl;
}
