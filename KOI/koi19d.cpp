#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct punkty{
	int x, y, idx;
}a[MAXN];

struct droga{
	bool is_query;
	pi vect;
	int idx1, idx2;
	bool operator<(const droga &x)const{
		lint k = ccw(pi(0, 0), vect, x.vect);
		if(k != 0) return k > 0;
		if(is_query != x.is_query) return is_query < x.is_query;
		return pi(idx1, idx2) < pi(x.idx1, x.idx2);
	}
};

llf query_tri(punkty a, punkty b, punkty c){
	lint area = abs(ccw(pi(a.x, a.y), pi(b.x, b.y), pi(c.x, c.y)));
	return 0.5L * area / hypotl(b.x - a.x, b.y - a.y);
}

int n, rev[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y;
	}
	sort(a, a + n, [&](const punkty &a, const punkty &b){
		return pi(a.x, a.y) < pi(b.x, b.y);
	});
	for(int i=0; i<n; i++){
		a[i].idx = i;
		rev[i] = i;
	}
	vector<droga> event;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			event.push_back({0, pi(a[j].x - a[i].x, a[j].y - a[i].y), i, j});
			if(a[j].y > a[i].y){
				event.push_back({1, pi(a[j].y - a[i].y, a[i].x - a[j].x), i, j});
			}
			else{
				event.push_back({1, pi(a[i].y - a[j].y, a[j].x - a[i].x), i, j});
			}
		}
	}
	sort(event.begin(), event.end());
	llf ret = 0;
	for(auto &i : event){
		if(i.is_query == 0){
			swap(rev[i.idx1], rev[i.idx2]);
			i.idx1 = rev[i.idx1];
			i.idx2 = rev[i.idx2];
			if(i.idx1 > i.idx2) swap(i.idx1, i.idx2);
			swap(a[i.idx1], a[i.idx2]);
			if(i.idx2 + 1 <  n) ret = max(ret, query_tri(a[i.idx1], a[i.idx2], a[i.idx2 + 1]));
			if(i.idx1 - 1 >= 0) ret = max(ret, query_tri(a[i.idx1], a[i.idx2], a[i.idx1 - 1]));
		}
		else{
			i.idx1 = rev[i.idx1];
			i.idx2 = rev[i.idx2];
			if(i.idx1 > i.idx2) swap(i.idx1, i.idx2);
			int st = i.idx1, ed = i.idx2;
			lint base_value = ccw(pi(0, 0), i.vect, pi(a[i.idx1].x, a[i.idx1].y));
			while(st != ed){
				int m = (st + ed) / 2;
				if(ccw(pi(0, 0), i.vect, pi(a[m].x, a[m].y)) != base_value) ed = m;
				else st = m + 1;
			}
			if(ccw(pi(0, 0), i.vect, pi(a[i.idx2].x - a[st].x, a[i.idx2].y - a[st].y)) == 0){
				ret = max(ret, 0.5L * hypotl(a[i.idx2].x - a[i.idx1].x, a[i.idx2].y - a[i.idx1].y));
			}
		}
	}
	printf("%.10Lf\n", ret);
}

