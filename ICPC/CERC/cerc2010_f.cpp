#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
const int mod = 1e9 + 7;

int n, x[1000005], y[1000005], p[1000005], q[1000005];
int cnt[256], submask[256];
lint dp[256], ipow[1000005];

int popcnt(int x){
	int cnt = 0;
	while(x){
		cnt++;
		x -= x & -x;
	}
	return cnt;
}

void solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&x[i], &y[i]);
		p[i] = x[i] + y[i];
		q[i] = x[i] - y[i];
	}
	memset(cnt, 0, sizeof(cnt));
	int a1 = *min_element(x, x+n);
	int a2 = *max_element(x, x+n);
	int a3 = *min_element(y, y+n);
	int a4 = *max_element(y, y+n);
	int a5 = *min_element(p, p+n);
	int a6 = *max_element(p, p+n);
	int a7 = *min_element(q, q+n);
	int a8 = *max_element(q, q+n);
	for(int i=0; i<n; i++){
		int mask = 0;
		if(a1 == x[i]) mask |= 1;
		if(a2 == x[i]) mask |= 2;
		if(a3 == y[i]) mask |= 4;
		if(a4 == y[i]) mask |= 8;
		if(a5 == p[i]) mask |= 16;
		if(a6 == p[i]) mask |= 32;
		if(a7 == q[i]) mask |= 64;
		if(a8 == q[i]) mask |= 128;
		mask ^= 255;
		for(int j=0; j<=mask; j++){
			if(j & (~mask)) continue;
			cnt[j]++;
		}
	}
	lint ret = 0;
	for(int i=0; i<256; i++){
		if(popcnt(i) & 1) ret += mod - ipow[cnt[i]];
		else ret += ipow[cnt[i]];
		ret %= mod;
	}
	printf("%lld\n",ret);
}

int main(){
	int t;
	scanf("%d",&t);
	ipow[0] = 1;
	for(int i=1; i<=1000000; i++){
		ipow[i] = ipow[i-1] << 1;
		ipow[i] %= mod;
	}
	while(t--){
		solve();
	}
}