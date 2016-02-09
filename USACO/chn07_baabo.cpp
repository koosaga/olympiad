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

int n;
lint a[1005], b[1005];
lint dp[1005][1005];

struct cht{
	int p, sz;
	lint pa[1005], pb[1005];
	double cross(int a, int b){
		return 1.0 * (pb[a] - pb[b]) / (pa[b] - pa[a]);
	}
	void add(lint a, lint b){
		pa[sz] = a;
		pb[sz] = b;
		while(sz - 2 >= p && 
			1ll * (pb[sz-2] - pb[sz-1]) * (pa[sz] - pa[sz-1])
			>= 1ll * (pb[sz-1] - pb[sz]) * (pa[sz-1] - pa[sz-2])){
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
		if(p == sz) return -1e18;
		while(p + 1 < sz && func(p, x) < func(p+1, x)) p++;
		return func(p, x);
	}
}ld[1005], rd[1005];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		a[i] += a[i-1];
	}
	for(int i=1; i<=n; i++){
		cin >> b[i];
		b[i] += b[i-1];
	}
	a[n+1] = a[n], b[n+1] = b[n];
	for(int i=1; i<=n; i++){
		dp[0][i] = dp[i][0] = -1e18;
	}
	for(int i=1; i<=n+1; i++){
		for(int j=1; j<=n+1; j++){
			rd[j-1].add(a[i-1], dp[i-1][j-1] - a[i-1] * a[i-1]);
		}
		for(int j=1; j<=n+1; j++){
			ld[i-1].add(b[j-1], dp[i-1][j-1] - b[j-1] * b[j-1]);
			lint cl = ld[i-1].query(2 * b[j-1]) - b[j-1] * b[j-1];
			lint cr = rd[j-1].query(2 * a[i-1]) - a[i-1] * a[i-1];
			dp[i][j] = max(cl, cr) + (a[i] - a[i-1]) * (b[j] - b[j-1]);
			/*
			for(int k=0; k<i; k++){
				dp[i][j] = max(dp[i][j], 
					dp[k][j-1] - a[k] * a[k] + 2 * a[i-1] * a[k]
					- a[i-1] * a[i-1])
			}
			for(int k=0; k<j; k++){
				dp[i][j] = max(dp[i][j], dp[i-1][k] - (b[j-1] - b[k]) * (b[j-1] - b[k]));
			}
			dp[i][j] += (a[i] - a[i-1]) * (b[j] - b[j-1]);*/
		}
	}
	cout << dp[n+1][n+1];
}