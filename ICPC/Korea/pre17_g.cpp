#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;

int n;
pi a[MAXN];
int p[MAXN], l[MAXN], s[MAXN];
short dp[MAXN][MAXN];

int solve(){
	vector<pi> ord;
	for(int i=1; i<=n; i++){
		p[i] = a[i].first;
		l[i] = a[i].second;
		s[i] = s[i-1] + a[i].second;
		ord.push_back(pi(p[i] - s[i], i));
	}
	sort(ord.begin(), ord.end());
	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			dp[i][j] = dp[i-1][j];
			int pos = s[i] - s[j] + p[j];
			if(pos - l[i] <= p[i] && p[i] <= pos) dp[i][j]++;
		}
		int curmax = 0;
		for(auto &j : ord){
			if(j.second < i) curmax = max(curmax, (int)dp[i-1][j.second]);
			else dp[i][j.second] = curmax;
		}
		for(int j=i; j<=n; j++){
			int pos = s[i] - s[j] + p[j];
			if(pos - l[i] <= p[i] && p[i] <= pos) dp[i][j]++;
		}
	}
	return n-*max_element(dp[n] + 1, dp[n] + n + 1);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		cin >> a[i].first;
	}
	for(int i=1; i<=n; i++){
		cin >> a[i].second;
	}
	sort(a+1, a+n+1);
	printf("%d\n", solve());
}
