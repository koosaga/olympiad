#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

struct foo{
	int pos, cost;
	bool operator<(const foo &f)const{
		return pos < f.pos;
	}
}a[MAXN];

int n;
int dp[MAXN][MAXN][MAXN][2];

int f(int l, int r, int k, int p){
	if(k == 0) return 0;
	if(l <= 0 || r > n) return -1e9;
	if(~dp[l][r][k][p]) return dp[l][r][k][p];
	int cpos = (p ? a[l].pos : a[r].pos);
	int ccost = (p ? a[l].cost : a[r].cost);
	return dp[l][r][k][p] = max({
		f(l-1, r, k-1, 1) + ccost - (cpos - a[l-1].pos) * (k - 1),
		f(l, r+1, k-1, 0) + ccost - (a[r+1].pos - cpos) * (k - 1),
		f(l-1, r, k, 1) - (cpos - a[l-1].pos) * k,
		f(l, r+1, k, 0) - (a[r+1].pos - cpos) * k});
}

int main(){
	int t; scanf("%d",&t);
	while(t--){
		memset(dp, -1, sizeof(dp));
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&a[i].pos);
		for(int i=1; i<=n; i++) scanf("%d",&a[i].cost);
		a[n+1].pos = 0, a[n+1].cost = 0;
		n++; sort(a+1, a+n+1);
		int st = -1;
		for(int i=1; i<=n; i++) if(a[i].pos == 0) st = i;
		int ret = -1e9;
		for(int i=0; i<=n; i++) ret = max(ret, f(st, st, i, 0));
		cout << ret << endl;
	}
}
