#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 998244353; //1e9 + 7;//998244353;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t; cin >> t;
	while(t--){
		int q, n, m, k;
		cin >> n >> m >> k;
		vector<vector<int>> isWin(m - 1, vector<int>(k));
		vector<int> sc(k);
		for(auto &i : sc) cin >> i;
		for(int i = 0; i < m-1; i++){
			for(int j = 0; j < k; j++){
				int x; cin >> x;
				if(sc[j] <= x) isWin[i][j] = 1;
			}
		}
		bool ok = false;
		if(m <= 20){
			vector<int> v;
			vector<int> dp((1 << (m - 1)), 1e9);
			dp[0] = 0;
			for(int i = 0; i < k; i++){
				int msk = 0;
				for(int j = 0; j < m-1; j++){
					if(!isWin[j][i]) msk |= (1 << j);
				}
				v.push_back(msk);
			}
			for(int i = 0; i < sz(dp); i++){
				if(dp[i] >= n) continue;
				for(auto &j : v){
					dp[i | j] = min(dp[i | j], dp[i] + 1);
				}
			}
			if(dp.back() <= n) ok = true;
		}
		else{
			for(int i = 0; i < (1<<k); i++){
				if(__builtin_popcount(i) > n) continue;
				vector<int> chk(m - 1);
				int cnt = 0;
				for(int j = 0; j < m-1; j++){
					for(int x = 0; x < k; x++){
						if((i >> x) & 1){
							if(!isWin[j][x] && !chk[j]){
								chk[j] = 1;
								cnt++;
							}
						}
					}
				}
				if(cnt == m - 1){
					ok = true;
					break;
				}
			}
		}
		cout << (ok ? "TAK" : "NIE") << "\n";
	}
}
