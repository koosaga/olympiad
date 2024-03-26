#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 800005;

struct bit {
	lint tree[MAXN];
	void add(int x, lint v) {
		for (int i = x; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	lint query(int x) {
		lint ret = 0;
		for (int i = x; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

vector<lint> play_game(long long K, vector<array<lint, 3>> intvs, vector<array<lint, 2>> queries) {
	vector<pi> events;
	vector<lint> crd = {0, K};

	for (auto &[l, r, v] : intvs) {
		crd.push_back(l % K);
		crd.push_back((r + 1) % K);
		events.push_back({l, +v});
		events.push_back({r + 1, -v});
	}
	events.push_back({0, 0});
	events.push_back({(lint(4e12) / K) * K, 0});
	sort(all(events));
	vector<array<lint, 5>> strips;
	lint cnt = 0;
	vector<lint> ans(sz(queries));
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
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
	for (auto &[l1, r1, l2, r2, v] : strips) {
		l2 = lower_bound(all(crd), l2) - crd.begin();
		r2 = lower_bound(all(crd), r2) - crd.begin();
	}

	sort(all(strips));
	map<lint, lint> mp;
	lint L = 0;
	lint R = 0;
	int p = 0;
	for (int i = 0; i < sz(strips); i++) {
		if (strips[i][0] != strips[i][1]) {
			while (R - L > strips[i][4]) {
				auto [x, y] = *mp.begin();
				bit.add(x + 1, -y);
				mp.erase(mp.begin());
				lint d = min(R - L - strips[i][4], y);
				y -= d;
				L += d;
				if (y > 0) {
					bit.add(x + 1, y);
					mp[x] = y;
					break;
				}
			}
			while (p < sz(queries) && queries[p][0] < strips[i][1] * K + K) {
				ans[queries[p][1]] = L + (queries[p][0] / K - strips[i][0] + 1) * strips[i][4];
				int j = upper_bound(all(crd), queries[p][0] % K) - crd.begin();
				ans[queries[p][1]] += bit.query(j);
				p++;
			}
			L += strips[i][4] * (strips[i][1] - strips[i][0] + 1);
			R += strips[i][4] * (strips[i][1] - strips[i][0] + 1);
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
					bit.add(strips[k][2] + 1, strips[k][4] - Y);
					mp[strips[k][2]] += strips[k][4] - Y;
					R += strips[k][4] - Y;
					Y = 0;
				} else {
					Y -= strips[k][4];
					auto it = mp.lower_bound(strips[k][2]);
					while (Y > 0 && (it != mp.end() && it->first < strips[k][3])) {
						auto [x, y] = *it;
						bit.add(x + 1, -y);
						it = mp.erase(it);
						lint d = min(y, Y);
						Y -= d;
						y -= d;
						R -= d;
						if (y > 0) {
							bit.add(x + 1, y);
							mp[x] = y;
							break;
						}
					}
				}
				Y += strips[k][4];
			}
			while (p < sz(queries) && queries[p][0] < strips[j - 1][1] * K + K) {
				ans[queries[p][1]] = L;
				int j = upper_bound(all(crd), queries[p][0] % K) - crd.begin();
				ans[queries[p][1]] += bit.query(j);
				p++;
			}
			i = j - 1;
		}
	}
	while (p < sz(queries))
		ans[queries[p++][1]] = R;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	lint D, A, B;
	cin >> n >> q >> D >> A >> B;
	vector<pi> a(n);
	for (auto &[x, y] : a) {
		cin >> x >> y;
	}
	vector<pi> query(q);
	for (int i = 0; i < q; i++) {
		cin >> query[i][0];
		query[i][1] = i;
	}
	sort(all(query));
	vector<pi> invs;
	invs.push_back({0, a[0][0] - 1});
	for (int i = 1; i < n; i++) {
		invs.push_back({a[i - 1][1] + 1, a[i][0] - 1});
	}
	invs.push_back({a[n - 1][1] + 1, lint(2e12)});
	vector<pi> nxt;
	nxt.push_back(invs[0]);
	int j = 0;
	for (int i = 1; i < sz(invs); i++) {
		while (j < sz(nxt) && nxt[j][1] < invs[i][0] - D)
			j++;
		if (j < sz(nxt) && nxt.back()[1] >= invs[i][0] - D) {
			invs[i][0] = max(invs[i][0], nxt[j][0] + D);
			if (invs[i][0] <= invs[i][1])
				nxt.push_back(invs[i]);
		}
	}
	invs = nxt;
	if (B >= A * D) {
		{
			vector<pi> nxt;
			nxt.push_back(invs[0]);
			int j = 0;
			for (int i = 1; i < sz(invs); i++) {
				while (j < sz(nxt) && nxt[j][1] < invs[i][0] - D)
					j++;
				if (j < sz(nxt) && nxt.back()[1] >= invs[i][0] - D) {
					invs[i][0] = max(invs[i][0], nxt[j][0] + D);
					if (invs[i][0] <= invs[i][1])
						nxt.push_back(invs[i]);
				}
			}
			invs = nxt;
		}
		vector<lint> dp(sz(invs));
		int j = 0;
		for (int i = 1; i < sz(dp); i++) {
			while (invs[j][1] < invs[i][0] - D) {
				j++;
			}
			assert(j < i);
			dp[i] = dp[j] + 1;
		}
		j = 0;
		vector<lint> ans(q);
		for (auto &[qp, idx] : query) {
			while (j + 1 < sz(invs) && invs[j + 1][0] <= qp)
				j++;
			if (invs[j][1] >= qp && invs[j][0] <= qp) {
				ans[idx] = qp * A + (B - A * D) * dp[j];
			} else
				ans[idx] = -1;
		}
		for (int i = 0; i < q; i++) {
			cout << ans[i] << "\n";
		}
		return 0;
	}
	j = 0;
	vector<array<lint, 3>> intvs;
	for (int i = 0; i < sz(invs); i++) {
		intvs.push_back({invs[i][0] + D, invs[i][1] + D, +1});
		j = max(j, i + 1);
		while (j < sz(invs) && invs[j][1] < invs[i][0] + D)
			j++;
		for (int k = j; k < sz(invs); k++) {
			if (invs[k][0] > invs[i][1] + D)
				break;
			lint is = max(invs[i][0], invs[k][0] - D);
			lint ie = min(invs[i][1], invs[k][1] - D);
			if (is <= ie)
				intvs.push_back({is + D, ie + D, (k - i) * lint(2e12)});
		}
	}
	auto jumpgame = play_game(D, intvs, query);
	j = 0;
	vector<lint> ans(q);
	for (auto &[qp, idx] : query) {
		while (j + 1 < sz(invs) && invs[j + 1][0] <= qp)
			j++;
		if (invs[j][1] >= qp && invs[j][0] <= qp && jumpgame[idx] / lint(2e12) == j) {
			ans[idx] = qp * A + (B - A * D) * (jumpgame[idx] % lint(2e12));
		} else
			ans[idx] = -1;
	}
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
}