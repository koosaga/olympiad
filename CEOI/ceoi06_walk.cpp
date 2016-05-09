#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int offset = 1e6;
const int lim = (1 << 21);

struct seg{
	pi tree[4200000];
	int piv;
	void set(int s, int e, int x){
		s += offset + lim;
		e += offset + lim;
		++piv;
		while(s < e){
			if(s%2 == 1){
				tree[s] = max(tree[s], pi(piv, x));
				s++;
			}
			if(e%2 == 0){
				tree[e] = max(tree[e], pi(piv, x));
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e){
			tree[s] = max(tree[s], pi(piv, x));
		}
	}
	int query(int pos){
		pos += offset + lim;
		pi ret(0, 0);
		while(pos){
			ret = max(ret, tree[pos]);
			pos >>= 1;
		}
		return ret.second;
	}
}seg;

int x, y, n;

struct rect{
	int sx, ex, sy, ey;
}a[100005];

vector<pi> pnt;
vector<int> gph[400050];
int dp[400050];

vector<pi> v;

bool ds(pi a, pi b, pi c){
	int ok1 = b.first == a.first;
	int ok2 = b.second == a.second;
	int ok3 = c.first == a.first;
	int ok4 = c.second == a.second;
	if(ok1 && ok3) return 1;
	if(ok2 && ok4) return 1;
	return 0;
}

int par[400005], dist[400005];

vector<pi> dijkstra(int s, int e){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	pq.push(pi(0, s));
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	while(!pq.empty()){
		auto t = pq.top();
		pq.pop();
		if(dist[t.second] < t.first) continue;
		for(auto &i : gph[t.second]){
			int cst = abs(pnt[t.second].first - pnt[i].first) + abs(pnt[t.second].second - pnt[i].second);
			if(dist[i] > t.first + cst){
				dist[i] = t.first + cst;
				par[i] = t.second;
				pq.push(pi(dist[i], i));
			}
		}
	}
	vector<pi> v;
	for(int j=e; j!=s; j=par[j]){
		v.push_back(pnt[j]);
		v.emplace_back(pnt[par[j]].first, pnt[j].second);
	}
	v.push_back(pnt[s]);
	reverse(v.begin(), v.end());
	printf("%d\n",dist[e]);
	auto u = v;
	v.clear();
	for(auto &i : u){
		while(v.size() >= 2 && ds(v[v.size()-2], v.back(), i)){
			v.pop_back();
		}
		v.push_back(i);
	}
	printf("%d\n",v.size()-1);
	for(int i=1; i<v.size(); i++){
		printf("%d %d\n", v[i].first - v[i-1].first, v[i].second - v[i-1].second);
	}
	return v;
}

int main(){
	scanf("%d %d %d",&x,&y,&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&a[i].sx, &a[i].sy, &a[i].ex, &a[i].ey);
		if(a[i].sx > a[i].ex) swap(a[i].sx, a[i].ex);
		if(a[i].sy > a[i].ey) swap(a[i].sy, a[i].ey);
		a[i].ex++, a[i].ey++;
		a[i].sx--, a[i].sy--;
	}
	a[n] = {0, 0, -offset, 0};
	a[n+1] = {0, 0, 0, offset};
	n += 2;
	sort(a, a+n, [&](const rect &a, const rect &b){
		return a.ex < b.ex;
	});
	for(int i=0; i<n; i++){
		pnt.emplace_back(a[i].sx, a[i].sy);
		pnt.emplace_back(a[i].sx, a[i].ey);
		pnt.emplace_back(a[i].ex, a[i].sy);
		pnt.emplace_back(a[i].ex, a[i].ey);
	}
	pnt.emplace_back(x, y);
	sort(pnt.begin(), pnt.end());
	pnt.resize(unique(pnt.begin(), pnt.end()) - pnt.begin());
	for(int i=0; i<n; i++){
		int p1 = lower_bound(pnt.begin(), pnt.end(), pi(a[i].sx, a[i].sy)) - pnt.begin();
		int p2 = lower_bound(pnt.begin(), pnt.end(), pi(a[i].sx, a[i].ey)) - pnt.begin();
		int p3 = lower_bound(pnt.begin(), pnt.end(), pi(a[i].ex, a[i].sy)) - pnt.begin();
		int p4 = lower_bound(pnt.begin(), pnt.end(), pi(a[i].ex, a[i].ey)) - pnt.begin();
		if(p4 != p2){
			gph[p2].push_back(p4);
		}
		if(p3 != p1){
			gph[p1].push_back(p3);
		}
	}
	int q = 0;
	for(int i=0; i<pnt.size(); i++){
		if(pnt[i].first <= 0) continue;
		while(q < n && a[q].ex <= pnt[i].first){
			seg.set(a[q].sy+1, a[q].ey-1, q);
			q++;
		}
		int p = seg.query(pnt[i].second);
		auto x = lower_bound(pnt.begin(), pnt.end(), pi(a[p].ex, a[p].sy)) - pnt.begin();
		auto y = lower_bound(pnt.begin(), pnt.end(), pi(a[p].ex, a[p].ey)) - pnt.begin();
		gph[x].push_back(i);
		gph[y].push_back(i);
	}
	int st = find(pnt.begin(), pnt.end(), pi(0, 0)) - pnt.begin();
	int ed = find(pnt.begin(), pnt.end(), pi(x, y)) - pnt.begin();
	dijkstra(st, ed);
}