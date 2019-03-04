#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n;
pi a[1005];

int gcd(int x, int y){ return y ? gcd(y, x%y) : x; }

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int linecase(){
	sort(a, a+n);
	vector<tuple<int, int, int>> v;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			int dx = a[i].first - a[j].first;
			int dy = a[i].second - a[j].second;
			tie(dx, dy) = pi(-dy, dx);
			if(pi(dx, dy) < pi(0, 0)) tie(dx, dy) = pi(-dx, -dy);
			int g = gcd(dx, abs(dy));
			dx /= g;
			dy /= g;
			int p = (a[i].first + a[j].first) / 2;
			int q = (a[i].second + a[j].second) / 2;
			v.emplace_back(dx, dy, p * dy - q * dx);
		}
	}
	int ans = n;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			int tmp = n;
			for(int k=0; k<n; k++){
				if(ccw(a[i], a[j], a[k]) == 0) tmp--;
			}
			ans = min(ans, tmp);
		}
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i] == v[e]) e++;
		int dx, dy, av;
		tie(dx, dy, av) = v[i];
		int tmp = n - 2 * e + 2 * i;
		for(int k=0; k<n; k++){
			if(dy * a[k].first - dx * a[k].second == av) tmp--;
		}
		ans = min(ans, tmp);
		i = e;
	}
	return ans;
}

int pointcase(){
	vector<pi> p, q, r;
	for(int i=0; i<n; i++) p.push_back(a[i]);
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			q.push_back(pi(a[i].first + a[j].first, a[i].second + a[j].second));
			q.back().first /= 2;
			q.back().second /= 2;
		}
	}
	for(auto &i : p) r.push_back(i);
	for(auto &i : q) r.push_back(i);
	sort(p.begin(), p.end());
	sort(q.begin(), q.end());
	sort(r.begin(), r.end());
	r.resize(unique(r.begin(), r.end()) - r.begin());
	int ans = n;
	for(auto &i : r){
		int stabp = upper_bound(p.begin(), p.end(), i) - lower_bound(p.begin(), p.end(), i);
		int stabm = upper_bound(q.begin(), q.end(), i) - lower_bound(q.begin(), q.end(), i);
		ans = min(ans, n - stabp - 2 * stabm);
	}
	return ans;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		a[i].first *= 2;
		a[i].second *= 2;
	}
	cout << min(pointcase(), linecase());
}
