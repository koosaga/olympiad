#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

vector<pi> v[MAXN];

int main(){
	lint w, h, r;
	cin >> w >> h >> r;
	lint ret = 0;
	for(lint i = 1; i <= r; i++){
		int d = (int)floor(sqrt(r*r-i*i));
		ret += 3 * d + 2;
	}
	for(lint i = 0; i <= h && i <= r-w; i++){
		int d = (int)floor(sqrt((r-w)*(r-w)-i*i));
		ret += d;
	}
	for(lint i = 1; i <= r-h; i++){
		int d = (int)floor(sqrt((r-h)*(r-h)-i*i));
		v[i].emplace_back(0, d);
	}
	for(lint i = h+1; i <= r-w; i++){
		int d = (int)floor(sqrt((r-w)*(r-w)-i*i));
		v[i-h].emplace_back(w, w + d);
	}
	for(int i = 1; i < MAXN; i++){
		for(auto &[x, y] : v[i]) ret += y - x + 1;
		if(sz(v[i]) == 2){
			int l = max(v[i][0].first, v[i][1].first);
			int r = min(v[i][0].second, v[i][1].second);
			if(l <= r) ret -= r - l + 1;
		}
	}
	cout << ret << endl;;
}
