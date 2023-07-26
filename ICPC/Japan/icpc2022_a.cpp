#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using llf = long double;
const int MAXN = 15005;

int ps[MAXN], chk[MAXN], n, S;
bitset<MAXN> dp[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<array<int, 3>> a(n);
	vector<int> vis(n);
	for(int i = 0;i < n; i++){
		cin >> a[i][0] >> a[i][1];
		a[i][2] = i;
	}
	vector<int> ans(n);
	for(int i = 1; i <= 31; i++){
		vector<pi> pos;
		for(int j = 0; j < n; j++){
			if(a[j][0] <= i && !vis[a[j][2]]){
				pos.push_back({a[j][1], a[j][2]});
			}
		}
		sort(all(pos));
		for(int j = 0; j < min(k, sz(pos)); j++){
			vis[pos[j][1]] = 1;
			ans[pos[j][1]] = i;
		}
	}
	for(auto &x : ans) cout << x << "\n";
}