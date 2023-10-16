#include <bits/stdc++.h>
using namespace std;
#define HAS(msk, x) (((msk) >> (x)) & 1)
const int MAXN = 250005;
using lint = long long;
using pi = pair<lint, lint>;

struct cht{
	bool ccw(pi a, pi b, pi c){
		return (a.second - b.second) * (c.first - b.first) >= (b.second - c.second) * (b.first - a.first);
	}
	vector<pi> v;
	void add(lint x, lint y){
		if(v.size() && v.back().first == x){
			y = max(y, v.back().second);
			v.pop_back();
		}
		while(v.size() >= 2 && ccw(v[v.size() - 2], v.back(), pi(x, y))){
			v.pop_back();
		}
		v.emplace_back(x, y);
	}
	lint query(lint x){
		while(v.size() >= 2){
		    auto prv = v[v.size() - 2];
		    auto nxt = v.back();
		    if(prv.first * x + prv.second < nxt.first * x + nxt.second) break;
		    v.pop_back();
		}
		if(v.empty()) return -2e18;
		return v.back().first * x + v.back().second;
	}
}cht;

int n;
pi a[MAXN];

int main(){
	cin >> n;
	lint sumS = 0;
	lint sumFS = 0;
	for(int i=0; i<n; i++){
		scanf("%lld %lld",&a[i].first,&a[i].second);
		if(a[i].first > a[i].second) swap(a[i].first, a[i].second);
		sumS += a[i].second;
		sumFS += 1ll * a[i].first * a[i].second;
	}
	sort(a, a + n, [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	lint dap = 0;
	for(int i=0; i<n; i++){
		dap = max(dap, cht.query(sumS - a[i].second) - sumFS + 1ll * a[i].first * a[i].second);
		cht.add(a[i].second, -1ll * a[i].second * a[i].second + 1ll * a[i].first * a[i].second);
	}
	cout << dap << endl;
}

