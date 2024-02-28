#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

long long play_game(long long N, int Q, long long K, vector<long long> Lv, vector<long long> Rv) {
	N = (N / K + 1) * K;
	vector<pi> events;
	vector<lint> crd = {0, K};
	for (auto &x : Lv) {
		crd.push_back(x % K);
		events.push_back({x, +1});
	}
	for (auto &x : Rv) {
		crd.push_back((x + 1) % K);
		events.push_back({x + 1, -1});
	}
	events.push_back({0, 0});
	events.push_back({N, 0});
	sort(all(events));
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	vector<array<lint, 5>> strips;
	int cnt = 0;
	for (int i = 0; i < sz(events);) {
		int j = i;
		while (j < sz(events) && events[j][0] == events[i][0]) {
			cnt += events[j++][1];
		}
		if (j < sz(events)) {
			lint l = events[i][0];
			lint r = events[j][0];
			if (l / K == r / K) {
				strips.push_back({l / K, l / K, l % K, r % K, cnt});
			} else {
				strips.push_back({l / K, l / K, l % K, K, cnt});
				if (l / K + 1 < r / K)
					strips.push_back({l / K + 1, r / K - 1, 0, K, cnt});
				if (r % K > 0)
					strips.push_back({r / K, r / K, 0, r % K, cnt});
			}
		}
		i = j;
	}
	sort(all(strips));
	for (auto &[l1, r1, l2, r2, v] : strips) {
		l2 = lower_bound(all(crd), l2) - crd.begin();
		r2 = lower_bound(all(crd), r2) - crd.begin();
	}
	map<lint, lint> mp;
	lint L = 0;
	lint R = 0;
	for (int i = 0; i < sz(strips); i++) {
		if (strips[i][0] != strips[i][1]) {
			L += strips[i][4] * (strips[i][1] - strips[i][0] + 1);
			R += strips[i][4] * (strips[i][1] - strips[i][0] + 1);
			while (R - L > strips[i][4]) {
				auto [x, y] = *mp.begin();
				mp.erase(mp.begin());
				lint d = min(R - L - strips[i][4], y);
				y -= d;
				L += d;
				if (y > 0) {
					mp[x] = y;
					break;
				}
			}
		} else {
			int j = i;
			while (j < sz(strips) && strips[j][0] == strips[i][0])
				j++;
			assert(strips[j - 1][0] == strips[j - 1][1]);
			lint Y = R - L;
			L += Y;
			R += Y;
			for (int k = i; k < j; k++) {
				if (strips[k][4] > Y) {
					mp[strips[k][2]] += strips[k][4] - Y;
					R += strips[k][4] - Y;
					Y = 0;
				} else {
					Y -= strips[k][4];
					auto it = mp.lower_bound(strips[k][2]);
					while (Y > 0 && (it != mp.end() && it->first < strips[k][3])) {
						auto [x, y] = *it;
						it = mp.erase(it);
						lint d = min(y, Y);
						Y -= d;
						y -= d;
						R -= d;
						if (y > 0) {
							mp[x] = y;
							break;
						}
					}
				}
				Y += strips[k][4];
			}
			i = j - 1;
		}
	}
	return R;
}
