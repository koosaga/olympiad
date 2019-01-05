#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, a[MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint ret[MAXN];

int main(){
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	vector<pi> hull;
	for(int i=0; i<=n+1; i++){
		while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), pi(i, a[i])) >= 0){
			hull.pop_back();
		}
		hull.emplace_back(i, a[i]);
	}
	for(int i=1; i<hull.size(); i++){
		int l = hull[i-1].first, r = hull[i].first;
		for(int j=l; j<=r; j++){
			unsigned long long gap = 1ll * a[l] * (r - j) + 1ll * a[r] * (j - l);
			gap *= 100000;
			ret[j] = gap / (r - l);
		}
	}
	for(int i=1; i<=n; i++){
		printf("%lld\n", ret[i]);
	}
}
