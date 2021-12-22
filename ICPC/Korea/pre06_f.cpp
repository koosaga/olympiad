#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

int solve(vector<int> r, vector<int> c, vector<vector<int>> a){
	int n = sz(r);
	vector<int> ar(n), ac(n);
	int ans = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int isFlip = r[i] ^ c[j] ^ a[i][j];
			ans += isFlip;
			ar[i] ^= isFlip;
			ac[j] ^= isFlip;
		}
	}
	if(ar != r || ac != c) return 1e9;
	return ans;
}

int main(){
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vector<vector<int>> a(n, vector<int>(n));
		vector<int> r(n), c(n);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				string s; cin >> s;
				int y = (s == "V");
				a[i][j] ^= y;
				r[i] ^= y;
				c[j] ^= y;
			}
		}
		int ret = 1e9;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				ret = min(ret, solve(r, c, a));
				for(auto &x : c) x ^= 1;
			}
			for(auto &x : r) x ^= 1;
		}
		cout << ret << '\n';
	}
}
