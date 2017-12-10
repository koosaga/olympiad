#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 3000005;

int main(){
	string s = "0123456789";
	string t;
	pi ans(-1e18, -1e18);
	lint pwr = 1, y = 0;
	cin >> t;
	int n = t.size();
	for(int i=0; i<n; i++){
		pwr = pwr * 10;
		y = y * 10 + t[i] - '0';
	}
	do{
		lint x = 0;
		for(int i=0; i<n; i++) x = x * 10 + s[i] - '0';
		ans = max(ans, 
				pi(min(pwr - abs(x - y), abs(x - y)), -x));
	}while(next_permutation(s.begin(), s.end()));
	ans.second *= -1;
	for(int i=0; i<n; i++){
		pwr /= 10;
		printf("%lld", ans.second / pwr);
		ans.second %= pwr;
	}
}
