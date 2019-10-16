#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, w;
lint a[MAXN];
int dp[MAXN];

bool trial(lint x){
	dp[0] = 1;
	int p1 = 0, p2 = 0;
	for(int i=1; i<=n; i++){
		while(a[i] - a[p1] >= x) p1++;
		while(a[i] - a[p2] > w) p2++;
		int sum = (p1 ? dp[p1-1] : 0) - (p2 ? dp[p2-1] : 0);
		if(sum) dp[i] = dp[i-1] + 1;
		else dp[i] = dp[i-1];
	}
	return dp[n] != dp[n-1];
}

int main(){
	scanf("%d %d",&w,&n);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	lint s = 0, e = w;
	while(s != e){
		lint m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << (w - s) * (w - s) << endl;
}
