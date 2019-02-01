#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;
const int mod = 998244353;
const int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};

set<pi> s;
int ans[MAXN];

int main(){
	int n; cin >> n;
	while(n--){
		int x, y; cin >> x >> y;
		s.emplace(x, y);
	}
	int t;
	cin >> t;
	ans[0] = s.size();
	int px = 0, py = 0, d = 2;
	for(int i=1; i<=t && i<=300000; i++){
		if(s.find(pi(px, py)) != s.end()){
			s.erase(pi(px, py));
			d = (d + 1) % 4;
		}
		else{
			s.insert(pi(px, py));
			d = (d + 3) % 4;
		}
		px += dx[d];
		py += dy[d];
		ans[i] = s.size();
	}
	if(t <= 300000) cout << ans[t] << endl;
	else{
		int v = (t - 300000) / 104 + 1;
		int pos = t - 104 * v;
		cout << ans[pos] + v * (ans[pos] - ans[pos - 104]) << endl;
	}
}
