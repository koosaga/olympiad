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

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct seg{
	vector<pi> tree[270000];
	int lim;
	void init(int n, pi *a){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<270000; i++) tree[i].clear();
		for(int i=1; i<=n; i++){
			int p = lim + i;
			while(p){
				while(tree[p].size() >= 2 && ccw(tree[p][tree[p].size()-2], tree[p].back(), a[i]) >= 0){
					tree[p].pop_back();
				}
				tree[p].push_back(a[i]);
				p >>= 1;
			}
		}
	}
	bool f(vector<pi> &t, pi ts, pi te){
		int s = 0, e = t.size() - 1;
		while(s != e){
			int m = (s+e)/2;
			lint t1 = ccw(ts, te, t[m]);
			lint t2 = ccw(ts, te, t[m+1]);
			if(t1 < t2) s = m+1;
			else e = m;
		}
		return ccw(ts, te, t[s]) > 0;
	}
	int query(int s, int e, pi ps, pi pe){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1 && f(tree[s++], ps, pe)) return 1;
			if(e%2 == 0 && f(tree[e--], ps, pe)) return 1;
			s >>= 1;
			e >>= 1;
		}
		if(s == e && f(tree[s], ps, pe)) return 1;
		return 0;
	}
}seg;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d %d",&a[i].first, &a[i].second);
		}
		seg.init(n, a);
		for(int i=1; i<n; i++){
			if(!seg.query(i+2, n, a[i], a[i+1])){
				printf("0 ");
				continue;
			}
			int s = i+2, e = n;
			while(s != e){
				int m = (s+e)/2;
				if(seg.query(i+2, m, a[i], a[i+1])){
					e = m;
				}
				else s = m+1;
			}
			printf("%d ", s-1);
		}
		puts("");
	}
}