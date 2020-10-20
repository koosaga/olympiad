// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;

struct seg{
	int tree[MAXN];
	void init(){
		fill(tree, tree + MAXN, -1e9);
	}
	void upd(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i) tree[i] = max(tree[i], v);
	}
	int query(int x){
		int ret = -1e9;
		for(int i=x; i; i-=i&-i) ret = max(ret, tree[i]);
		return ret;
	}
}seg[4];

int n, a[MAXN];
int dp[MAXN][4];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	vector<int> v(a, a + n + 1);
	sort(all(v));
	for(int i=1; i<=n; i++) a[i] = lower_bound(all(v), a[i]) - v.begin();
	for(int i=0; i<4; i++) seg[i].init();
	int ret = 0;
	for(int i=1; i<=n; i++){
		dp[i][0] = max(seg[0].query(n+1-a[i]), seg[3].query(n+1-a[i])) + 1;
		dp[i][1] = seg[0].query(n+1-a[i]) + 1;
		dp[i][2] = max(seg[1].query(a[i]), seg[2].query(a[i])) + 1;
		dp[i][3] = seg[2].query(a[i]) + 1;
		dp[i][1] = max(dp[i][1], 1);
		dp[i][3] = max(dp[i][3], 1);
		ret = max({ret, dp[i][1], dp[i][3]});
		seg[0].upd(n+1-a[i], dp[i][0]);
		seg[1].upd(a[i], dp[i][1]);
		seg[2].upd(a[i], dp[i][2]);
		seg[3].upd(n+1-a[i], dp[i][3]);
	}
	if(ret <= 1) ret = 0;
	cout << ret << endl;
}
