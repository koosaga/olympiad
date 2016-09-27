#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[200005];
lint ps[200005];

lint solve(int s, int e){
	int m = (s+e)/2;
	return 1ll * a[m] * (m - s + 1) - (ps[m] - ps[s-1]) + (ps[e] - ps[m]) - 1ll * (e - m) * a[m];
}

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i+n] = a[i] + 10000000;
	}
	sort(a+1, a+2*n+1);
	for(int i=1; i<=2*n; i++){
		ps[i] = ps[i-1] + a[i];
	}
	lint ret = 1e18;
	for(int i=1; i<=n; i++){
		ret = min(ret, solve(i, i+n-1));
	}
	cout << ret;
}
