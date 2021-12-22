#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 5005;
const int mod = 1e9 + 7;

int dp[MAXN][MAXN][3];
short lcp[MAXN][MAXN];
int nxt[2][MAXN];

void easy(int n, int k){
	vector<pi> a[2];
	lint sum = 0;
	for(int i = 0; i < n; i++){
		string t; cin >> t;
		int p, q; 
		cin >> p >> q;
		sum += q;
		a[t == "G"].emplace_back(p, q);
	}
	for(int i = 0; i <= sz(a[0]); i++){
		for(int j = 0; j <= sz(a[1]); j++){
			dp[i + 1][j][0] = max(dp[i][j][0], dp[i + 1][j][0]);
			dp[i][j + 1][0] = max(dp[i][j][0], dp[i][j + 1][0]);
			if(i < sz(a[0]) && j < sz(a[1]) && abs(a[0][i].first - a[1][j].first) <= k){
				dp[i + 1][j + 1][0] = max(dp[i][j][0] + (int)a[0][i].second + (int)a[1][j].second, dp[i + 1][j + 1][0]);
			}
		}
	}
	cout << sum - dp[sz(a[0])][sz(a[1])][0] << '\n';
}

int haejo[MAXN * 2][2];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t, n, k; 
	cin >> t >> n >> k;
	if(t == 1){
		easy(n, k);
		return 0;
	}
	vector<pi> a[2];
	lint sum = 0;
	for(int i = 0; i < n; i++){
		string t; cin >> t;
		int p, q; 
		cin >> p >> q;
		sum += q;
		a[t == "G"].emplace_back(p, q);
	}
	for(int i = 0; i < 2; i++){
		int p  = 0;
		for(int j = 0; j < sz(a[i]); j++){
			while(p < sz(a[i ^ 1]) && a[i ^ 1][p].first <= a[i][j].first + k) p++;
			nxt[i][j] = p;
		}
	}
	for(int i = sz(a[0]) - 1; i >= 0; i--){
		for(int j = sz(a[1]) - 1; j >= 0; j--){
			if(abs(a[0][i].first - a[1][j].first) <= k) lcp[i][j] = lcp[i+1][j+1] + 1;
		}
	}
	for(int i = 0; i < MAXN; i++){
		for(int j = 0; j < MAXN; j++){
			for(int k = 0; k < 3; k++){
				dp[i][j][k] = -1e9;
			}
		}
	}
	for(int i = 0; i < 2 * MAXN; i++){
		for(int j = 0; j < 2; j++){
			haejo[i][j] = -1e9;
		}
	}
	dp[sz(a[0])][sz(a[1])][0] = 0;
	for(int i = sz(a[0]); i >= 0; i--){
		for(int j = sz(a[1]); j >= 0; j--){
			if(i < sz(a[0])){
				dp[i][j][1] = max(dp[i][j][1], haejo[i + 1 - j + MAXN][0]);
				int nxtpos = max(0, nxt[0][i] - j);
				if(i + 1 + nxtpos <= sz(a[0]) && lcp[i + 1][j] >= nxtpos){
					dp[i][j][1] = max(dp[i][j][1], dp[i + nxtpos + 1][j + nxtpos][0]);
				}
				dp[i][j][1] += a[0][i].second;
			}
			if(j < sz(a[1])){
				dp[i][j][2] = max(dp[i][j][2], haejo[i - j - 1 + MAXN][1]);
				int nxtpos = max(0, nxt[1][j] - i);
				if(j + 1 + nxtpos <= sz(a[1]) && lcp[i][j + 1] >= nxtpos){
					dp[i][j][2] = max(dp[i][j][2], dp[i + nxtpos][j + nxtpos + 1][0]);
				}
				dp[i][j][2] += a[1][j].second;
			}
			if(i < sz(a[0]) && j < sz(a[1])){
				if(abs(a[0][i].first - a[1][j].first) <= k){
				haejo[i - j + MAXN][0] = max(haejo[i - j + MAXN][0], dp[i][j][1]);
				haejo[i - j + MAXN][1] = max(haejo[i - j + MAXN][1], dp[i][j][2]);
				dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j + 1][0]);
				}
				else{
					haejo[i - j + MAXN][0] = haejo[i - j + MAXN][1] = -1e9;
				}
			}
			if(i < sz(a[0])) dp[i][j][0] = max(dp[i][j][1], dp[i][j][0]);
			if(j < sz(a[1])) dp[i][j][0] = max(dp[i][j][2], dp[i][j][0]);
		}
	}
	cout << dp[0][0][0] << '\n';
}
