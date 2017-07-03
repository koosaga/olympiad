#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct sweep{
	int dx, dy, idx1, idx2;
	int mode(){
		return pi(dx, dy) < pi(0, 0);
	}
	bool operator<(const sweep &s)const{
		lint k = 1ll * dx * s.dy - 1ll * dy * s.dx;
		if(k != 0) return k > 0;
		return pi(idx1, idx2) < pi(s.idx1, s.idx2);
	}
};

lint ccw(sweep a, sweep b){
	return 1ll * a.dx * b.dy - 1ll * b.dx * a.dy;
}

struct point{
	int x, y, c;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[2005];

struct seg{
	struct node{
		lint sum, lsum, rsum, opt;
	}tree[4100];
	int lim;
	node make(int x){
		return (node){x, max(x, 0), max(x, 0), max(x, 0)}; 
	}
	node merge(node a, node b){
		node ans;
		ans.sum = a.sum + b.sum;
		ans.lsum = max(a.lsum, a.sum + b.lsum);
		ans.rsum = max(b.rsum, b.sum + a.rsum);
		ans.opt = max({a.opt, b.opt, a.rsum + b.lsum});
		return ans;
	}
	void init(int n, point *a){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int j=0; j<n; j++){
			tree[j + lim] = make(a[j].c);
		}
		for(int j=lim-1; j>=1; j--){
			tree[j] = merge(tree[2*j], tree[2*j+1]); 
		}
	}
	void update(int x, int v){
		x += lim;
		tree[x] = make(v);
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	lint query(){ return tree[1].opt; }
}seg;

int n, rev[2005];
vector<sweep> v;

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i].x >> a[i].y >> a[i].c;
	if(n == 1){
		cout << max(0, a[0].c);
		return 0;
	}
	sort(a, a+n);
	iota(rev, rev + n, 0);
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			v.push_back({a[j].x - a[i].x, a[j].y - a[i].y, i, j});
		}
	}
	sort(v.begin(), v.end());
	seg.init(n, a);
	lint ans = 0;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && ccw(v[i], v[e]) == 0) e++;
		for(int j=i; j<e; j++){
			int rx = rev[v[j].idx1], ry = rev[v[j].idx2];
			swap(rev[v[j].idx1], rev[v[j].idx2]);
			swap(a[rx], a[ry]);
			seg.update(rx, a[rx].c);
			seg.update(ry, a[ry].c);
		}
		ans = max(ans, seg.query());
		i = e;
	}
	cout << ans;
}
