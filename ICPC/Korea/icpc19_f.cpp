#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())

struct sweep{
	int dx, dy, idx1, idx2;
	int mode(){
		return pi(dx, dy) < pi(0, 0);
	}
	bool operator<(const sweep &s)const{
		lint k = 1ll * dx * s.dy - 1ll * dy * s.dx;
		if(k != 0) return k > 0;
		return pi(idx1, idx2) < pi(s.idx1, s.idx2);
	}
};

lint ccw(sweep a, sweep b){
	return 1ll * a.dx * b.dy - 1ll * b.dx * a.dy;
}

struct point{
	int x, y;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[1005];

lint ccw(point x, point y, point z){
	y.x -= x.x;
	y.y -= x.y;
	z.x -= x.x;
	z.y -= x.y;
	return 1ll * y.x * z.y - 1ll * y.y * z.x;
}

int bh(lint x){
	assert(x != 0);
	return x > 0 ? 1 : -1;
}

bool is_convex(point x, point y, point z, point w){
	return bh(ccw(x, y, z)) * bh(ccw(x, y, w)) < 0 && bh(ccw(z, w, x)) * bh(ccw(z, w, y)) < 0;
}

int n, rev[1005];
vector<sweep> v;

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i].x >> a[i].y;
	sort(a, a+n);
	iota(rev, rev + n, 0);
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			v.push_back({a[j].x - a[i].x, a[j].y - a[i].y, i, j});
		}
	}
	sort(v.begin(), v.end());
	lint ret = 0;
	lint cur = 9e18;
	lint minDap = 0;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && ccw(v[i], v[e]) == 0) e++;
		for(int j=i; j<e; j++){
			int rx = rev[v[j].idx1], ry = rev[v[j].idx2];
			if(rx > ry) swap(rx, ry);
			assert(rx + 1 == ry);
			swap(rev[v[j].idx1], rev[v[j].idx2]);
			swap(a[rx], a[ry]);
			ret += 1ll * rx * (n - ry - 1);
			lint minL = (rx > 0 ? abs(ccw(a[rx], a[rx + 1], a[rx - 1])) : -1);
			lint minR = abs(ccw(a[rx], a[rx + 1], a[rx + 2]));
			vector<point> cndl, cndr;
			for(int j=rx-1; j>=0; j--){
				lint val = abs(ccw(a[rx], a[rx + 1], a[j]));
				if(val == minL) cndl.push_back(a[j]);
				else break;
			}
			for(int j=rx+2; j<n; j++){
				lint val = abs(ccw(a[rx], a[rx + 1], a[j]));
				if(val == minR) cndr.push_back(a[j]);
				else break;
			}
			for(auto &i : cndl){
				for(auto &j : cndr){
					if(cur > minL + minR){
						cur = minL + minR;
						minDap = 0;
					}
					if(cur == minL + minR){
						minDap += 1 + (!is_convex(a[rx], a[rx + 1], i, j));
					}
				}
			}
		}
		i = e;
	}
	cout << ret + minDap << endl;
}

