#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n;
pi a[MAXN];

double dist(pi a, pi b){
	return hypot(b.first - a.first, b.second - a.second);
}

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pi sub(pi a, pi b){
	return pi(b.first - a.first, b.second - a.second);
}

bool cmp(pi a, pi b){
	bool flg1 = a < pi(0, 0);
	bool flg2 = b < pi(0, 0);
	if(flg1 != flg2) return flg1 < flg2;
	return ccw(pi(0, 0), a, b) > 0;
}

struct query1{
	pi l, r;
	int time;
	double val;
};

struct query2{
	int s, e;
	double val;
};

vector<query1> v;
vector<query2> w[MAXN];

struct seg{
	vector<double> tree;
	vector<double> lazy;
	void init(int n){
		tree.resize(4 * n + 4);
		lazy.resize(4 * n + 4);
	}
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, double v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
}seg;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	a[n] = a[0];
	set<int> s;
	for(int i=0; i<n; i++) s.insert(i);
	for(int i=0; i<n; i++){
		v.push_back({sub(a[i+1], a[i]), sub(a[i], a[i+1]), 0, +dist(a[i], a[i+1])});
	}
	int q;
	scanf("%d",&q);
	for(int i=1; i<=q; i++){
		int x;
		scanf("%d",&x);
		x--;
		int nxt = x;
		s.erase(x);
		auto l = s.upper_bound(x);
		if(l == s.end()) l = s.begin();
		int nxtr = *l;
		l = s.lower_bound(x);
		if(l == s.begin()) l = s.end();
		l--;
		int nxtl = *l;
		v.push_back({sub(a[nxtr], a[nxt]), sub(a[nxt], a[nxtr]), i, -dist(a[nxt], a[nxtr])});
		v.push_back({sub(a[nxt], a[nxtl]), sub(a[nxtl], a[nxt]), i, -dist(a[nxt], a[nxtl])});
		v.push_back({sub(a[nxtr], a[nxtl]), sub(a[nxtl], a[nxtr]), i, +dist(a[nxtr], a[nxtl])});
	}
	vector<pi> crd;
	crd.push_back(pi(0, -1)); // last guy
	for(auto &i : v){
		crd.push_back(i.l);
		crd.push_back(i.r);
	}
	sort(crd.begin(), crd.end(), cmp);
	crd.resize(unique(crd.begin(), crd.end(), [&](const pi &a, const pi &b){
		return !cmp(a, b) && !cmp(b, a);
	}) - crd.begin());
	int M = 2 * crd.size();
	for(auto &i : v){
		int idx1 = lower_bound(crd.begin(), crd.end(), i.l, cmp) - crd.begin() + 1;
		int idx2 = lower_bound(crd.begin(), crd.end(), i.r, cmp) - crd.begin() + 1;
		if(idx1 < idx2){
			w[i.time].push_back({2 * idx1 + 1, 2 * idx2 - 1, i.val});
		}
		else{
			w[i.time].push_back({2 * idx1 + 1, M, i.val});
			w[i.time].push_back({1, 2 * idx2 - 1, i.val});
		}
	}
	vector<double> arr(M + 1);
	seg.init(M);
	for(int i=0; i<=q; i++){
		for(auto &j : w[i]){
			seg.add(j.s, j.e, 1, M, 1, j.val);
		}
		printf("%.10f\n", seg.tree[1]);
	}
}
