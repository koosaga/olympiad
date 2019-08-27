#include "walk.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 100005;
const int MAXV = 2000005;

struct intv{
	int s, e, x;
	bool operator<(const intv &i)const{
		return x < i.x;
	}
};

struct point{
	int x, y, idx;
};

int n, m;
vector<int> witness[MAXN];
vector<pi> event[MAXN];
vector<pi> gph[MAXV];
lint dist[MAXV];

lint dijkstra(int s, int e){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	pq.emplace(0, s);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.second] != x.first) continue;
		for(auto &j : gph[x.second]){
			if(dist[j.second] > x.first + j.first){
				dist[j.second] = x.first + j.first;
				pq.emplace(dist[j.second], j.second);
			}
		}
	}
	if(dist[e] > 1e17) return -1;
	return dist[e];
}

void add_edge(point x, point y){
	int dist = abs(x.x - y.x) + abs(x.y - y.y);
	gph[x.idx].emplace_back(dist, y.idx);
	gph[y.idx].emplace_back(dist, x.idx);
}

void make_vertex(vector<intv> v){
	for(auto &i : v){
		event[i.s].emplace_back(i.x, +1);
		event[i.e+1].emplace_back(i.x, -1);
	}
	multiset<int> swp;
	for(int i=0; i<n; i++){
		for(auto &j : event[i]){
			if(j.second == +1) swp.insert(j.first);
			else swp.erase(swp.find(j.first));
		}
		vector<int> nxt = witness[i];
		for(auto &j : witness[i]){
			if(j == 0) continue;
			auto l = swp.upper_bound(j);
			if(l != swp.end()) nxt.push_back(*l);
			l = swp.lower_bound(j);
			if(l != swp.begin()) nxt.push_back(*prev(l));
		}
		sort(nxt.begin(), nxt.end());
		nxt.resize(unique(nxt.begin(), nxt.end()) - nxt.begin());
		witness[i] = nxt;
	}
}

long long min_distance(vector<int> x, vector<int> h, vector<int> l, vector<int> r, vector<int> y, int s, int e) {
	n = sz(x);
	m = sz(l);
	for(int i=0; i<m; i++){
		witness[l[i]].push_back(y[i]);
		witness[r[i]].push_back(y[i]);
	}
	witness[s].push_back(0);
	witness[e].push_back(0);
	vector<pi> points;
	vector<intv> hors;
	set<int> alive;
	for(int i=0; i<n; i++){
		points.emplace_back(h[i], i);
		alive.insert(i);
	}
	for(int i=0; i<m; i++) hors.push_back({l[i], r[i], y[i]});
	sort(points.begin(), points.end());
	sort(hors.begin(), hors.end());
	int ptr = 0;
	for(auto &i : hors){
		while(ptr < sz(points) && points[ptr].first < i.x){
			alive.erase(points[ptr++].second);
		}
		if(i.s <= s && s <= i.e){
			auto it = alive.lower_bound(s);
			witness[*it].push_back(i.x);
			if(*it != s) witness[*prev(it)].push_back(i.x);
		}
		if(i.s <= e && e <= i.e){
			auto it = alive.lower_bound(e);
			witness[*it].push_back(i.x);
			if(*it != e) witness[*prev(it)].push_back(i.x);
		}
	}
	make_vertex(hors);
	vector<point> ans;
	for(int i=0; i<n; i++){
		for(auto &j : witness[i]){
			int num = ans.size();
			ans.push_back({x[i], j, num});
		}
	}
	auto cmpx = [&](const point &x, const point &y) { return pi(x.x, x.y) < pi(y.x, y.y); };
	auto cmpy = [&](const point &x, const point &y) { return pi(x.y, x.x) < pi(y.y, y.x); };
	sort(ans.begin(), ans.end(), cmpx);
	for(int i=0; i<n; i++){
		int st = lower_bound(ans.begin(), ans.end(), (point){x[i], 0, -1}, cmpx) - ans.begin();
		int ed = upper_bound(ans.begin(), ans.end(), (point){x[i], h[i], -1}, cmpx) - ans.begin();
		for(int j=st+1; j<ed; j++){
			add_edge(ans[j-1], ans[j]);
		}
	}
	sort(ans.begin(), ans.end(), cmpy);
	for(int i=0; i<m; i++){
		int st = lower_bound(ans.begin(), ans.end(), (point){x[l[i]], y[i], -1}, cmpy) - ans.begin();
		int ed = upper_bound(ans.begin(), ans.end(), (point){x[r[i]], y[i], -1}, cmpy) - ans.begin();
		for(int j=st+1; j<ed; j++){
			add_edge(ans[j-1], ans[j]);
		}
	}
	s = lower_bound(ans.begin(), ans.end(), (point){x[s], 0, -1}, cmpy)->idx;
	e = lower_bound(ans.begin(), ans.end(), (point){x[e], 0, -1}, cmpy)->idx;
	return dijkstra(s, e);
}
