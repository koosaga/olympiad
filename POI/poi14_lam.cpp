#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

struct pnt{
	lint x, y;
	int idx, k;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[200005];

lint ccw(pi a, pi b){
	return a.first * b.second - b.first * a.second;
}

int n, ans[200005];
pi p1, p2;

struct bit{
	int tree[200005];
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

void solve(int s, int e, vector<pnt> &v){
	if(s == e){
		for(auto &i : v) ans[i.idx] = s;
		return;
	}
	int m = (s+e)/2;
	vector<pnt> l, r;
	for(auto &i : v){
		int c = bit.query(i.y);
		if(c >= i.k || i.idx <= m){
			bit.add(i.y, 1);
			l.push_back(i);
		}
		else{
			i.k -= c;
			r.push_back(i);
		}
	}
	for(auto &i : l) bit.add(i.y, -1);
	solve(s, m, l);
	solve(m+1, e, r);
}

int main(){
	scanf("%d",&n);
	scanf("%lld %lld %lld %lld",&p1.first,&p1.second,&p2.first,&p2.second);
	for(int i=1; i<=n; i++){
		scanf("%lld %lld",&a[i].x,&a[i].y);
		a[i].idx = i;
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i].k);
	}
	if(ccw(p1, p2) < 0) swap(p1, p2);
	if(ccw(p1, p2) == 0){
		vector<lint> vx;
		for(int i=1; i<=n; i++){
			lint nx = ccw(p1, pi(a[i].x, a[i].y));
			lint ny = p1.first * a[i].x + p1.second * a[i].y;
			a[i].x = nx;
			a[i].y = -ny;
		}
		sort(a+1, a+n+1);
		for(int i=1; i<=n; i++){
			a[i].y = -i;
		}
	}
	if(ccw(p1, p2) > 0){
		for(int i=1; i<=n; i++){
			lint nx = ccw(p1, pi(a[i].x, a[i].y));
			lint ny = -ccw(p2, pi(a[i].x, a[i].y));
			a[i].x = nx;
			a[i].y = ny;
		}
	}
	vector<lint> vx, vy;
	for(int i=1; i<=n; i++){
		vx.push_back(a[i].x);
		vy.push_back(a[i].y);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=1; i<=n; i++){
		a[i].x = lower_bound(vx.begin(), vx.end(), a[i].x) - vx.begin() + 1;
		a[i].y = lower_bound(vy.begin(), vy.end(), a[i].y) - vy.begin() + 1;
	}
	sort(a+1, a+n+1);
	vector<pnt> v;
	for(int i=1; i<=n; i++) v.push_back(a[i]);
	solve(1, n, v);
	for(int i=1; i<=n; i++) printf("%d ", ans[i]);
}
