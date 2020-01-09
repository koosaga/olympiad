#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 30005;
const int MAXT = 66000;

struct point{
	int x, y, z;
}a[MAXN];

int n;

struct seg{
	struct node{
		int sx, sy, rx, ly, opt;
		node operator+(const node &n)const{
			node ret;
			ret.sx = sx + n.sx;
			ret.sy = sy + n.sy;
			ret.rx = max(n.rx, n.sx + rx);
			ret.ly = max(ly, sy + n.ly);
			ret.opt = max(opt + n.sy, sx + n.opt);
			return ret;
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, (node){0, 0, 0, 0, 0});
	}
	void upd(int x, int v){
		x += lim;
		if(v == 0) tree[x] = {1, 0, 1, 0, 1};
		if(v == 1) tree[x] = {0, 1, 0, 1, 1};
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
}seg;

int solve1(int *p){
	int cur_z = 0;
	for(int i=0; i<n; i++) cur_z += (a[i].z == p[2]);
	int ret = cur_z;
	seg.init(n);
	for(int i=0; i<n; i++){
		if(a[i].z == p[0]) seg.upd(a[i].y, 0);
		if(a[i].z == p[1]) seg.upd(a[i].y, 1);
		if(a[i].z == p[2]) cur_z--;
		ret = max(ret, cur_z + seg.tree[1].opt);
	}
	return ret;
}

int dp[MAXN][3];

int solve2(int *p){
	memset(dp, 0, sizeof(dp));
	for(int i=0; i<n; i++){
		int cur = 0;
		for(int j=0; j<3; j++){
			cur = max(cur, dp[i][j]);
			dp[i + 1][j] = cur;
		}
		dp[i + 1][p[a[i].z]]++;
	}
	return *max_element(dp[n], dp[n] + 3);
}

void solve(){
	{
		vector<int> vx, vy;
		int f, b, c;
		scanf("%d %d %d",&f,&b,&c);
		n = f + b + c;
		for(int i=0; i<n; i++){
			scanf("%d %d",&a[i].x,&a[i].y);
			a[i].z = (i >= f) + (i >= f + b);
			vx.push_back(a[i].x);
			vy.push_back(a[i].y);
		}
		sort(all(vx));
		vx.resize(unique(all(vx)) - vx.begin());
		sort(all(vy));
		vy.resize(unique(all(vy)) - vy.begin());
		for(int i=0; i<n; i++){
			a[i].x = lower_bound(all(vx), a[i].x) - vx.begin();
			a[i].y = lower_bound(all(vy), a[i].y) - vy.begin();
		}
	}
	int ans = 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			int p[3] = {0, 1, 2};
			sort(a, a + n, [&](const point &x, const point &y){
				return x.x < y.x;
			});
			do{
				ans = max({ans, solve1(p), solve2(p)});
			}while(next_permutation(p, p + 3));
			for(int k=0; k<n; k++) a[k].x = n - 1 - a[k].x;
		}
		for(int k=0; k<n; k++) swap(a[k].x, a[k].y);
	}
	cout << ans << endl;
}

int main(){
	int t; cin >> t;
	while(t--) solve();
}
