#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; string s; cin >> n >> s;
	unordered_set<string> hs;
	for(int i = 0; i < n; i++){
		string t; 
		cin >> t;
		hs.insert(t);
	}
	vector<int> dp(sz(s) + 1, 1e9); dp[0] = 0;
	for(int i = 1; i <= sz(s); i++){
		int cur = 1e9;
		for(int j = 2; j <= i && j <= 20; j++){
			string t = s.substr(i - j, j);
			cur = min(cur, dp[i - j + 1]);
			if(hs.count(t)){
				dp[i] = min(dp[i], cur + 1);
				if(i == j) dp[i] = 1;
			}
		}
	}
	cout << dp.back() << "\n";
}
