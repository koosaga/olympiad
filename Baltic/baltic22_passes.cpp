#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

lint nxt[1 << 15][15];
int cnt[15][MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s; cin >> s;
	int n = sz(s);
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < n; j++){
			cnt[i][j + 1] = cnt[i][j] + (s[j] == ('A' + i));
		}
	}
	for(int i = 0; i < 15; i++){
		vector<int> v;
		for(int j = 0; j < n; j++){
			if(s[j] == i + 'A') v.push_back(j);
		}
		vector<lint> L[15], R[15];
		for(int j = 0; j < 15; j++){
			L[j].resize(sz(v));
			R[j].resize(sz(v));
			for(int k = 0; k < sz(v); k++){
				L[j][k] = cnt[j][v[k]];
				if(k) L[j][k] += L[j][k-1];
			}
			for(int k = sz(v) - 1; k >= 0; k--){
				R[j][k] = cnt[j][n] - cnt[j][v[k]+1];
				if(k + 1 < sz(v)) R[j][k] += R[j][k+1];
			}
		}
		for(int j = 0; j < (1<<15); j++){
			if((j >> i) & 1) continue;
			auto func = [&](int k){
				lint lo = 0, hi = 0;
				for(int x = 0; x < 15; x++){
					if((j >> x) & 1){
						if(k) lo += L[x][k - 1];
						if(k < sz(v)) hi += R[x][k];
					}
				}
				return 2 * lo + 2 * hi + 1ll * k * (k - 1) / 2 + 1ll * (sz(v) - k) * (sz(v) - k - 1) / 2;
			};
			int s = 0, e = sz(v); 
			while(s != e){
				int m = (s + e) / 2;
				if(func(m) > func(m + 1)) s = m + 1;
				else e = m;
			}
			nxt[j][i] = func(s);
		}
	}
	vector<lint> dp(1 << 15, 1e18);
	dp[0] = 0;
	for(int i = 1; i < (1<<15); i++){
		for(int j = 0; j < 15; j++){
			if((i >> j) & 1){
				dp[i] = min(dp[i], dp[i - (1<<j)] + nxt[i - (1<<j)][j]);
			}
		}
	}
	cout << setprecision(69) << dp.back() * 0.5 << "\n";
}
