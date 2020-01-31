#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;
const int mod = 998244353;

int n, a[MAXN];
lint dp[MAXN], nxt[MAXN];
vector<pi> ev;

int main(){
	cin >> n;
	lint ret = 0;
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		ev.emplace_back(n + 1 - x, -1);
		ev.emplace_back(i, +1);
		ret -= x;
	}
	sort(all(ev));
	reverse(all(ev));
	for(auto &[x, y] : ev){
		if(y == -1){
			for(int k=0; k + 1<MAXN; k++){
				nxt[k] = (dp[k] + dp[k + 1]) % mod;
			}
		}
		else{
			for(int k=0; k<MAXN; k++){
				nxt[k] = dp[k];
				if(k == 1) nxt[k]++;
				if(k > 1){
					nxt[k] += dp[k - 1] * k * (k - 1);
				}
				nxt[k] %= mod;
			}
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	ret += dp[0];
	ret %= mod;
	if(ret % 2) ret += mod;
	cout << ret / 2 << endl;
}
