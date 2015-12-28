#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <complex>
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
typedef complex<double> pnt;

int a[300005], n;
lint ret[300005], sum[2][300005];
int rotp;

struct rmq{
	pi tree[1050000];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 1050000, pi(1e9, 1e9));
		for(int i=0; i<n; i++){
			tree[i+lim] = pi(a[i], i);
		}
		for(int i=lim-1; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
	}
	pi query(int s, int e){
		pi ret(1e9, 1e9);
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq;

lint expand(int x, int s, int e){
	int ps = s, pe = e;
	lint ret = a[x];
	while(ps < x || x < pe){
		pi t1 = rmq.query(ps, x-1);
		pi t2 = rmq.query(x+1, pe);
		if(t1.first < t2.first){
			int cl = pe - t1.second;
			ret += sum[pe%2][t1.second] - sum[pe%2][ps-1];
			ps = t1.second + 1;
		}
		else{
			int cl = t2.second - ps;
			ret += sum[ps%2][pe] - sum[ps%2][t2.second-1];
			pe = t2.second - 1;
		}
	}
	return ret;
}

void solve(int s, int e, lint alt0, lint alt1){
	if(s > e) return;
	int p = rmq.query(s, e).second;
	ret[p] = expand(p, s, e) + alt0;
	lint nalt0 = sum[s%2][e] - sum[s%2][p-1];
	lint nalt1 = sum[(s+1)%2][e] - sum[(s+1)%2][p-1];
	solve(s, p-1, nalt0 + alt0, nalt1 + alt1);
	nalt0 = sum[e%2][p] - sum[e%2][s-1];
	nalt1 = sum[(e+1)%2][p] - sum[(e+1)%2][s-1];
	solve(p+1, e, nalt0 + alt0, nalt1 + alt1);
} 

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	rotp = min_element(a, a+n) - a;
	rotate(a, a + rotp, a+n);
	for(int i=0; i<n; i++){
		if(i){
			sum[0][i] = sum[0][i-1];
			sum[1][i] = sum[1][i-1];
		}
		sum[i%2][i] += a[i];
	}
	rmq.init(n, a);
	ret[0] = a[0];
	int s = 1, e = n-1;
	for(int i=0; i<n-1; i++){
		if(a[s] < a[e]){
			if(i%2 == 1) ret[0] += a[e];
			e--;
		}
		else{
			if(i%2 == 1) ret[0] += a[s];
			s++;
		}
	}
	if(n%2 == 1) solve(1, n-1, a[0], 0);
	else solve(1, n-1, 0, a[0]);
	rotate(ret, ret + n - rotp, ret + n);
	for(int i=0; i<n; i++){
		printf("%lld\n",ret[i]);
	}
}