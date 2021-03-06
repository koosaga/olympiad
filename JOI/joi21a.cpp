#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n;
lint a[MAXN], c[MAXN], d[MAXN];

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
	for(int i = 1; i <= n; i++){
		c[i] = c[i - 1] + max(a[i - 1] - a[i] + 1, 0ll);
	}
	for(int i = n; i; i--){
		d[i] = d[i + 1] + max(a[i + 1] - a[i] + 1, 0ll);
	}
	lint ret = 1e18;
	for(int i = 1; i <= n; i++){
		ret = min(ret, max(c[i], d[i]));
	}
	cout << ret << endl;
}

