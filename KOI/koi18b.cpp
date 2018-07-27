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
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, m;
pi a[MAXN];
pi b[MAXN];

lint solve(int v){
	auto l = lower_bound(b + 1, b + m + 1, pi(v + 1, -1e9)) - b;
	return b[l-1].second;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	scanf("%d",&m);
	for(int i=1; i<=m; i++) scanf("%d %d",&b[i].first,&b[i].second);
	for(int i=1; i<=m; i++) b[i].second += b[i-1].second;
	int l, r; cin >> l >> r;
	lint ans = 0;
	for(int i=1; i<=n; i++){
		ans += 1ll * a[i].second * (solve(r + a[i].first) - solve(l - 1 + a[i].first));
	}
	cout << ans << endl;
}
