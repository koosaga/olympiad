#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int k, n;
int s[500005], e[500005];
int dx[2000005], mx[2000005];
int dp[2000005];
pi a[500005], b[500005];
vector<pi> v;

int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

int main(){
	scanf("%d %d",&k,&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&a[i].first,&a[i].second,&b[i].first, &b[i].second);
		int g1 = gcd(a[i].first, a[i].second);
		int g2 = gcd(b[i].first, b[i].second);
		a[i].first /= g1;
		a[i].second /= g1;
		b[i].first /= g2;
		b[i].second /= g2;
		v.push_back(a[i]);
		v.push_back(b[i]);
	}
	auto cmp = [&](const pi &a, const pi &b){
		return 1ll * a.first * b.second - 1ll * b.first * a.second > 0;
	};
	sort(v.begin(), v.end(), cmp);
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<n; i++){
		s[i] = lower_bound(v.begin(), v.end(), a[i], cmp) - v.begin();
		e[i] = lower_bound(v.begin(), v.end(), b[i], cmp) - v.begin();
		if(s[i] > e[i]) swap(s[i], e[i]);
		s[i] *= 2;
		e[i] *= 2;
		dx[s[i]]++;
		dx[e[i] + 1]--;
		mx[s[i]] = max(mx[s[i]], e[i]);
	}
	n = v.size() * 2 - 1;
	for(int i=1; i<n; i++){
		mx[i] = max({mx[i-1], mx[i], i});
		dx[i] += dx[i-1];
	}
	int ans = 0;
	for(int i=1; i<=k; i++){
		for(int j=0; j<n; j++) dp[j] = max(dp[j], dp[mx[j] + 1] + dx[j]);
		for(int j=n-1; j>=0; j--) dp[j] = max(dp[j], dp[j+1]);
		ans = max(ans, dp[0]);
	}
	cout << ans;
}
