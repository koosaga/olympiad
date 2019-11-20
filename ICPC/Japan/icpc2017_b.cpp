#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int inf = 1e9 + 100;

int n, t, a[MAXN], b[MAXN];

int main(){
	cin >> n >> t;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++) b[i] = max(a[i], b[i - 1]);
	lint sum = 0;
	for(int i=1; i<=n; i++){
		lint curTime = (t - sum + b[i] - a[i]) / b[i];
		printf("%lld\n", max(0ll, curTime) + 1);
		sum += a[i];
	}
}
