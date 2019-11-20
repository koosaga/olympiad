#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, k, a[MAXN];
lint sum[MAXN];

lint cost(int s, int e){ // [s, e]
	if(s >= e) return 0;
	int m = (s + e) / 2;
	lint ret = 0;
	ret += 1ll * (m - s + 1) * a[m] - (sum[m] - sum[s-1]);
	ret += (sum[e] - sum[m]) - 1ll * (e - m) * a[m];
	return ret;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	sort(a + 1, a + n + 1);
	for(int i=1; i<=n; i++) sum[i] = sum[i-1] + a[i];
	int ptr = 1, ret = 0;
	for(int i=1; i<=n; i++){
		while(ptr < n && cost(i, ptr + 1) <= k) ptr++;
		ret = max(ret, ptr - i + 1);
	}
	cout << ret << endl;
}
