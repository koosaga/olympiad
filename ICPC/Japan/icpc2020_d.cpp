#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 270000;

struct point{
	int x, y, c;
};

struct segcombine{
	struct node{
		int m1, m2, opt;
		node(){
			m1 = m2 = opt = 8e8;
		}
		node(int x, int y){
			m1 = x, m2 = y, opt = 8e8;
		}
		node operator+(const node &nd){
			node ret;
			ret.m1 = min(m1, nd.m1);
			ret.m2 = min(m2, nd.m2);
			ret.opt = min({opt, nd.opt, m1 + nd.m2});
			return ret;
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, node());
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, pi p){
		x += lim;
		tree[x] = node(p.first, p.second);
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node L, R;
		while(s < e){
			if(s%2 == 1) L = L + tree[s++];
			if(e%2 == 0) R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) L = L + tree[s];
		return L + R;
	}
}seg[2];

int n;
vector<pi> v;
pi ds[2][MAXT];

int solve(vector<point> p){
	seg[0].init(n);
	seg[1].init(n);
	fill(ds[0], ds[0] + MAXT, pi(8e8, 8e8));
	fill(ds[1], ds[1] + MAXT, pi(8e8, 8e8));
	for(int i = 0; i < n; i++){
		if(p[i].c == 1){
			ds[0][p[i].y] = pi(8e8, 2 * p[i].x);
			ds[1][p[i].y] = pi(8e8, 2 * p[i].x + 2 * v[p[i].y].first);
			seg[0].upd(p[i].y, ds[0][p[i].y]);
			seg[1].upd(p[i].y, ds[1][p[i].y]);
		}
	}
	int ret = 2e9;
	for(int i = 0; i < sz(p); ){
		int j = i;
		while(j < sz(p) && p[i].x == p[j].x) j++;
		for(int k = i; k < j; k++){
			if(p[k].c == 0){
				ds[0][p[k].y].first = -2*p[k].x-2*v[p[k].y].first;
				ds[1][p[k].y].first = -2*p[k].x;
				seg[0].upd(p[k].y, ds[0][p[k].y]);
				seg[1].upd(p[k].y, ds[1][p[k].y]);
			}
		}
		for(int k = i; k < j; k++){
			if(p[k].c == 2){
				// case 1
				auto q1 = seg[0].query(0, p[k].y - 1);
				auto q2 = seg[1].query(p[k].y + 1, n - 1);
				ret = min({ret, q1.m1 + q2.m2, q1.opt + 2*v[p[k].y].first, q2.opt - 2*v[p[k].y].first});
			}
		}
		for(int k = i; k < j; k++){
			if(p[k].c == 1){
				ds[0][p[k].y].second = 8e8;
				ds[1][p[k].y].second = 8e8;
				seg[0].upd(p[k].y, ds[0][p[k].y]);
				seg[1].upd(p[k].y, ds[1][p[k].y]);
			}
		}
		i = j;
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	vector<point> a(n);
	for(auto &i : a){
		scanf("%d %d %d",&i.x,&i.y,&i.c);
		v.push_back(pi(i.y, i.x));
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(auto &i : a){
		i.y = lower_bound(all(v), pi(i.y, i.x)) - v.begin();
	}
	int ret = 2e9;
	for(int i = 0; i < 2; i++){
		sort(all(a), [&](const point &p, const point &q){
			return pi(p.x, p.y) < pi(q.x, q.y);
		});
		vector<int> p = {0, 1, 2};
		do{
			vector<point> b = a;
			for(auto &i : b) i.c = p[i.c];
			ret = min(ret, solve(b));
		}while(next_permutation(all(p)));
		for(auto &i : a){
			i.x = -i.x;
		}
	}
	cout << ret << endl;
}
