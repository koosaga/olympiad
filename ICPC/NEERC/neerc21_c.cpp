#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	vector<int> vx, vy;
	vector<pi> p(3);
	vector<tuple<int, int, int, int>> ans;
	auto Do = [&](int sx, int sy, int ex, int ey){
		if(sx == ex && sy == ey) return;
		ans.emplace_back(sx, sy, ex, ey);
	};
	for(auto &[x, y] : p){
		cin >> x >> y;
		vx.push_back(x);
		vy.push_back(y);
	}
	sort(all(vx));
	sort(all(vy));
	sort(all(p));
	Do(vx[1], vy[0], vx[1], vy[2]);
	if(p[0].first < p[1].first) Do(p[0].first, p[0].second, p[1].first, p[0].second);
	if(p[1].first < p[2].first) Do(p[1].first, p[2].second, p[2].first, p[2].second);
	cout << sz(ans) << "\n";
	for(auto &[p, q, r, s] : ans) cout << p << " " << q << " " << r << " " << s << "\n";
	return 0;
}
