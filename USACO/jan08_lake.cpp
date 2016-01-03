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
typedef pair<lint, int> pi;

int n;
int w[100005], h[100005];

struct rmq{
	pi tree[270000];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++){
			tree[i+lim] = pi(a[i], i);
		}
		for(int i=lim; i; i--){
			tree[i] = max(tree[2*i], tree[2*i+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(0,0);
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}rmq;

lint ret[100005];
int minp;

pi solve(int s, int e, lint offset){
	if(s > e) return pi(0, 0);
	pi t = rmq.query(s, e);
	pi ls, rs;
	if(t.second < minp){
		ls = solve(t.second + 1, e, offset);
		ls.first += 1ll * (w[e] - w[t.second]) * (t.first - ls.second);
		rs = solve(s, t.second - 1, offset + ls.first);
		rs.first += 1ll * (w[t.second - 1] - w[s-1]) * (t.first - rs.second);
	}
	else{
		ls = solve(s, t.second - 1, offset);
		ls.first += 1ll * (w[t.second - 1] - w[s-1]) * (t.first - ls.second);
		rs = solve(t.second + 1, e, offset + ls.first);
		rs.first += 1ll * (w[e] - w[t.second]) * (t.first - rs.second);
	}
	ret[t.second] = offset + ls.first + rs.first + w[e] - w[s-1];
	return pi(ls.first + rs.first, t.first);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&w[i], &h[i]);
		w[i] += w[i-1];
	}
	minp = min_element(h+1, h+n+1) - h;
	rmq.init(n, h);
	solve(1, n, 0);
	for(int i=1; i<=n; i++){
		printf("%lld\n",ret[i]);
	}
}