#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXT = 270000;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int n;
lint sfx[MAXN], pfx[MAXN];
pi a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a + 1, a + n + 1);
	vector<pi> lh, rh;
	lint la = 0, ra = 0;
	for(int i=1; i<=n; i++){
		while(lh.size() >= 2 && ccw(lh[lh.size()-2], lh.back(), a[i]) <= 0){
			la -= ccw(lh[0], lh[lh.size()-2], lh.back());
			lh.pop_back();
		}
		while(rh.size() >= 2 && ccw(rh[rh.size()-2], rh.back(), a[i]) >= 0){
			ra -= ccw(rh[0], rh[rh.size()-2], rh.back());
			rh.pop_back();
		}
		lh.push_back(a[i]);
		rh.push_back(a[i]);
		if(lh.size() > 2){
			la += ccw(lh[0], lh[lh.size()-2], lh.back());
		}
		if(rh.size() > 2){
			ra += ccw(rh[0], rh[rh.size()-2], rh.back());
		}
		pfx[i] = abs(la) + abs(ra);
	}
	lh.clear();
	rh.clear();
	la = ra = 0;
	for(int i=n; i; i--){
		while(lh.size() >= 2 && ccw(lh[lh.size()-2], lh.back(), a[i]) >= 0){
			la -= ccw(lh[0], lh[lh.size()-2], lh.back());
			lh.pop_back();
		}
		while(rh.size() >= 2 && ccw(rh[rh.size()-2], rh.back(), a[i]) <= 0){
			ra -= ccw(rh[0], rh[rh.size()-2], rh.back());
			rh.pop_back();
		}
		lh.push_back(a[i]);
		rh.push_back(a[i]);
		if(lh.size() > 2){
			la += ccw(lh[0], lh[lh.size()-2], lh.back());
		}
		if(rh.size() > 2){
			ra += ccw(rh[0], rh[rh.size()-2], rh.back());
		}
		sfx[i] = abs(la) + abs(ra);
	}
	a[0].first = a[1].first - 1;
	a[n+1].first = a[n].first + 1;
	lint ret = 8.5e18;
	for(int i=0; i<=n; i++){
		if(a[i].first != a[i+1].first) ret = min(ret, pfx[i] + sfx[i + 1]);
	}
	cout << (ret + 1) / 2 << endl;
}
