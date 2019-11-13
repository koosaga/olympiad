#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 4005;
const int MAXT = 8200;
const int inf = 1e8;

int n;
pi a[MAXN];
int dp[MAXN][MAXN]; // dp(how much, component)
int nest[MAXN];

struct seg{
	struct node{
		int addv, upv;
	}tree[MAXT];
	void apply(int x, int y, int z){
		tree[x].addv += y;
		tree[x].upv = max(tree[x].upv + y, z);
	}
	void init(){
		fill(tree, tree + MAXT, (node){0, -inf});
		tree[1]= {-inf, -inf};
	}
	void add(int s, int e, int ps = 1, int pe = MAXN, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			apply(p, 1, -inf);
			return;
		}
		int pm = (ps+pe)/2;
		apply(2 * p, tree[p].addv, tree[p].upv);
		apply(2 * p + 1, tree[p].addv, tree[p].upv);
		tree[p] = {0, -inf};
		add(s, e, ps, pm, 2*p);
		add(s, e, pm+1, pe, 2*p+1);
	}
	void upd(int s, int e, int v, int ps = 1, int pe = MAXN, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			apply(p, 0, v);
			return;
		}
		int pm = (ps+pe)/2;
		apply(2 * p, tree[p].addv, tree[p].upv);
		apply(2 * p + 1, tree[p].addv, tree[p].upv);
		tree[p] = {0, -inf};
		upd(s, e, v, ps, pm, 2*p);
		upd(s, e, v, pm+1, pe, 2*p+1);
	}
	int query(int x, int s = 1, int e = MAXN, int p = 1){
		if(s == e) return max(tree[p].addv, tree[p].upv);
		int m = (s+e)/2;
		apply(2 * p, tree[p].addv, tree[p].upv);
		apply(2 * p + 1, tree[p].addv, tree[p].upv);
		tree[p] = {0, -inf};
		if(x <= m) return query(x, s, m, 2*p);
		return query(x, m+1, e, 2*p+1);
	}
}seg;

int low[MAXN];

vector<int> solve(){
	for(int i=n; i; i--) a[i] = a[i-1]; // stupid))
	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			if(a[j].first >= a[i].first) nest[i]++;
			if(a[j].second < a[i].first) low[i] = j;
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			dp[i][j] = -1e9;
		}
	}
	dp[0][0] = 0;
	for(int i=1; i<=n; i++){
		int pmax[MAXN] = {};
		for(int j=0; j<=n; j++){
			pmax[j] = dp[i-1][j];
			if(j) pmax[j] = max(pmax[j], pmax[j-1]);
		}
		for(int j=1; j<=n; j++){
			dp[i][j] = pmax[low[j]] + nest[j] + 1;
		}
		seg.init();
		for(int j=1; j<=n; j++){
			dp[i][j] = max(dp[i][j], seg.query(a[j].first) + 1);
			seg.add(1, a[j].first); // a[i] += 1
			seg.upd(a[j].first, a[j].second, dp[i][j]); // max(a[i], v);
		}
	}
	vector<int> ans(n);
	for(int i=1; i<=n; i++){
		int ret = 0;
		for(int j=1; j<=n; j++) ret = max(ret, dp[i][j]);
		for(int j=0; j<ret; j++){
			ans[j] = max(ans[j], i);
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	vector<int> crd;
	crd.push_back(-1e9);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		crd.push_back(a[i].first);
		crd.push_back(a[i].second);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(all(crd), a[i].first) - crd.begin();
		a[i].second = lower_bound(all(crd), a[i].second) - crd.begin();
	}
	sort(a, a + n, [&](const pi &a, const pi &b){
		return pi(a.second, a.first) < pi(b.second, b.first);
	});
	auto ans = solve();
	for(int i=0; i<sz(ans); i++) ans[i] = min(ans[i], i + 1);
	reverse(ans.begin(), ans.end());
	for(auto &i : ans) printf("%d ", i);
}
