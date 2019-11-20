#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 1005;
const int inf = 1e9 + 100;

int n, w, d;

bool in(int x, int y){
	return 0 <= x && x <= w && 0 <= y && y <= d;
}

int shoot(int x, int y, int dx, int dy){
	int s = 0, e = 1e6;
	while(s != e){
		int m = (s+e)/2;
		if(!in(x + dx * m, y + dy * m)) e = m;
		else s = m + 1;
	}
	s--;
	x += dx * s;
	y += dy * s;
	if(x == 0) return y;
	if(y == d) return x + d;
	if(x == w) return w + d + (d - y);
	return w + d + d + (w - x);
}

pi f(string s){
	if(s == "N") return pi(-1, -1);
	if(s == "E") return pi(-1, 1);
	if(s == "S") return pi(1, 1);
	return pi(1, -1);
}

pi g(string s){
	if(s == "N") return pi(-1, 1);
	if(s == "E") return pi(1, 1);
	if(s == "S") return pi(1, -1);
	return pi(-1, -1);
}

int main(){
	cin >> n >> w >> d;
	swap(w, d);
	int X = w + w + d + d;
	vector<pi> v;
	for(int i=0; i<n; i++){
		string s;
		int x, y; cin >> x >> y >> s;
		swap(x, y);
		x = w - x;
		int l = shoot(x, y, f(s).first, f(s).second);
		int r = shoot(x, y, g(s).first, g(s).second);
		if(l < r){
			v.emplace_back(l, r);
			v.emplace_back(l + X, r + X);
		}
		else v.emplace_back(l, r + X);
	}
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	int ans = 1e9;
	for(int i=0; i<sz(v); i++){
		int cur = v[i].first;
		int cnt = 1;
		if(cur >= X) continue;
		for(int j=0; j<sz(v); j++){
			if(v[j].second >= v[i].first + X) continue;
			if(v[j].first <= v[i].first) continue;
			if(cur < v[j].first){
				cur = v[j].second;
				cnt++;
			}
		}
		ans = min(ans, cnt);
	}
	cout << ans << endl;
}
