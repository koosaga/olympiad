#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 50005;
const int MAXT = 132000;

int n;
int a[MAXN], minv[MAXN], maxv[MAXN], f[MAXN];
int ia[MAXN], iminv[MAXN], imaxv[MAXN];
int ja[MAXN], jminv[MAXN], jmaxv[MAXN];
lint ret[MAXN], S;

struct node3{
	pi p[3];
	node3(){
		fill(p, p + 3, pi(2e9, 2e9));
	}
	node3 operator+(const node3 &n)const{
		int p1 = 0, p2 = 0;
		node3 ret;
		for(int i=0; i<3; i++){
			if(p[p1] < n.p[p2]) ret.p[i] = p[p1++];
			else ret.p[i] = n.p[p2++];
		}
		return ret;
	}
};

node3 make_node(set<pi> &s){
	node3 ret;
	auto itr = s.begin();
	for(int i=0; i<3 && itr != s.end(); i++, itr++){
		ret.p[i] = *itr;
	}
	return ret;
}

struct seg{
	node3 tree[MAXT];
	set<pi> val[MAXN];
	int lim;
	void init(int n){
		node3 p;
		for(int i=0; i<MAXT; i++) tree[i] = p;
		for(int i=0; i<MAXN; i++) val[i].clear();
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void ins(int x, pi v){
		val[x].insert(v);
		tree[x + lim] = make_node(val[x]);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	void del(int x, pi v){
		val[x].erase(v);
		tree[x + lim] = make_node(val[x]);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node3 query(int s, int e){
		s += lim;
		e += lim;
		node3 ret;
		while(s < e){
			if(s%2 == 1) ret = ret + tree[s++];
			if(e%2 == 0) ret = ret + tree[e--];
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = ret + tree[s];
		return ret;
	}
}seg;

namespace solve1{
	struct foo{
		int x, y, type, idx;
		bool operator<(const foo &f)const{
			return make_tuple(x, -y, type) < make_tuple(f.x, -f.y, f.type);
		}
	};
	void Do() {
		vector<int> crd;
		vector<lint> f1(n), f2(n);
		vector<foo> evt;
		for(int i = 1; i <= n - 2; i++){
			f1[i] = S - f[i] + imaxv[i] + iminv[i] - 2 * ia[i];
			f2[i] = - f[i] + jmaxv[i] + jminv[i] - 2 * ja[i];
			crd.push_back(jminv[i]);
			evt.push_back({ja[i], jminv[i], 0, i});
			evt.push_back({iminv[i], ia[i], 1, i});
		}
		sort(all(crd));
		crd.resize(unique(all(crd)) - crd.begin());
		sort(all(evt));
		seg.init(n);
		for(auto &i : evt){
			int loc = lower_bound(all(crd), i.y) - crd.begin();
			if(i.type == 0){
				seg.ins(loc, pi(f2[i.idx], i.idx));
			}
			else{
				auto qr = seg.query(loc, sz(crd) - 1);
				for(int j=0; j<3; j++){
					if(abs(i.idx - qr.p[j].second) == 1) continue;
					ret[i.idx] = min(ret[i.idx], f1[i.idx] + qr.p[j].first); 
					break;
				}
			}
		}
	}
}

namespace solve2{
	struct foo{
		int x, idx, type;
		int bar, baz;
		bool operator<(const foo &f)const{
			return pi(x, -abs(type)) < pi(f.x, -abs(f.type));
		}
	};
	void Do(){
		vector<lint> f1(n), f2(n);
		vector<int> crd;
		vector<foo> evt;
		for(int i = 1; i <= n - 2; i++) {
			f1[i] = S - f[i] + imaxv[i] + iminv[i];
			f2[i] = - f[i] - 2 * ja[i] + jmaxv[i] - jminv[i];
			evt.push_back({jminv[i], i, +1, ja[i], -1});
			evt.push_back({ia[i], i, 0, -int(1e9), iminv[i]});
			evt.push_back({jmaxv[i] + 1, i, -1, ja[i], -1});
			crd.push_back(ja[i]);
		}
		sort(all(crd));
		crd.resize(unique(all(crd)) - crd.begin());
		sort(all(evt));
		seg.init(n);
		for(auto &i : evt){
			if(i.type == +1){
				int loc = lower_bound(all(crd), i.bar) - crd.begin();
				seg.ins(loc, pi(f2[i.idx], i.idx));
			}
			else if(i.type == -1){
				int loc = lower_bound(all(crd), i.bar) - crd.begin();
				seg.del(loc, pi(f2[i.idx], i.idx));
			}
			else{
				int loc1 = lower_bound(all(crd), i.bar) - crd.begin();
				int loc2 = upper_bound(all(crd), i.baz) - crd.begin();
				auto qr = seg.query(loc1, loc2 - 1);
				for(int j=0; j<3; j++){
					if(abs(i.idx - qr.p[j].second) == 1) continue;
					ret[i.idx] = min(ret[i.idx], f1[i.idx] + qr.p[j].first); 
					break;
				}
			}
		}
	}
}

namespace solve3{
	struct foo{
		int x, idx, type;
		int bar, baz;
		bool operator<(const foo &f)const{
			return pi(x, -abs(type)) < pi(f.x, -abs(f.type));
		}
	};
	void Do(){
		vector<lint> f1(n), f2(n);
		vector<int> crd;
		vector<foo> evt;
		for(int i = 1; i <= n - 2; i++) {
			f1[i] = S - f[i] + imaxv[i] - iminv[i] + 2 * ia[i];
			f2[i] = - f[i] - jmaxv[i] - jminv[i];
			evt.push_back({jmaxv[i], i, +1, ja[i], -1});
			evt.push_back({ia[i], i, 0, iminv[i], imaxv[i]});
			crd.push_back(ja[i]);
		}
		sort(all(crd));
		crd.resize(unique(all(crd)) - crd.begin());
		sort(all(evt));
		seg.init(n);
		for(auto &i : evt){
			if(i.type == +1){
				int loc = lower_bound(all(crd), i.bar) - crd.begin();
				seg.ins(loc, pi(f2[i.idx], i.idx));
			}
			else{
				int loc1 = lower_bound(all(crd), i.bar) - crd.begin();
				int loc2 = upper_bound(all(crd), i.baz) - crd.begin();
				auto qr = seg.query(loc1, loc2 - 1);
				for(int j=0; j<3; j++){
					if(abs(i.idx - qr.p[j].second) == 1) continue;
					ret[i.idx] = min(ret[i.idx], f1[i.idx] + qr.p[j].first); 
					break;
				}
			}
		}
	}
}

namespace solve4{
	struct foo{
		int x, idx, type;
		int bar, baz;
		bool operator<(const foo &f)const{
			return pi(x, -abs(type)) < pi(f.x, -abs(f.type));
		}
	};
	void Do(){
		vector<lint> f1(n), f2(n);
		vector<int> crd;
		vector<foo> evt;
		for(int i = 1; i <= n - 2; i++) {
			f1[i] = S - f[i] + imaxv[i] - iminv[i];
			f2[i] = - f[i] + jmaxv[i] - jminv[i];
			evt.push_back({jminv[i], i, +1, ja[i], -1});
			evt.push_back({ia[i], i, 0, iminv[i], imaxv[i]});
			evt.push_back({jmaxv[i] + 1, i, -1, ja[i], -1});
			crd.push_back(ja[i]);
		}
		sort(all(crd));
		crd.resize(unique(all(crd)) - crd.begin());
		sort(all(evt));
		seg.init(n);
		for(auto &i : evt){
			if(i.type == +1){
				int loc = lower_bound(all(crd), i.bar) - crd.begin();
				seg.ins(loc, pi(f2[i.idx], i.idx));
			}
			else if(i.type == -1){
				int loc = lower_bound(all(crd), i.bar) - crd.begin();
				seg.del(loc, pi(f2[i.idx], i.idx));
			}
			else{
				int loc1 = lower_bound(all(crd), i.bar) - crd.begin();
				int loc2 = upper_bound(all(crd), i.baz) - crd.begin();
				auto qr = seg.query(loc1, loc2 - 1);
				for(int j=0; j<3; j++){
					if(abs(i.idx - qr.p[j].second) == 1) continue;
					ret[i.idx] = min(ret[i.idx], f1[i.idx] + qr.p[j].first); 
					break;
				}
			}
		}
	}
}

void solve_case1() {
	solve1::Do();
	for(int i = 0; i < n; i++) {
		ja[i] *= -1;
		iminv[i] *= -1;
		imaxv[i] *= -1;
		swap(iminv[i], imaxv[i]);
	}
	solve1::Do();
	for(int i = 0; i < n; i++) {
		ia[i] *= -1;
		jminv[i] *= -1;
		jmaxv[i] *= -1;
		swap(jmaxv[i], jminv[i]);
	}
	solve1::Do();
	for(int i = 0; i < n; i++) {
		ja[i] *= -1;
		iminv[i] *= -1;
		imaxv[i] *= -1;
		swap(iminv[i], imaxv[i]);
	}
	solve1::Do();
}

void solve_case2() {
	solve2::Do();
	for(int i = 0; i < n; i++) {
		ja[i] *= -1;
		iminv[i] *= -1;
		imaxv[i] *= -1;		
		swap(iminv[i], imaxv[i]);
	}
	solve2::Do();
}

void solve_case3() {
	solve3::Do();
	for(int i = 0; i < n; i++) {
		ia[i] *= -1;
		jminv[i] *= -1;
		jmaxv[i] *= -1;
		swap(jmaxv[i], jminv[i]);
	}
	solve3::Do();
}

void solve_case4() {
	solve4::Do();
}

lint do_swap(int x, int y) {
	lint ret = S;
	if(x > 0) ret -= abs(a[x] - a[x - 1]);
	if(x + 1 < n) ret -= abs(a[x + 1] - a[x]);
	if(y > 0) ret -= abs(a[y] - a[y - 1]);
	if(y + 1 < n) ret -= abs(a[y + 1] - a[y]);
	swap(a[x], a[y]);
	if(x > 0) ret += abs(a[x] - a[x - 1]);
	if(x + 1 < n) ret += abs(a[x + 1] - a[x]);
	if(y > 0) ret += abs(a[y] - a[y - 1]);
	if(y + 1 < n) ret += abs(a[y + 1] - a[y]);
	swap(a[x], a[y]);
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i < n; i++) S += abs(a[i] - a[i - 1]);
	for(int i = 0; i < n; i++) {
		ret[i] = S;
	}
	for(int i = 1; i < n - 1; i++) {
		minv[i] = min(a[i - 1], a[i + 1]);
		maxv[i] = max(a[i - 1], a[i + 1]);
		f[i] = abs(a[i + 1] - a[i]) + abs(a[i] - a[i - 1]);
	}
	if(n > 2) {
		for(int i = 0; i < n; i++) {
			ia[i] = ja[i] = a[i];
			iminv[i] = jminv[i] = minv[i];
			imaxv[i] = jmaxv[i] = maxv[i];
		}
		solve_case1();
		for(int i = 0; i < n; i++) {
			ia[i] = ja[i] = a[i];
			iminv[i] = jminv[i] = minv[i];
			imaxv[i] = jmaxv[i] = maxv[i];
		}
		solve_case2();
		for(int i = 0; i < n; i++) {
			ia[i] = ja[i] = a[i];
			iminv[i] = jminv[i] = minv[i];
			imaxv[i] = jmaxv[i] = maxv[i];
		}
		solve_case3();
		for(int i = 0; i < n; i++) {
			ia[i] = ja[i] = a[i];
			iminv[i] = jminv[i] = minv[i];
			imaxv[i] = jmaxv[i] = maxv[i];
		}
		solve_case4();
	}
	lint ns = do_swap(0, n - 1);
	ret[0] = min(ret[0], ns);
	ret[n - 1] = min(ret[n - 1], ns);
	for(int i = 1; i < n - 1; i++) {
		lint vv = do_swap(i, i - 1);
		ret[i-1] = min(ret[i-1], vv);
		ret[i] = min(ret[i], vv);
		lint v = do_swap(0, i);
		ret[0] = min(ret[0], v);
		ret[i] = min(ret[i], v);
		lint w = do_swap(n - 1, i);
		ret[n - 1] = min(ret[n - 1], w);
		ret[i] = min(ret[i], w);
	}
	for(int i = 0; i < n; i++) {
		printf("%lld\n", ret[i]);
	}

}
