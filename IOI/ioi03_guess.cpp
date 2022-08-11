#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

char sum[1 << 24];
char dp[1 << 24];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m; cin >> n >> m;
	vector<string> s(n);
	vector<int> msk(n);
	memset(dp, 0x3f, sizeof(dp));
	for(int i = 0; i < n; i++){
		s[i].resize(m);
		int ans = 0;
		for(int j = 0; j < m; j++){
			cin >> s[i][j];
			ans |= (1 << (3 * j + (s[i][j] - 'X')));
		}
		int w = (1 << (3 * m)) - ans - 1;
		for(int x = w; ; x = (x - 1) & w){
			sum[x | ans]++;
			if(x == 0) break;
		}
		msk[i] = ans;
	}
	for(int j = 0; j < (1 << (3 * m)); j++){
		if(sum[j] == 0) continue;
		else if(sum[j] == 1) dp[j] = 0;
		else{
			for(int k = 0; k < m; k++){
				int w = (j >> (3 * k)) & 7;
				for(int l = w; l > 0; l = (l - 1) & w){
					if(w == l) continue;
					int D = (l << (3 * k));
					int E = ((w - l) << (3 * k));
					dp[j] = min(dp[j], (char)(max(dp[j - D], dp[j - E]) + 1));
				}
			}
		}
	}
	int pos = (1 << (3 * m)) - 1;
	while(dp[pos]){
		bool ok = 0;
		for(int k = 0; k < m; k++){
			int w = (pos >> (3 * k)) & 7;
			for(int l = w; l > 0; l = (l - 1) & w){
				if(w == l) continue;
				int D = (l << (3 * k));
				int E = ((w - l) << (3 * k));
				if(max(dp[pos - D], dp[pos - E]) + 1 == dp[pos]){
					cout << "Q " << k + 1;
					for(int x = 0; x < 3; x++){
						if((D >> (3 * k + x)) & 1){
							cout << " " << (char)(x + 'X');
						}
					}
					cout << endl;
					int y; cin >> y;
					if(y == 0) pos -= D;
					else pos -= E;
					ok = 1;
					break;
				}
			}
			if(ok) break;
		}
	}
	for(int i = 0; i < n; i++){
		if((pos & msk[i]) == msk[i]){
			cout << "C " << i + 1 << endl;
			return 0;
		}
	}
}
