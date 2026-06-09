#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
typedef long long lint;
typedef pair<int, int> pi;

double cur_pos;
int n;

int x[MAXN], y[MAXN], r[MAXN];

double func(int c) {
	int idx = c / 2;
	int t = c % 2;
	double dx = abs(x[idx] - cur_pos);
	double rr = (r[idx] - 0.001);
	double yy = sqrt(rr * rr - dx * dx);
	if (t == 0)
		return y[idx] - yy;
	return y[idx] + yy;
}

bool same(int a, int b) { return a == b; }

auto cmp = [](int a, int b) { return func(a) < func(b); };
set<int, decltype(cmp)> s(cmp);

struct event {
	int val;
	int pos, mode;
	bool operator<(const event &e) const { return pos == e.pos ? mode < e.mode : pos < e.pos; }
};

event v[4 * MAXN];
int vc = 0;

vector<pi> cnd;

bool ok(int p, int q) {
	if (x[p] + r[p] == x[q] - r[q])
		return 0;
	if (x[p] - r[p] == x[q] + r[q])
		return 0;
	int dx = x[p] - x[q];
	int dy = y[p] - y[q];
	int rr = r[p] + r[q];
	return 1ll * dx * dx + 1ll * dy * dy == 1ll * rr * rr;
}

lint solve_case() {
	vector<pi> lx, rx;
	for (int i = 0; i < n; i++) {
		lx.emplace_back(x[i] - r[i], y[i]);
		rx.emplace_back(x[i] + r[i], y[i]);
	}
	sort(lx.begin(), lx.end());
	sort(rx.begin(), rx.end());
	lint ans = 0;
	for (auto &i : lx) {
		if (binary_search(rx.begin(), rx.end(), i))
			ans++;
	}
	return ans;
}

lint solve(vector<pi> &v) {
	vector<pi> tmp;
	for (auto &i : v) {
		if (i.first == i.second)
			continue;
		if (i.first > i.second)
			swap(i.first, i.second);
		if (!ok(i.first, i.second))
			continue;
		tmp.push_back(i);
	}
	sort(tmp.begin(), tmp.end());
	tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
	return tmp.size();
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &x[i], &y[i], &r[i]);
		v[vc++] = {2 * i, x[i] - r[i], 1};
		v[vc++] = {2 * i + 1, x[i] - r[i], 1};
		v[vc++] = {2 * i, x[i] + r[i], 0};
		v[vc++] = {2 * i + 1, x[i] + r[i], 0};
	}
	sort(v, v + vc);
	for (int ii = 0; ii < vc; ii++) {
		auto &i = v[ii];
		if (i.mode == 0) {
			cur_pos = i.pos - 0.01;
			auto l = s.lower_bound(i.val);
			if (l == s.end() || !same(*l, i.val))
				l--;
			assert(same(*l, i.val));
			s.erase(l);
			l = s.lower_bound(i.val);
			int lidx = -1, ridx = -1;
			if (l != s.end()) {
				ridx = (*l) / 2;
			}
			if (l != s.begin()) {
				l--;
				lidx = (*l) / 2;
			}
			if (lidx != -1 && ridx != -1)
				cnd.emplace_back(lidx, ridx);
		} else {
			cur_pos = i.pos + 0.01;
			auto l = s.lower_bound(i.val);
			if (l != s.end()) {
				cnd.emplace_back(i.val / 2, (*l) / 2);
			}
			if (l != s.begin()) {
				l--;
				cnd.emplace_back(i.val / 2, (*l) / 2);
			}
			s.insert(i.val);
		}
	}
	cout << solve(cnd) + solve_case() << endl;
}