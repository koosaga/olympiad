#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 300005;

vector<pi> gph[MAXN];
int ans = 0;
lint t[MAXN];
int n;

pi dfs(int x, int p = -1){
	lint closest = 1e18;
	lint tolerance = t[x];
	for(auto &[w, y] : gph[x]){
		if(y == p) continue;
		auto sln = dfs(y, x);
		if(sln.first == 0){ // covered
			// closest covering ones
			closest = min(closest, sln.second + w);
		}
		else{
			if(sln.second < w){
				// Low toleration.
				ans++;
				closest = min(closest, w - sln.second);
			}
			else{
				tolerance = min(tolerance, sln.second - w);
			}
		}
	}
	if(closest <= tolerance) return pi(0, closest);
	return pi(1, tolerance);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> n >> k;
	vector<lint> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 0; i < n-1; i++){
		int s, e, x; cin >> s >> e >> x;
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	lint s = 0, e = 1e18;
	while(s != e){
		lint m = (s + e) / 2;
		for(int i = 1; i <= n; i++){
			t[i] = m / a[i];
		}
		ans = 0;
		if(dfs(1).first) ans++;
		if(ans <= k) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}
