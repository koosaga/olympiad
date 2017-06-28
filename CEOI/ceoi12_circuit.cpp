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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
  
int n;
pi a[100005];
vector<pi> v;
  
int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}
  
bool ccw(pi a, pi b){
	return 1ll * b.first * a.second > 1ll * a.first * b.second;
}
  
bool ccw2(pi a, pi b, pi c){
	return ccw(pi(b.first - a.first, b.second - a.second), pi(c.first - a.first, c.second - a.second));
}
  
bool same(pi a, pi b){
	return 1ll * b.first * a.second == 1ll * a.first * b.second;
}
  
struct line{
	int a, b;
	lint c;
};
  
double crs(line a, line b){
	return (1.0 * a.b * b.c - 1.0 * a.c * b.b) / (1.0 * a.a * b.b - 1.0 * a.b * b.a);
}
  
pi compare(pi p, pi q, int r1, int r2){
	if(p.first == -1) return q;
	if(q.first == -1) return p;
	r1 = max(r1, 0);
	r2 = min(r2, (int)v.size() - 1);
	line p1 = {a[p.second].second - a[p.first].second, a[p.first].first - a[p.second].first, 0ll};
	p1.c = - 1ll * p1.a * a[p.first].first - 1ll * p1.b * a[p.first].second;
	line p2 = {a[q.second].second - a[q.first].second, a[q.first].first - a[q.second].first, 0ll};
	p2.c = - 1ll * p2.a * a[q.first].first - 1ll * p2.b * a[q.first].second;
	line p3 = {v[r1].second + v[r2].second, -v[r1].first - v[r2].first, 0ll};
	if(crs(p1, p3) < crs(p2, p3)) return p;
	return q;
}

struct seg{
	int lim;
	pi tree[270000];
	int ps[270000], pe[270000];
	void init(int n){
		fill(tree, tree + 270000, pi(-1, -1));
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<lim; i++){
			ps[i + lim] = pe[i + lim] = i;
		}
		for(int i=lim-1; i; i--){
			ps[i] = ps[2*i];
			pe[i] = pe[2*i+1];
		}
	}
	void add(int s, int e, pi v){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1){
				tree[s] = compare(tree[s], v, ps[s], pe[s] + 1);
				s++;
			}
			if(e%2 == 0){
				tree[e] = compare(tree[e], v, ps[e], pe[e] + 1);
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s] = compare(tree[s], v, ps[s], pe[s] + 1);
	}
	pi query(int p){
		p += lim;
		pi ret = tree[p];
		while(p > 1){
			p >>= 1;
			ret = compare(ret, tree[p], ps[p], pe[p] + 1);
		}
		return ret;
	}
}seg;

pi queries[100005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		int g = gcd(a[i].first, a[i].second);
		v.push_back(pi(a[i].first / g, a[i].second / g));
	}
	a[n] = a[0];
	sort(v.begin(), v.end(), ccw);
	v.resize(unique(v.begin(), v.end()) - v.begin());
	seg.init(v.size() - 1);
	for(int i=0; i<n; i++){
		int s = lower_bound(v.begin(), v.end(), a[i], ccw) - v.begin();
		int e = lower_bound(v.begin(), v.end(), a[i+1], ccw) - v.begin();
		if(s == e) continue;
		pi val(i, (i+1)%n);
		if(s > e){
			swap(s, e);
			swap(val.first, val.second);
		}
		seg.add(s, e-1, val);
	}
	for(int i=0; i<v.size()-1; i++){
		queries[i] = query(i);
	}
	vector<int> v2;
	for(int i=0; i<n; i++){
		int p = lower_bound(v.begin(), v.end(), a[i], ccw) - v.begin();
		bool bad = 0;
		if(p != v.size()-1){
			pi t = queries[p];
			if(ccw2(a[t.second], a[t.first], a[i])){
				bad = 1;
			}
		}
		if(p != 0){
			pi t = queries[p-1];
			if(ccw2(a[t.second], a[t.first], a[i])){
				bad = 1;
			}
		}
		if(!bad) v2.push_back(i+1);
	}
	printf("%d\n",v2.size());
	for(auto &i : v2){
		printf("%d ",i);
	}
}