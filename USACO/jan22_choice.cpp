#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

lint dot(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

lint dist(pi a, pi b){
	return dot(a, b, b);
}

lint ccw(pi a, pi b, pi c){
	lint dx1 = b.first - a.first;
	lint dy1 = b.second - a.second;
	lint dx2 = c.first - a.first;
	lint dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

pi operator+(pi a, pi b){
	return pi(a.first + b.first, a.second + b.second);
}


pi operator-(pi a, pi b){
	return pi(a.first - b.first, a.second - b.second);
}

pi rot90(pi a){
	return pi(-a.second, a.first);
}

lint ccw(pi a, pi b){
	return ccw(pi(0, 0), a, b);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	pi cur(0, 0);	
	vector<pair<pi, pi>> ev;
	const pi dir = pi(1, -1e9 - 1);
	for(int i = 0; i < n; i++){
		int m; cin >> m;
		vector<pi> v(m);
		for(auto &[x, y] : v) cin >> x >> y;
		swap(v[0], *min_element(all(v)));
		sort(v.begin() + 1, v.end(), [&](const pi &a, const pi &b){
			lint q = ccw(v[0], a, b);
			if(q != 0) return q > 0;
			return dist(v[0], a) < dist(v[0], b);
		});
		vector<pi> h;
		for(auto &p : v){
			while(sz(h) >= 2 && ccw(h[sz(h) - 2], h.back(), p) <= 0) h.pop_back();
			h.push_back(p);
		}
		for(int i = 0; i < sz(h); i++){
			pi C = h[(i + sz(h) - 1) % sz(h)];
			pi A = h[i];
			pi B = h[(i + 1) % sz(h)];
			pi start = rot90(C - A);
			pi end = rot90(A - B);
			assert(ccw(start, end) >= 0);
			if(ccw(start, dir) >= 0 && ccw(dir, end) > 0){
				cur = cur + h[i];
				ev.emplace_back(end, pi(0, 0) - h[i]);
				if(ccw(start, dir) > 0) ev.emplace_back(start, h[i]);
			}
			else{
				ev.emplace_back(start, h[i]);
				ev.emplace_back(end, pi(0, 0) - h[i]);
			}
		}
	}
	sort(all(ev), [&](const pair<pi, pi> &a, const pair<pi, pi> &b){
			int bh0 = (a.first < pi(0, 0));
			int bh1 = (b.first < pi(0, 0));
			if(bh0 != bh1) return bh0 < bh1;
			return ccw(a.first, b.first) > 0;
			});
	lint ans = dist(pi(0, 0), cur);
	for(int i = 0; i < sz(ev); ){
		int j = i;
//		printf("Gakdo = %lld %lld\n", ev[i].first.first, ev[i].first.second);
		while(j < sz(ev) && ccw(ev[i].first, ev[j].first) == 0 && dot(pi(0, 0), ev[i].first, ev[j].first) >= 0){
//			printf("Add %lld %lld\n", ev[j].second.first, ev[j].second.second);
			cur = cur + ev[j++].second;
		}
//		printf("Cur = %lld %lld\n", cur.first, cur.second);
		ans = max(ans, dist(pi(0, 0), cur));
		i = j;
	}
	cout << ans << "\n";
}

