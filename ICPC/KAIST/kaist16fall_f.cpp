#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<pi> daks;
int dp1[10005], dp2[10005];

int main(){
	int l = 1, r = 2;
	while(r < 10000){
		daks.push_back(pi(l, r));
		tie(l, r) = pi(r, l+r);
	}
	int n;
	cin >> n;
	for(int i=1; i<=10000; i++) dp1[i] = 1e9, dp2[i] = -1e9;
	for(int i=1; i<=n; i++){
		for(auto &j : daks){
			if(j.second <= i){
				dp1[i] = min(dp1[i], dp1[i - j.second] + j.first);
				dp2[i] = max(dp2[i], dp2[i - j.second] + j.first);
			}
		}
	}
	cout << dp1[n] << " " << dp2[n];
}
