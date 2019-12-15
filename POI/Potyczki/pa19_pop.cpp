#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 205;
const int MAXL = 64;
const int mod = 1e9 + 7;

lint n, m, a[MAXN];
lint dp[MAXL][MAXN][MAXN];
lint rdp[MAXL][MAXN];
vector<pi> v;

void dfs(lint s, lint e, lint ps, lint pe){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		v.emplace_back(ps, pe);
		return;
	}
	lint pm = (ps+pe)/2;
	dfs(s, e, ps, pm); dfs(s, e, pm+1, pe);
}

int popcnt(lint x){
	int ret = 0;
	while(x){
		ret++;
		x -= x & -x;
	}
	return ret;
}

int main(){
	for(int i=0; i<MAXL; i++){
		for(int j=0; j<MAXN; j++){
			rdp[i][j] = -4e18;
			for(int k=0; k<MAXN; k++){
				dp[i][j][k] = -4e18;
				if(i == 0 && j == k) dp[i][j][k] = 0;
				if(i == 0 && j + 1 == k) dp[i][j][k] = 0;
			}
		}
	}
	scanf("%lld %lld",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	for(int i=1; i<MAXL; i++){
		for(int j=0; j<=n; j++){
			for(int k=j; k<=n; k++){
				for(int m=j; m<=k; m++){
					dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][m] + dp[i-1][m][k] + a[k] - a[m]);
				}
			}
		}
	}
	dfs(0, m, 0, (1ll<<60)-1);
	sort(all(v));
	rdp[0][0] = 0;
	for(int i=0; i<sz(v); i++){
		int pcnt = popcnt(v[i].first);
		int lv = popcnt(v[i].second) - popcnt(v[i].first);
		for(int j=0; j<=n; j++){
			for(int k=0; k<=j; k++){
				rdp[i + 1][j] = max(rdp[i + 1][j], rdp[i][k] + dp[lv][k][j] + pcnt * (a[j] - a[k]));
			}
		}
	}
	cout << rdp[sz(v)][n] << endl;
}
