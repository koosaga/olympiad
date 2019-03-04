#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 250005;
const int MAXT = 1050000;

struct seg{
	lint tree[MAXT], lazy[MAXT];
	void init(int s, int e, int p){
		tree[p] = 1e18;
		lazy[p] = 0;
		if(s == e) return;
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
	}
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void upd(int pos, int s, int e, int p, lint v){
		if(s == e){
			tree[p] = v;
			return;
		}
		int m = (s+e)/2;
		lazydown(p);
		if(pos <= m) upd(pos, s, m, 2*p, v);
		else upd(pos, m+1, e, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	void dfs(int s, int e, int p, vector<lint> &dist){
		if(s == e){
			dist[s] = tree[p];
			return;
		}
		int m = (s+e)/2;
		lazydown(p);
		dfs(s, m, 2*p, dist);
		dfs(m+1, e, 2*p+1, dist);
	}
}seg1, seg2, seg3;

struct swp{
	int pos, l, r;
	lint update;
	bool operator<(const swp &s)const{
		return pos < s.pos;
	}
};

lint solve(int n, pi src, pi dst, vector<pi> p1, vector<pi> p2, vector<int> w){
	if(src > dst) swap(src, dst);
	vector<int> v = {src.second, dst.second};
	for(int i=0; i<n; i++){
		v.push_back(p1[i].second);
		v.push_back(p2[i].second);
	}
	sort(v.begin(), v.end());
	auto locate = [&](int x){ return lower_bound(v.begin(), v.end(), x) - v.begin(); };
	src.second = locate(src.second);
	dst.second = locate(dst.second);
	for(int i=0; i<n; i++){
		p1[i].second = locate(p1[i].second);
		p2[i].second = locate(p2[i].second);
	}
	vector<swp> event;
	for(int i=0; i<n; i++){
		if(p1[i].first < src.first) continue;
		if(p1[i].first < dst.first){
			event.push_back({p1[i].first, p1[i].second, p2[i].second, -1});
		}
		if(p2[i].first < dst.first){
			event.push_back({p2[i].first, p1[i].second, p2[i].second, 1ll * (p2[i].first - p1[i].first) * (w[i] - 10)});
		}
	}
	sort(event.begin(), event.end());
	seg1.init(0, v.size() - 1, 1);
	seg2.init(0, v.size() - 1, 1);
	seg3.init(0, v.size() - 1, 1);
	auto upload = [&](int pos, lint val){
		seg1.upd(pos, 0, v.size() - 1, 1, val);
		seg2.upd(pos, 0, v.size() - 1, 1, val - 10ll * v[pos]);
		seg3.upd(pos, 0, v.size() - 1, 1, val + 10ll * v[pos]);
	};
	upload(src.second, 0);
	lint ret = 1e18;
	for(auto &i : event){
		if(i.update == -1){
			lint lmin = seg3.query(i.l, i.r, 0, v.size() - 1, 1) - 10ll * v[i.l];
			lint rmin = seg2.query(i.l, i.r, 0, v.size() - 1, 1) + 10ll * v[i.r];
			upload(i.l, lmin);
			upload(i.r, rmin);
		}
		else{
			seg1.add(i.l + 1, i.r - 1, 0, v.size() - 1, 1, i.update);
			seg2.add(i.l + 1, i.r - 1, 0, v.size() - 1, 1, i.update);
			seg3.add(i.l + 1, i.r - 1, 0, v.size() - 1, 1, i.update);
		}
	}
	int leftest_good = 1e9;
	int rightest_good = -1;
	vector<lint> dist(v.size());
	seg1.dfs(0, v.size() - 1, 1, dist);
	for(int i=0; i<v.size(); i++){
		if(dist[i] < 1e12){
			leftest_good = min(leftest_good, i);
			rightest_good = max(rightest_good, i);
		}
	}
	if(leftest_good <= dst.second && dst.second <= rightest_good){
		for(int i=leftest_good; i<=rightest_good; i++){
			ret = min(ret, dist[i] + 10ll * abs(v[i] - v[dst.second]));
		}
	}
	return ret + 10ll * (dst.first - src.first);

}

lint shortest_path(pi src, pi dst, vector<pi> p1, vector<pi> p2, vector<int> w){
	int n = w.size();
	lint ret = solve(n, src, dst, p1, p2, w);
	swap(src.first, src.second);
	swap(dst.first, dst.second);
	for(int i=0; i<n; i++){
		swap(p1[i].first, p1[i].second);
		swap(p2[i].first, p2[i].second);
	}
	ret = min(ret, solve(n, src, dst, p1, p2, w));
	if(ret > 1e13) ret = 10ll * abs(src.first - dst.first) + 10ll * abs(src.second - dst.second);
	return ret;
}

int main(){
	int n; pi x, y;
	cin >> x.first >> x.second;
	cin >> y.first >> y.second;
	cin >> n;
	vector<pi> st(n);
	vector<pi> ed(n);
	vector<int> w(n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d %d",&st[i].first,&st[i].second,&ed[i].first,&ed[i].second,&w[i]);
	}
	printf("%lld\n", shortest_path(x, y, st, ed, w));
}


