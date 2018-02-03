#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 100005;

int n, a[MAXN], dp[MAXN], fst;

bool trial(int x){
	int clq = 0, p = 0;
	for(int i=1; i<=n; i++){
		while(a[i] - a[p+1] >= x) p++;
		dp[i] = max(dp[i-1], dp[p] + 1);
		clq = max(clq, i - p);
	}
	if(clq >= (n + 3) / 2) return 0;
	if(n - dp[n] <= n / 2 - 1) return 1;
	return fst;
}

int main(){
	char buf[10];
	cin >> n >> buf;
	if(*buf == 'A') fst = 1;
	if(n % 2 == 0) fst ^= 1;
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	int s = 1, e = 1e9;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s;
}
