#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXT = 1050000;

struct node{
	lint sum, l, r, opt;
	node() : sum(0), l(0), r(0), opt(0) {}
	node(lint x) : sum(x), l(max(0ll, x)), r(max(0ll, x)), opt(max(0ll, x)) {}
	node operator+(const node &nd)const{
		node ret;
		ret.sum = sum + nd.sum;
		ret.l = max(l, sum + nd.l);
		ret.r = max(nd.r, nd.sum + r);
		ret.opt = max({nd.opt, opt, nd.l + r});
		return ret;
	}
};

struct seg{
	node tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = node(v);
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
}seg;

struct event{
	int type;
	pi pos;
	int val;
};

int main(){
	int n, m, d;
	cin >> n >> m >> d;
	set<pi> s;
	vector<event> ev;
	auto Emp = [&](int x, int v){
		auto p = s.lower_bound(pi(x, v));
		if(p != s.begin() && p != s.end()){
			ev.push_back({0, *prev(p), 0});
		}
		if(p != s.begin()){
			ev.push_back({0, *prev(p), d - (x - prev(p)->first)});
		}
		if(p != s.end()){
			ev.push_back({0, pi(x, v), d - (p->first - x)});
		}
		s.emplace(x, v);
	};
	auto Query = [&](int p){
		ev.push_back({1, pi(-1, -1), p});
	};
	for(int i = 0; i < n; i++){
		int x; cin >> x;
		Emp(x, i);
	}
	for(int i = 0; i < m; i++){
		int x; cin >> x;
		Emp(x, i + n);
		Query(i);
	}
	vector<pi> crd;
	for(auto &x : ev){
		if(x.type != 1) crd.push_back(x.pos);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	seg.init(sz(crd));
	for(auto &x : ev){
		if(x.type == 0){
			int pos = lower_bound(all(crd), x.pos) - crd.begin();
			seg.upd(pos, x.val);
		}
		else{
			lint ans = seg.tree[1].opt;
			if(ans%2) cout << ans/2 << ".5 ";
			else cout << ans/2 << " ";
		}
	}
}
