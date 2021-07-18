#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint dist(pi a, pi b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return 1ll * dx * dx + 1ll * dy * dy;
}

bool awkward(pi s1, pi e1, pi s2, pi e2){
	return ccw(pi(0, 0), pi(e1.first - s1.first, e1.second - s1.second),
			pi(e2.first - s2.first, e2.second - s2.second)) > 0;
}

int n;
pi a[400005];

int main(){
	int t;
	cin >> t;
	while(t--){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			int x, y, w; scanf("%d %d %d",&x,&y,&w);
			a[4*i+0] = pi(x, y);
			a[4*i+1] = pi(x, y+w);
			a[4*i+2] = pi(x+w, y);
			a[4*i+3] = pi(x+w, y+w);
		}
		n *= 4;
		sort(a, a + n);
		n = unique(a, a + n) - a;
		sort(a+1, a+n, [&](const pi &p, const pi &q){
			auto w = ccw(a[0], p, q);
			if(w != 0) return w > 0;
			return dist(a[0], p) < dist(a[0], q);
		});
		vector<pi> hull;
		for(int i=0; i<n; i++){
			while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), a[i]) <= 0){
				hull.pop_back();
			}
			hull.push_back(a[i]);
		}
		int p = 0;
		lint ret = -1; pi p1, p2;
		for(int i=0; i<hull.size(); i++){
			while(awkward(hull[i], hull[(i+1)%hull.size()], hull[p], hull[(p+1)%hull.size()])){
				auto k = dist(hull[i], hull[p]);
				if(k > ret){
					ret = k;
					p1 = hull[i], p2 = hull[p];
				}
				p++;
				if(p == hull.size()) p = 0;
			}
			auto k = dist(hull[i], hull[p]);
			if(k > ret){
				ret = k;
				p1 = hull[i], p2 = hull[p];
			}
		}
		cout << ret << endl;
	}
}

