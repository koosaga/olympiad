#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

int n, a[MAXN], dp[MAXN][MAXN];

int getpos(int v){
	auto l = lower_bound(a, a + n, v) - a;
	if(l < n && a[l] == v) return l;
	return -1;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a + n);
	int ret = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			dp[i][j] = 2;
			int nxt = 2 * a[j] - a[i];
			int pos = getpos(nxt);
			if(~pos) dp[i][j] = max(dp[i][j], dp[j][pos] + 1);
			ret = max(ret, dp[i][j]);
		}
	}
	cout << ret << endl;
}
