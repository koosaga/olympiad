#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 +7;

int n, m, a[100005], b[100005];
int l[100005], r[100005];

lint solve(int *a, int *b, int n, int m){
    lint sum = 0, ret = 0;
	for(int i=0; i<n; i++){
		l[i] = lower_bound(b, b+m, a[i]) - b;
		r[i] = b + m - upper_bound(b, b+m, a[i]);
	}
	for(int i=0; i<n; i++){
		ret += r[i] * sum;
		sum += l[i];
		ret %= mod;
		sum %= mod;
	}
	return ret;
}

int main(){
	scanf("%d %d %*d %*d",&n,&m);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++) scanf("%d",&b[i]);
	sort(a, a+n);
	sort(b, b+m);
	lint ret = solve(a, b, n, m);
	ret += solve(b, a, m, n);
	cout << ret % mod;
}