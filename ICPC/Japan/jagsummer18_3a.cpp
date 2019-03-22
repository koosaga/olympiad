#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int dp[MAXN];

int main(){
	string s; cin >> s;
	int cur = 0;
	for(int i=1; i<=s.size(); i++){
		if(s[i-1] == 'R') cur++;
		else cur--;
		dp[i] = dp[i-1];
		if(cur % 4 == 0){
		int cnt = 0;
		for(int j=i-1; j>=0; j--){
			if(s[j] == 'R') cnt--;
			else cnt++;
			if(cnt == -4) dp[i] = max(dp[i], dp[j] + 1);
		}
		}
	}
	cout << dp[s.size()] << endl;
}
