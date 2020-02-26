#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int MAXT = 530000;
const int mod = 1e9 + 7;

int n, k;
struct seg{
	struct node{
		int sum, pl;
	}tree[MAXT];
	void clear(){
		fill(tree, tree + MAXT, (node){0, 1});
	}
	void lazydown(int s, int e, int p){
		if(tree[p].pl == 1) return;
		for(int j=2*p; j<2*p+2; j++){
			tree[j].sum = 1ll * tree[j].sum * tree[p].pl % mod;
			tree[j].pl  = 1ll * tree[j].pl  * tree[p].pl % mod;
		}
		tree[p].pl = 1;
	}
	void init(int s, int e, int p, int *a){
		if(s == e){
			tree[p] = {a[s], 1};
			return;
		}
		tree[p].pl = 1;
		int m = (s+e)/2;
		init(s, m, 2*p, a);
		init(m+1, e, 2*p+1, a);
		tree[p].sum = (tree[2*p].sum + tree[2*p+1].sum) % mod;
	}
	void add(int pos, int v, int ps = 0, int pe = 2 * n + 2, int p = 1){
		if(ps == pe){
			tree[p].sum = v;
			tree[p].pl = 1;
			return;
		}
		lazydown(ps, pe, p);
		int pm = (ps+pe)/2;
		if(pos <= pm) add(pos, v, ps, pm, 2*p);
		else add(pos, v, pm+1, pe, 2*p+1);
		tree[p].sum = (tree[2*p].sum + tree[2*p+1].sum) % mod;
	}
	void prod(int s, int e, int v, int ps = 0, int pe = 2 * n + 2, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].sum = 1ll * v * tree[p].sum % mod;
			tree[p].pl = 1ll * v * tree[p].pl % mod;
			return;
		}
		lazydown(ps, pe, p);
		int pm = (ps+pe)/2;
		prod(s, e, v, ps, pm, 2*p);
		prod(s, e, v, pm+1, pe, 2*p+1);
		tree[p].sum = (tree[2*p].sum + tree[2*p+1].sum) % mod;
	}
	int query(int s, int e, int ps = 0, int pe = 2 * n + 2, int p = 1){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].sum;
		lazydown(ps, pe, p);
		int pm = (ps+pe)/2;
		return (query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1)) % mod;
	}
}seg;

lint dp[12][MAXN];
lint bino[11][11], pwr[MAXN], fact[11];

pi a[MAXN];

int main(){
	freopen("help.in", "r", stdin);
	freopen("help.out", "w", stdout);
	pwr[0] = 1;
	fact[0] = 1;
	for(int i=1; i<MAXN; i++) pwr[i] = pwr[i-1] * 2 % mod;
	bino[0][0] = 1;
	for(int i=0; i<11; i++){
		if(i) fact[i] = fact[i-1] * i % mod;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] * j + bino[i-1][j-1];
			bino[i][j] %= mod;
		}
	}
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a + 1, a + n + 1, [&](const pi &p, const pi &q){
		return p.second < q.second;
	});
	a[n+1] = pi(2*n+1, 2*n+2);
	dp[0][0] = 1;
	lint ret = 0;
	for(int i=1; i<=k+1; i++){
		seg.clear();
		for(int j=1; j<=n+1; j++){
			seg.add(a[j-1].second, dp[i-1][j-1]);
			dp[i][j] = seg.query(0, a[j].first - 1);
			seg.prod(0, a[j].first - 1, 2);
		}
		if(i > 1){
			lint func = bino[k][i-1] * fact[i-1] % mod;
			ret += func * dp[i][n+1] % mod;
			ret %= mod;
		}
	}
	cout << ret << endl;
}
