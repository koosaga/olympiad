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
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
  
int n, d;
pi a[100005];
  
struct disj{
	int par[100005], sz[100005];
	void init(int n){
		for(int i=0; i<=n; i++){
			par[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x){
		return par[x] = (par[x] == x ? x : find(par[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		par[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;
  
struct rmq{
	pi tree[270000];
	int lim;
	void init(int n){
		fill(tree, tree + 270000, pi(-1e9, -1e9));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, pi v){
		x += lim;
		while(x){
			tree[x] = max(tree[x], v);
			x >>= 1;
		}
	}
	pi q(int s, int e){
		pi ret(-1e9,-1e9);
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) ret = max(ret,tree[s++]);
			if(e%2 == 0) ret = max(ret,tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret,tree[s]);
		return ret;
	}
}rmq;
  
vector<int> vx, vy;
  
int main(){
	scanf("%d %d",&n,&d);
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[i] = pi(x+y, x-y);
		vx.push_back(x+y);
		vy.push_back(x-y);
	}
	sort(vx.begin(), vx.end());
	sort(vy.begin(), vy.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(vx.begin(), vx.end(), a[i].first) - vx.begin();
		a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
	}
	rmq.init(n);
	disj.init(n);
	sort(a,a+n);
	for(int i=0; i<n; i++){
		int e = i;
		while(e < n && a[e].first == a[i].first) e++;
		for(int j=i; j<e; j++){
			if(j != i && vy[a[j-1].second] >= vy[a[j].second] - d){
				disj.uni(j-1, j);
			}
			int st = lower_bound(vy.begin(), vy.end(), vy[a[j].second] - d) - vy.begin();
			int ed = lower_bound(vy.begin(), vy.end(), vy[a[j].second] + 1) - vy.begin() - 1;
			pi t = rmq.q(st, ed);
			if(t.first >= 0 && vx[t.first] >= vx[a[j].first] - d){
				disj.uni(t.second, j);
			}
			st = lower_bound(vy.begin(), vy.end(), vy[a[j].second]) - vy.begin();
			ed = lower_bound(vy.begin(), vy.end(), vy[a[j].second] + d + 1) - vy.begin() - 1;
			t = rmq.q(st, ed);
			if(t.first >= 0 && vx[t.first] >= vx[a[j].first] - d){
				disj.uni(t.second, j);
			}
		}
		for(int j=i; j<e; j++){
			rmq.add(a[j].second, pi(a[j].first, j));
		}
		i = e-1;
	}
	int maxsz = *max_element(disj.sz, disj.sz + n);
	int ret = 0;
	for(int i=0; i<n-1; i++){
		ret += disj.uni(i, i+1);
	}
	printf("%d %d",ret, maxsz);
}