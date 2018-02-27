#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
const int MAXN = 500005;

lint sum[MAXN], tot;
int n, a[MAXN];

int main(){
	scanf("%d",&n);
	lint ans = 0;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		lint tmp = 1 + tot - sum[a[i]] + mod;
		tmp %= mod;
		sum[a[i]] += tmp;
		tot += tmp;
		ans += tmp;
		ans %= mod;
		tot %= mod;
		sum[a[i]] %= mod;
	}
	cout << ans << endl;
}