#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;

string dp[MAXN];

bool cmp(const string &a, const string &b){
	if(a.size() != b.size()) return a.size() < b.size();
	return a < b;
}

int main(){
	dp[1] = "()";
	dp[2] = "[]";
	dp[3] = "{}";
	for(int i=2; i<MAXN; i++){
		if(i > 3){
			for(int j=0; j<i; j++) dp[i] = dp[i] + "()";
		}
		if(i % 2 == 0) dp[i] = min(dp[i], "(" + dp[i / 2] + ")", cmp);
		if(i % 3 == 0) dp[i] = min(dp[i], "[" + dp[i / 3] + "]", cmp);
		if(i % 5 == 0) dp[i] = min(dp[i], "{" + dp[i / 5] + "}", cmp);
		for(int j=1; j<i; j++){ 
			dp[i] = min(dp[j] + dp[i - j], dp[i], cmp);
		}
	}
	for(int i=1; i<MAXN; i++){
		for(auto &j : dp[i]){
			if(j == '[') j = '{';
			else if(j == '{') j = '[';
			if(j == ']') j = '}';
			else if(j == '}') j = ']';
		}
	}
	int q; cin >> q;
	assert(q <= 100 && 1 <= q);
	while(q--){
		int x; cin >> x;
		assert(5 <= x && x <= 1000);
		cout << dp[x] << endl;
	}
}
