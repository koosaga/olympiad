#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using pi = pair<int, int>;

int n, k;
char str1[500010];
char str2[500010];

int dp[MAXN], BW[MAXN], WB[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	scanf("%s %s", str1 + 1, str2 + 1);
	for(int i=2; i<=n; i++){
		BW[i] = BW[i-1] + (str2[i-1] == 'B' && str2[i] == 'W');
		WB[i] = WB[i-1] + (str2[i-1] == 'W' && str2[i] == 'B');
	}
	priority_queue<pi, vector<pi>, greater<pi> > pq1;
	priority_queue<pi, vector<pi>, greater<pi> > pq2;
	pq1.emplace(dp[0] - WB[1], 0);
	pq2.emplace(dp[0] - BW[1], 0);
	for(int i=1; i<=n; i++){
		dp[i] = 1e9;
		if(str1[i] == str2[i]) dp[i] = dp[i-1];
		while(!pq1.empty() && pq1.top().second < i - k) pq1.pop();
		while(!pq2.empty() && pq2.top().second < i - k) pq2.pop();
		dp[i] = min(dp[i], 1 + WB[i] + pq1.top().first + (str2[i] == 'W'));
		dp[i] = min(dp[i], 1 + BW[i] + pq2.top().first + (str2[i] == 'B'));
		pq1.emplace(dp[i] - WB[i+1], i);
		pq2.emplace(dp[i] - BW[i+1], i);
	}
	cout << dp[n] << endl;
}