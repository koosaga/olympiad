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

int n, a[50005], b[50005], v[100005], p;
int cale[50005], cals[50005];

struct seg1{
	int tree[270000], lazy[270000];
	void init(){
		memset(tree,0,sizeof(tree));
		memset(lazy,0,sizeof(lazy));
	}
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps + pe) / 2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg1;

int solve(){
	int ret = 0;
	int ed = n-1, st = 0;
	seg1.init();
	for(int i=0; i<n; i++){
		seg1.add(a[i], 2*n, 1, 2*n, 1, 1);
		if(seg1.query(b[ed], 2*n, 1, 2*n, 1) > 0){
			seg1.add(b[ed], 2*n, 1, 2*n, 1, -1);
			ed--;
		}
		cale[i] = ed;
	}
	seg1.init();
	vector<int> vr;
	for(int i=n-1; i>=0; i--){
		seg1.add(1, a[i], 1, 2*n, 1, 1);
		if(seg1.query(1, b[st], 1, 2*n, 1) > 0){
			seg1.add(1, b[st], 1, 2*n, 1, -1);
			st++;
		}
		cals[i] = st;
	}
	for(int i=0; i<=n; i++){
		ret = max(ret, n - ((i ? cale[i-1] : n-1) - cals[i] + 1));
	}
	return ret;
}

int main(){
	freopen("cardgame.in","r",stdin);
	freopen("cardgame.out","w",stdout);
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i];
		v[a[i]] = 1;
	}
	for(int i=1; i<=2*n; i++){
		if(!v[i]) b[p++] = i;
	}
	cout << solve();
}