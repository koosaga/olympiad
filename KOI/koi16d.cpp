#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, t, x[30005], y[30005], dx[30005], dy[30005];
pi a[30005];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint dist(pi a, pi b){
	return 1ll * (b.first - a.first) * (b.first - a.first) + 1ll * (b.second - a.second) * (b.second - a.second);
}

bool awkward(pi s1, pi e1, pi s2, pi e2){
	return ccw(pi(0, 0), pi(e1.first - s1.first, e1.second - s1.second), 
			pi(e2.first - s2.first, e2.second - s2.second)) >= 0;
}

lint trial(int t){
	for(int i=0; i<n; i++){
		a[i] = pi(x[i] + dx[i] * t, y[i] + dy[i] * t);
	}
	swap(a[0], *min_element(a, a+n));
	sort(a+1, a+n, [&](const pi &p, const pi &q){
		lint t = ccw(a[0], p, q);
		if(t != 0) return t > 0;
		return dist(a[0], p) < dist(a[0], q);
	});
	vector<pi> hull;
	for(int i=0; i<n; i++){
		while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), a[i]) <= 0){
			hull.pop_back();
		}
		hull.push_back(a[i]);
	}
	lint ret = 0;
	int p = 0;
	for(int i=0; i<hull.size(); i++){
		while(p+1 < hull.size() && awkward(hull[i], hull[i+1], hull[p], hull[p+1])){
			ret = max(ret, dist(hull[i], hull[p]));
			p++;
		}
		ret = max(ret, dist(hull[i], hull[p]));
	}
	return ret;
}

int main(){
	cin >> n >> t;
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&x[i],&y[i],&dx[i],&dy[i]);
	}
	int s = 0, e = t;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m) <= trial(m+1)) e = m;
		else s = m+1;
	}
	cout << s << endl << trial(s) << endl;
}
