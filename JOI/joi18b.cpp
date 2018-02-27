#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;

int n;
pi a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%lld %lld",&a[i].first,&a[i].second);
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++){
		a[i].second += a[i-1].second;
	}
	lint maxv = -1e18, ans = 0;
	for(int i=1; i<=n; i++){
		maxv = max(maxv, a[i].first - a[i-1].second);
		ans = max(ans, -a[i].first + a[i].second + maxv);
	}
	cout << ans << endl;
}
