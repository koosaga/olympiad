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

int n, k, a[1005];

lint s0[1005], s1[1005];
lint dp[8][1005];

struct cht{
	lint pa[1005], pb[1005];
	int p, sz;
	void init(){
		p = sz = 0;
	}
	llf cross(int a, int b){
		return (llf) (pb[b] - pb[a]) / (pa[a] - pa[b]);
	}
	void add(lint a, lint b){
		tie(pa[sz], pb[sz]) = make_tuple(a, b);
		while(sz - 2 >= p && cross(sz, sz-1) <= cross(sz-1, sz-2)){
			pa[sz-1] = pa[sz];
			pb[sz-1] = pb[sz];
			sz--;
		}
		sz++;
	}
	lint func(int p, int x){
		return pa[p] * x + pb[p];
	}
	lint query(int x){
		while(p + 1 < sz && func(p, x) > func(p+1, x)) p++;
		return func(p, x);
	}
}cht;

lint solve(){
	for(int i=1; i<=n; i++){
		s0[i] = s0[i-1] + a[i];
		s1[i] = s1[i-1] + a[i] * i;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=k; i++){
		cht.init();
		for(int j=1; j<=n; j++){
			cht.add(-(j), dp[i-1][j-1] - s1[j-1] + 1ll * (j) * s0[j-1]);
			dp[i][j] = cht.query(s0[j]) + s1[j];
		}
	}
	return dp[k][n];
}
int main(){
	freopen("cbarn.in","r",stdin);
	freopen("cbarn.out","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	lint ret = 1e18;
	for(int i=1; i<=n; i++){
		ret = min(ret, solve());
		rotate(a+1, a+2, a+n+1);
	}
	printf("%lld",ret);
}