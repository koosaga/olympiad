#include "parks.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 400005;
const int mod = 1e9 + 7;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct point{
	int x, y, idx;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int construct_roads(std::vector<int> x, std::vector<int> y) {
	int n = sz(x);
	vector<point> p;
	vector<pi> edges;
	vector<pi> matches;
	vector<pi> to_mst;
	for(int i = 0; i < n; i++){
		p.push_back({x[i], y[i], i});
	}
	sort(all(p), [&](const point &a, const point &b){
		return pi(a.y, a.x) < pi(b.y, b.x);
	});
	for(int i = 1; i < sz(p); i++){
		if(p[i-1].y == p[i].y && p[i-1].x + 2 == p[i].x){
			to_mst.emplace_back(p[i-1].idx, p[i].idx);
		}
	}
	sort(all(p));
	for(int i = 1; i < sz(p); i++){
		if(p[i-1].x == p[i].x && p[i-1].y + 2 == p[i].y){
			to_mst.emplace_back(p[i-1].idx, p[i].idx);
		}
	}
	map<pi, int> mp;
	vector<int> U, V, A, B;
	sort(all(p), [&](const point &a, const point &b){
		return a.idx < b.idx;
	});
	for(auto &[x, y] : to_mst){
		set<pi> s;
		int mx = (p[x].x + p[y].x) / 2;
		int my = (p[x].y + p[y].y) / 2;
		for(int i = 0; i < 4; i++){
			s.emplace(mx + dx[i], my + dy[i]);
		}
		s.erase(pi(p[x].x, p[x].y));
		s.erase(pi(p[y].x, p[y].y));
		for(auto &p : s){
			if(mp.find(p) == mp.end()){
				int idx = sz(mp);
				mp[p] = idx;
			}
		}
	}
	sort(all(p));
	auto fnd = [&](int x, int y){
		auto ret = lower_bound(all(p), (point){x, y, -1});
		if(ret != p.end() && ret->x == x && ret->y == y) return ret->idx;
		return -1;
	};
	for(auto &[p, idx] : mp){
		int val = (p.first + p.second) % 4;
		int i1 = fnd(p.first - 1, p.second - 1);
		int i2 = fnd(p.first - 1, p.second + 1);
		int i3 = fnd(p.first + 1, p.second - 1);
		int i4 = fnd(p.first + 1, p.second + 1);
		if(val == 0){
			if(~i1 && ~i2){
				U.push_back(i1);
				V.push_back(i2);
				A.push_back(p.first);
				B.push_back(p.second);
			}
			else if(~i3 && ~i4){
				U.push_back(i3);
				V.push_back(i4);
				A.push_back(p.first);
				B.push_back(p.second);
			}
		}
		else{
			if(~i1 && ~i3){
				U.push_back(i1);
				V.push_back(i3);
				A.push_back(p.first);
				B.push_back(p.second);
			}
			else if(~i2 && ~i4){
				U.push_back(i2);
				V.push_back(i4);
				A.push_back(p.first);
				B.push_back(p.second);
			}
		}
	}
	disj.init(n);
	for(int i = 0; i < sz(U); i++){
		n -= disj.uni(U[i], V[i]);
	}
	if(n == 1){
		build(U, V, A, B);
		return 1;
	}
	return 0;
}
