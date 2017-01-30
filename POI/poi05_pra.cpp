#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
pi a[1005];
int dp[1005][1005];
int pfx[1005][1005];

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

vector<int> ang[1005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].second *= -1;
	}
	sort(a+2, a+n, [&](const pi &p, const pi &q){
		if(1ll * ccw(a[0], a[1], p) * ccw(a[0], a[1], q) < 0){
			return ccw(a[0], a[1], p) > ccw(a[0], a[1], q);
		}
		return ccw(a[0], p, q) > 0;
	});
	for(int i=n-1; i; i--){
		for(int j=i+1; j<n; j++){
			if(ccw(a[i], a[j], a[0]) <= 0){
				dp[i][j] = -1e9;
				continue;
			}
			else{
				ang[i].push_back(j);
				int s = 0, e = ang[j].size();
				while(s != e){
					int m = (s+e)/2;
					if(ccw(a[i], a[j], a[ang[j][m]]) > 0) e = m;
					else s = m+1;
				}
				dp[i][j] = pfx[j][s] + 1;
			}
		}
		sort(ang[i].begin(), ang[i].end(), [&](const int &p, const int &q){
			return ccw(a[i], a[p], a[q]) > 0;
		});
		for(int j=(int)ang[i].size()-1; j>=0; j--){
			pfx[i][j] = max(dp[i][ang[i][j]], pfx[i][j+1]);
		}
	}
	int ans = 0;
	for(int i=2; i<n; i++){
		if(ccw(a[0], a[1], a[i]) > 0) ans = max(ans, 1 + dp[1][i]);
	}
	cout << ans;
}
