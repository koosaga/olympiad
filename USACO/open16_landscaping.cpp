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

int q, x, y, z;
int a[1000005], b[1000005], n, m;

struct t1{
	int pos, typ, lev;
}elem[2000005], tmp[2000005];

lint dp[2000005], psum[2000005];

lint solve(int s, int e){
	for(int i=s; i<=e; i++){
		tmp[i-s+1] = elem[i];
	}
	for(int i=2; i<=e-s+1; i++){
		psum[i] = psum[i-2] + min(0ll, 1ll * z * (tmp[i].pos - tmp[i-1].pos) - x - y);
	}
	lint p10 = 1e18, p11 = 1e18;
	lint p20 = 1e18, p21 = 1e18;
	for(int i=1; i<=e-s+1; i++){
		dp[i] = dp[i-1];
		dp[i] = min(dp[i], (i % 2 ? p10 : p11) + psum[i-1]);
		dp[i] = min(dp[i], (i % 2 ? p20 : p21) + psum[i-1] + 1ll * z * tmp[i].pos - x - y);
		if(i%2 == 0){
			p10 = min(p10, dp[i-1] - psum[i]);
			p20 = min(p20, dp[i-1] - psum[i] - 1ll * z * tmp[i].pos);
		}
		if(i%2 == 1){
			p11 = min(p11, dp[i-1] - psum[i]);
			p21 = min(p21, dp[i-1] - psum[i] - 1ll * z * tmp[i].pos);
		}
	}
	return dp[e-s+1];
}

int main(){
	scanf("%d %d %d %d",&q,&y,&x,&z);
	for(int i=0; i<q; i++){
		int p, q;
		scanf("%d %d",&p,&q);
		while(p--){
			a[n++] = i;
		}
		while(q--){
			b[m++] = i;
		}
	}
	for(int i=0; i<n; i++){
		elem[i] = {a[i], 1, 0};
	}
	for(int i=0; i<m; i++){
		elem[i+n] = {b[i], 2, 0};
	}
	sort(elem, elem+n+m, [&](const t1 &a, const t1 &b){
		return pi(a.pos, a.typ) < pi(b.pos, b.typ);
	});
	for(int i=1; i<n+m; i++){
		if(elem[i].typ == elem[i-1].typ){
			if(elem[i].typ == 1){
				elem[i].lev = elem[i-1].lev - 1;
			}
			else{
				elem[i].lev = elem[i-1].lev + 1; 
			}
		}
		else{
			elem[i].lev = elem[i-1].lev;
		}
	}
	sort(elem, elem+n+m, [&](const t1 &a, const t1 &b){
		return pi(a.lev, a.pos) < pi(b.lev, b.pos);
	});
	lint ret = 0;
	for(int i=0; i<n+m; ){
		int e = i;
		while(e < n+m && elem[e].lev == elem[i].lev) e++; // z - x - y
		ret += solve(i, e-1);
		i = e;
	}
	ret += 1ll * x * n + 1ll * y * m;
	cout << ret;
}
