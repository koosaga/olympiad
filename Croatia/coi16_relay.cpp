#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct pnt{
	int first, second, idx;
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint ccw(pnt a, pnt b, pnt c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint dist(pnt a, pnt b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}

int n, m;
pi a[100005], b[100005];

void getch(vector<pnt> &v){
	swap(v[0], *min_element(v.begin(), v.end(), [&](const pnt &a, const pnt &b){
		return pi(a.first, a.second) < pi(b.first, b.second);
	}));
	sort(v.begin() + 1, v.end(), [&](const pnt &a, const pnt &b){
		lint k = ccw(v[0], a, b);
		if(k != 0) return k > 0;
		return dist(v[0], a) < dist(v[0], b);
	});
	vector<pnt> h;
	for(auto &i : v){
		while(h.size() >= 2 && ccw(h[h.size() - 2], h.back(), i) <= 0){
			h.pop_back();
		}
		h.push_back(i);
	}
	v = h;
}


int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	scanf("%d",&m);
	for(int i=0; i<m; i++) scanf("%d %d",&b[i].first,&b[i].second);
	int lp = 0, rp = 0;
	for(int i=1; i<m; i++){
		if(ccw(a[0], b[lp], b[i]) < 0) lp = i;
		if(ccw(a[0], b[rp], b[i]) > 0) rp = i;
	}
	vector<pnt> lv, rv;
	vector<pi> mv;
	for(int i=1; i<n; i++){
		if(ccw(a[0], b[lp], a[i]) <= 0){
			lv.push_back({a[i].first, a[i].second, -1});
		}
		if(ccw(a[0], b[rp], a[i]) >= 0){
			rv.push_back({a[i].first, a[i].second, -1});
		}
		if(ccw(a[0], b[lp], a[i]) > 0 && ccw(a[0], b[rp], a[i]) < 0 && ccw(b[lp], b[rp], a[i]) <= 0){
			mv.push_back(a[i]);
		}
	}
	for(int i=0; i<m; i++){
		lv.push_back({b[i].first, b[i].second, i});
		rv.push_back({b[i].first, b[i].second, i});
	}
	getch(lv);
	getch(rv);
	int ps = -1, pe = -1;
	pi ls, rs;
	for(int i=0; i<lv.size(); i++){
		if(lv[i].idx == -1 && lv[(i+1)%lv.size()].idx != -1){
			ls = pi(lv[i].first, lv[i].second);
			ps = lv[(i+1)%lv.size()].idx;
		}
	}
	for(int i=0; i<rv.size(); i++){
		if(rv[(i+1)%rv.size()].idx == -1 && rv[i].idx != -1){
			rs = pi(rv[(i+1)%rv.size()].first, rv[(i+1)%rv.size()].second);
			pe = rv[i].idx;
		}
	}
	int ans = 0;
	for(auto &i : mv){
		bool okps = (ps == -1);
		bool okpe = (pe == -1);
		if(!okpe && ccw(a[0], b[pe], i) < 0 && ccw(rs, b[pe], i) < 0) okpe = 1;
		if(!okps && ccw(a[0], b[ps], i) > 0 && ccw(ls, b[ps], i) > 0) okps = 1;
		if(okps && okpe) ans++;
	}
	cout << n - ans - 1;
}
