#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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
 
int n, q;
pi a[200005];
int dp[200005];
int ret[200005];
 
struct qry{
	int x, y, idx;
}qr[200005];
 
vector<int> vy;
 
struct seg{
	int tree[530000], lim;
	void init(int n){
		memset(tree, 0, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;
 
int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		vy.push_back(a[i].second);
	}
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<n; i++){
		a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
	}
	sort(a, a+n, [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	seg.init(n);
	for(int i=n-1; i>=0; i--){
		dp[i] = seg.query(0, a[i].second) + 1;
		seg.add(a[i].second, dp[i]);
	}
	for(int i=0; i<q; i++){
		scanf("%d %d",&qr[i].x, &qr[i].y);
		qr[i].idx = i;
	}
	seg.init(n);
	sort(qr, qr + q, [&](const qry &a, const qry &b){
		return a.x > b.x;
	});
	int pnt = n;
	for(int i=0; i<q; i++){
		while(pnt > 0 && a[pnt-1].first >= qr[i].x){
			seg.add(a[pnt-1].second, dp[pnt-1]);
			pnt--;
		}
		ret[qr[i].idx] = seg.query(0, upper_bound(vy.begin(), vy.end(), qr[i].y) - vy.begin() - 1);
	}
	for(int i=0; i<q; i++){
		printf("%d\n",ret[i]);
	}
}