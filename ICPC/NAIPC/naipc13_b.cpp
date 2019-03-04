#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
typedef vector<int> vi;

int x[100005], r[100005], n;
vector<int> vx, v;

struct intv{
	int s, e, x;
}a[100005];

int lv[100005], rv[100005];
int fuck[100005];

set<int> s;

struct seg{
	pi tree[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2*lim+2, pi(-2e9, -2e9));
	}
	void add(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(-2e9, -2e9);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

void dfs(int x, int val, int *r){
	s.insert(x);
	seg.add(fuck[a[x].x], pi(-2e9, -2e9));
	r[a[x].x] = val;
	int cent = (a[x].s + a[x].e) / 2;
	int cnt = upper_bound(v.begin(), v.end(), cent) - v.begin();
	while(1){
		pi p = seg.query(0, cnt-1);
		if(p.first >= cent){
			dfs(p.second, val, r);
		}
		else break;
	}
}

void solve(){
	for(int i=0; i<n; i++){
		a[i] = {x[i] - r[i], x[i] + r[i], i};	
	}
	for(int i=0; i<n; i++) v.push_back(a[i].s);
	sort(v.begin(), v.end());
	sort(a, a+n, [&](const intv &a, const intv &b){
		return a.s < b.s;
	});
	for(int i=0; i<n; i++){
		fuck[a[i].x] = i;
	}
	sort(a, a+n, [&](const intv &a, const intv &b){
		return a.e < b.e;
	});
	seg.init(n);
	for(int i=0; i<n; i++){
		seg.add(fuck[a[i].x], pi(a[i].e, i));
	}
	for(int i=n-1; i>=0; i--){
		if(s.find(i) == s.end()){
			dfs(i, a[i].e, rv);
		}
	}
	s.clear();
	sort(a, a+n, [&](const intv &a, const intv &b){
		return a.s < b.s;
	});
	seg.init(n);
	for(int i=0; i<n; i++){
		seg.add(fuck[a[i].x], pi(a[i].e, i));
	}
	for(int i=0; i<n; i++){
		if(s.find(i) == s.end()){
			dfs(i, a[i].s, lv);
		}
	}
	for(int i=0; i<n; i++){
		printf("%d",upper_bound(vx.begin(), vx.end(), rv[i])
		- lower_bound(vx.begin(), vx.end(), lv[i]));
		if(i != n-1) printf(" ");
	}
	s.clear();
	puts("");
}

int main(){
	while(1){
		scanf("%d",&n);
		if(n == 0) break;
		for(int i=0; i<n; i++){
			scanf("%d %d",&x[i], &r[i]);
			vx.push_back(x[i]);
		}
		sort(vx.begin(), vx.end());
		solve();
		v.clear();
		vx.clear();
	}
}