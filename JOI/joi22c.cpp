#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 505;

double dp[MAXN][MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pi> x(n);
	for(int i = 0; i < n; i++){
		cin >> x[i].first >> x[i].second;
		if(x[i].second == -1) x[i].second = 1e6;
	}
	sort(all(x), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	double ret = 1e9;
	for(int i = 0; i <= k; i++){
		for(int j = 0; j <= k - i; j++){
			dp[0][j] = 1e9;
		}
		dp[0][0] = 0;
		for(int j = 1; j <= n; j++){
			for(int b = 0; b <= k - i; b++){
				int ord = j - b;
				dp[j][b] = dp[j-1][b] + (1 <= ord && ord <= i ? 1.0 * x[j - 1].second / ord : 0);
				if(b) dp[j][b] = min(dp[j][b],
						dp[j-1][b-1] + 1.0 * x[j-1].first / (i + 1));
			}
		}
		ret = min(ret, dp[n][k - i]);
	}
	printf("%.20f\n", ret);
}
