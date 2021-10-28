#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int main(){
	int n;
	scanf("%d",&n);
	vector<pi> a(n);
	for(auto &[x, y] : a) scanf("%d %d",&x,&y);
	sort(all(a));
	int ret = 0;
	for(int i = 0; i < n; i++){
		vector<pi> v;
		for(int j = i+1; j < n; j++){
			v.emplace_back(a[j].first - a[i].first, a[j].second - a[i].second);
		}
		sort(all(v), [&](const pi &a, const pi &b){
			return ccw(pi(0, 0), a, b) > 0;
		});
		for(int i = 0; i + 1 < sz(v); i++){
			int nxt = i + 1; 
			ret++;
			for(int j = i + 2; j < sz(v); j++){
				if(ccw(v[i], v[nxt], v[j]) > 0){
					nxt = j;
					ret++;
				}
			}
		}
	}
	cout << 1ll * n * (n - 1) * (n - 2) / 6 - ret << endl;
}
