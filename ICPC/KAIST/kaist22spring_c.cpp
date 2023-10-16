#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 3005;

int dp[MAXN][MAXN][2];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint m, k;
	int n; cin >> n;
	cin >> m >> k;
	vector<lint> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	auto trial = [&](lint X){
		int j = 0;
		lint ret = 0;
		lint curSum = 0;
		for(int i = 1; i <= n; i++){
			curSum += a[i] + X;
			while(j < i && curSum >= m){
				j++;
				curSum -= a[j] + X;
			}
			ret += j;
		}
		return ret;
	};
	lint s = 0, e = 1e18;
	while(s != e){
		lint m = (s + e) / 2;
		if(trial(m) >= k) e = m;
		else s = m + 1;
	}
	cout << s << "\n";
}
