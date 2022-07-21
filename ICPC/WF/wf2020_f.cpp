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

llf query_tri(punkty a, punkty b, punkty c, lint t){
	lint area = abs(ccw(pi(a.x, a.y), pi(b.x, b.y), pi(c.x, c.y)));
	return area <=  t * hypotl(b.x - a.x, b.y - a.y);
}

int n, rev[MAXN], t;

int main(){
	scanf("%d %d",&n,&t);
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
		}
	}
	sort(event.begin(), event.end());
	int ret = 0;
	for(auto &i : event){
		if(i.is_query == 0){
			swap(rev[i.idx1], rev[i.idx2]);
			i.idx1 = rev[i.idx1];
			i.idx2 = rev[i.idx2];
			if(i.idx1 > i.idx2) swap(i.idx1, i.idx2);
			swap(a[i.idx1], a[i.idx2]);
			if(i.idx2 + 1 < n){
				int s = i.idx2, e = n - 1;
				while(s != e){
					int m = (s + e + 1) / 2;
					if(query_tri(a[i.idx1], a[i.idx2], a[m], t)) s = m;
					else e = m - 1;
				}
				ret = max(ret, s - i.idx1 + 1);
			}
			if(i.idx1 - 1 >= 0){
				int s = 0, e = i.idx1;
				while(s != e){
					int m = (s + e) / 2;
					if(query_tri(a[i.idx1], a[i.idx2], a[m], t)) e = m;
					else s = m + 1;
				}
				ret = max(ret, i.idx2 - s + 1);
			}
		}
	}
	cout << ret << "\n";
}


