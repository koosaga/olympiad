#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
const lint inf = 1e10;

struct rect{
	lint sx, ex, sy, ey;
};

struct swp{
	lint s, e, x, y;
};

int w, h, n;
lint x[100005], y[100005], d[100005];
lint t[100005];

vector<lint> comp;
vector<swp> sweep;

bool cmp(swp a, swp b){
	return pi(a.x, -a.y) < pi(b.x, -b.y);
}

struct seg{
	int tree1[530000], tree2[530000];
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree2[p] += v;
			if(tree2[p]){
				tree1[p] = comp[pe+1] - comp[ps];
			}
			else{
				if(ps != pe) tree1[p] = tree1[2*p] + tree1[2*p+1];
				else tree1[p] = 0;
			}
			return;
		}
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		if(tree2[p] == 0){
			tree1[p] = tree1[2*p] + tree1[2*p+1];
		}
	}
}seg;

lint rect_union(vector<rect> &v){
	for(int i=0; i<v.size(); i++){
		comp.push_back(v[i].sy);
		comp.push_back(v[i].ey+1);
	}
	sort(comp.begin(), comp.end());
	comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
	for(int i=0; i<v.size(); i++){
		v[i].sy = lower_bound(comp.begin(), comp.end(), v[i].sy) - comp.begin();
		v[i].ey = lower_bound(comp.begin(), comp.end(), v[i].ey + 1) - comp.begin() - 1;
		sweep.push_back({v[i].sy, v[i].ey, v[i].sx, 1});
		sweep.push_back({v[i].sy, v[i].ey, v[i].ex+1, -1});
	}
	lint ret = 0;
	sort(sweep.begin(), sweep.end(), cmp);
	for(int i=0; i<sweep.size(); ){
		int e = i;
		while(e < sweep.size() && sweep[i].x == sweep[e].x) e++;
		for(int j=i; j<e; j++){
			seg.add(sweep[j].s, sweep[j].e, 0, comp.size()-2, 1, sweep[j].y);
		}
		if(e != sweep.size()){
			ret += (sweep[e].x - sweep[i].x) * seg.tree1[1];
		}
		i = e;
	}
	return ret;
}

struct cls{
	int p1, p2;
	lint t;
	bool operator<(const cls &a)const{
		return t < a.t;
	}
	bool operator>(const cls &a)const{
		return t > a.t;
	}
};

struct tup{
	lint piv, pos;
	int type, idx;
	bool operator<(const tup &a)const{
		return pi(piv, pos) < pi(a.piv, a.pos);
	}
};

typedef set<tup> ::iterator aauto;
set<tup> s[6];
priority_queue<cls, vector<cls>, greater<cls> > pq;

void process(int idx){
	if(s[idx].size() < 2) return;
	aauto it1 = s[idx].begin(), it2 = ++s[idx].begin();
	while(it2 != s[idx].end()){
		if(it1->type == 0 && it2->type == 1 && it1->piv == it2->piv){
			pq.push((cls){it1->idx, it2->idx, it2->pos - it1->pos});
		}
		it1++;
		it2++;
	}
}

void remove(tup x, int idx){
	s[idx].erase(x);
	aauto it = s[idx].lower_bound(x);
	if(it == s[idx].begin() || it == s[idx].end()) return;
	aauto bef = it;
	bef--;
	if(bef->type == 0 && it->type == 1 && bef->piv == it->piv){
		pq.push((cls){bef->idx, it->idx, it->pos - bef->pos});
	}
}

map<pi, int> mp;

int main(){
	vector<rect> trail;
	scanf("%d %d %d",&w,&h,&n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld",&x[i],&y[i],&d[i]);
		x[i] *= 2;
		y[i] *= 2;
		mp[pi(x[i], y[i])] = i;
		if(d[i] == 0 || d[i] == 1) s[0].insert((tup){x[i] - y[i], x[i] + y[i], d[i] != 0, i});
		if(d[i] == 0 || d[i] == 2) s[1].insert((tup){y[i], x[i], d[i] != 0, i});
		if(d[i] == 0 || d[i] == 3) s[2].insert((tup){x[i] + y[i], x[i] - y[i], d[i] != 0, i});
		if(d[i] == 1 || d[i] == 2) s[3].insert((tup){x[i] + y[i], x[i] - y[i], d[i] != 1, i});
		if(d[i] == 1 || d[i] == 3) s[4].insert((tup){x[i], y[i], d[i] != 3, i});
		if(d[i] == 2 || d[i] == 3) s[5].insert((tup){x[i] - y[i], x[i] + y[i], d[i] != 3, i});
	}
	for(int i=0; i<6; i++){
		process(i);
	}
	while(1){
		cls event;
		while(!pq.empty()){
			event = pq.top();
			pq.pop();
			if(t[event.p1] || t[event.p2]) continue;
			pq.push(event);
			break;
		}
		if(pq.empty()) break;
		lint min_time = (event.t + 1) / 2;
		int min_pos = event.p1;
		pi grnd = pi(x[min_pos] + min_time * dx[d[min_pos]], y[min_pos] + min_time * dy[d[min_pos]]);
		for(int i=0; i<4; i++){
			pi nxt = pi(grnd.first + min_time * dx[i], grnd.second + min_time * dy[i]);
			if(mp.find(nxt) != mp.end()){
				int i = mp[nxt];
				if(!t[i] && pi(x[i] + min_time * dx[d[i]], y[i] + min_time * dy[d[i]]) == grnd){
					t[i] = min_time;
					if(d[i] == 0 || d[i] == 1) remove((tup){x[i] - y[i], x[i] + y[i], d[i] != 0, i}, 0);
					if(d[i] == 0 || d[i] == 2) remove((tup){y[i], x[i], d[i] != 0, i}, 1);
					if(d[i] == 0 || d[i] == 3) remove((tup){x[i] + y[i], x[i] - y[i], d[i] != 0, i}, 2);
					if(d[i] == 1 || d[i] == 2) remove((tup){x[i] + y[i], x[i] - y[i], d[i] != 1, i}, 3);
					if(d[i] == 1 || d[i] == 3) remove((tup){x[i], y[i], d[i] != 3, i}, 4);
					if(d[i] == 2 || d[i] == 3) remove((tup){x[i] - y[i], x[i] + y[i], d[i] != 3, i}, 5);
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		x[i] /= 2;
		y[i] /= 2;
	 	t[i] = (t[i] + 1) / 2;
		if(!t[i]){
			if(d[i] == 0){
				trail.push_back({x[i], w, y[i], y[i]});
			}
			if(d[i] == 1){
				trail.push_back({x[i], x[i], 1, y[i]});
			}
			if(d[i] == 2){
				trail.push_back({1, x[i], y[i], y[i]});
			}
			if(d[i] == 3){
				trail.push_back({x[i], x[i], y[i], h});
			}
		}
		else{
			lint ex = x[i] + t[i] * dx[d[i]];
			lint ey = y[i] + t[i] * dy[d[i]];
			trail.push_back({ min(x[i], ex), max(x[i], ex), min(y[i], ey), max(y[i], ey)});
		}
	}
	printf("%lld",rect_union(trail));
}
