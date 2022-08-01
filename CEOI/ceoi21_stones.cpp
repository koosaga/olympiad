#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 505;

int dp[505][505];

int f(int x, int y){
	if(x == 0 && y == 0) return false;
	if(~dp[x][y]) return dp[x][y];
	if(y > 0) return dp[x][y] = !f(x, y - 1);
	else{
		if(!f(x - 1, 1)) return dp[x][y] = true;
		if(!f(x - 1, 0)) return dp[x][y] = true;
		return dp[x][y] = false;
	}
}

int main(){
	/*
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	*/
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	memset(dp, -1, sizeof(dp));
	for(int it = 1; ; it++){
		if(it % 2 == 1){
			int k; cin >> k;
			assert(k != -1);
			k--;
			if(a[k] == 1){
				cout << "1" << endl;
				a[k] = 0;
				continue;
			}
			int cnt = 0;
			int dnt = 0;
			for(auto &x : a){
				if(x == 1) cnt++;
				else if(x > 1) dnt++;
			}
			dnt--;
			for(int i = 0; i <= 2 && i < a[k]; i++){
				if(!f(dnt + (i == 2), cnt + (i == 1))){
					cout << a[k] - i << endl;
					a[k] = i;
					break;
				}
			}
		}
		else{
			if(*max_element(all(a)) == 0){
				cout << "-1" << endl;
				return 0;
			}
			pi ans(1e9, -1);
			for(int i = 0; i < n; i++){
				if(a[i]) ans = min(ans, pi(a[i], i));
			}
			cout << ans.second + 1 << endl;
			int q; cin >> q;
			a[ans.second] -= q;
		}
	}
}

