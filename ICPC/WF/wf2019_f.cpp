#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1010101;

int pos;
struct line {
	pi s, e;
	int idx;
	const double incep() const {
		double d = 1.0 * (pos - s[0]) / (e[0] - s[0]);
		return s[1] + d * (e[1] - s[1]);
	}
	bool operator<(const line &l) const { return incep() < l.incep(); }
};

vector<int> gph[MAXN];
int indeg[MAXN];

vector<int> toposort(int n) {
	queue<int> que;
	vector<int> idx(n);
	for (int i = 0; i < n; i++) {
		if (!indeg[i])
			que.push(i);
	}
	int cnt = 0;
	while (sz(que)) {
		int x = que.front();
		que.pop();
		idx[x] = cnt++;
		for (auto &y : gph[x]) {
			indeg[y]--;
			if (indeg[y] == 0)
				que.push(y);
		}
	}
	return idx;
}

vector<array<int, 4>> read_lines(int n) {
	vector<line> a(n);
	vector<array<lint, 3>> event;
	for (int i = 0; i < n; i++) {
		cin >> a[i].s[0] >> a[i].s[1] >> a[i].e[0] >> a[i].e[1];
		a[i].idx = i;
		if (a[i].s[0] > a[i].e[0])
			swap(a[i].s, a[i].e);
		event.push_back({a[i].s[0], i, +1});
		event.push_back({a[i].e[0], i, -1});
	}
	auto addEdge = [&](int a, int b) {
		gph[a].push_back(b);
		indeg[b]++;
	};
	set<line> s;
	sort(all(event));
	for (auto &[ipos, i, type] : event) {
		pos = ipos;
		if (type == 1) {
			s.insert(a[i]);
			auto z = s.lower_bound(a[i]);
			for (int i = 0; i < 3; i++) {
				if (z != s.begin())
					z--;
			}
			while (z->idx != i)
				z++;
			if (z != s.begin()) {
				addEdge(prev(z)->idx, i);
			}
			if (next(z) != s.end()) {
				addEdge(i, next(z)->idx);
			}
		} else {
			auto z = s.lower_bound(a[i]);
			for (int i = 0; i < 3; i++) {
				if (z != s.begin())
					z--;
			}
			while (z->idx != i)
				z++;
			auto it = s.erase(z);
			if (it != s.begin() && it != s.end()) {
				addEdge(prev(it)->idx, it->idx);
			}
		}
	}
	auto rev = toposort(n);
	vector<array<int, 4>> b(n);
	for (int i = 0; i < n; i++) {
		b[i][0] = rev[i] + 1;
		b[i][3] = (a[i].s[1] < a[i].e[1]);
		b[i][1] = a[i].s[0];
		b[i][2] = a[i].e[0];
	}
	return b;
}

struct bit {
	lint tree[MAXN];
	void add(int s, int e, lint v) {
		for (int i = s + 3; i < MAXN; i += i & -i)
			tree[i] += v;
		for (int i = e + 4; i < MAXN; i += i & -i)
			tree[i] -= v;
	}
	lint query(lint x) {
		lint ret = 0;
		for (int i = x + 3; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int l, r, n;
	cin >> l >> r >> n;
	vector<int> vect = {-int(2e9), l, r, int(2e9)};
	vector<array<int, 4>> a = read_lines(n);
	for (auto &[_, y1, y2, __] : a) {
		vect.push_back(y1);
		vect.push_back(y2);
	}
	sort(all(vect));
	vect.resize(unique(all(vect)) - vect.begin());
	l = lower_bound(all(vect), l) - vect.begin();
	r = lower_bound(all(vect), r) - vect.begin();
	for (auto &[_, y1, y2, __] : a) {
		y1 = lower_bound(all(vect), y1) - vect.begin();
		y2 = lower_bound(all(vect), y2) - vect.begin();
	}
	bit.add(0, l - 1, 1e9);
	bit.add(r + 1, sz(vect) - 1, 1e9);
	sort(all(a));
	reverse(all(a));
	set<int> ups, dns; // ups : dp[i] < dp[i + 1], dns : dp[i] > dp[i + 1]
	ups.insert(r);
	dns.insert(l - 1);
	for (auto &[_, y1, y2, type] : a) {
		if (type == 0) {
			auto it = ups.lower_bound(y1 + 1);
			while (it != ups.end() && *it <= y2) {
				int d = bit.query(*it + 1) - bit.query(*it);
				int nxt = (next(it) != ups.end() ? *next(it) : 1e9);
				nxt = min(nxt, y2);
				auto it2 = dns.lower_bound(*it + 1);
				while (it2 != dns.end() && *it2 <= nxt) {
					int e = bit.query(*it2) - bit.query(*it2 + 1);
					int dx = min(d, e);
					bit.add(*it + 1, *it2, -dx);
					d -= dx;
					e -= dx;
					if (e == 0)
						it2 = dns.erase(it2);
					else
						break;
				}
				if (d > 0) {
					bit.add(*it + 1, nxt, -d);
				}
				it = ups.erase(it);
			}
			bit.add(y1 + 1, y2 - 1, 1);
		}
		if (type == 1) {
			auto it = dns.lower_bound(y2 - 1);
			while (it != dns.begin() && *prev(it) >= y1) {
				it--;
				int d = bit.query(*it) - bit.query(*it + 1);
				int nxt = (it != dns.begin() ? *prev(it) : -1e9);
				nxt = max(nxt, y1 - 1);
				auto it2 = ups.lower_bound(*it);
				while (it2 != ups.begin() && *prev(it2) >= nxt) {
					it2--;
					int e = bit.query(*it2 + 1) - bit.query(*it2);
					int dx = min(d, e);
					bit.add(*it2 + 1, *it, -dx);
					d -= dx;
					e -= dx;
					if (e == 0)
						it2 = ups.erase(it2);
					else
						break;
				}
				if (d > 0) {
					bit.add(nxt + 1, *it, -d);
				}
				it = dns.erase(it);
			}
			bit.add(y1 + 1, y2 - 1, 1);
		}
		for (auto &z : {y1 - 1, y1, y2 - 1, y2}) {
			if (z < 0 || z + 1 >= sz(vect))
				continue;
			if (dns.count(z))
				dns.erase(z);
			if (ups.count(z))
				ups.erase(z);
			lint b1 = bit.query(z + 1) - bit.query(z);
			if (b1 > 0)
				ups.insert(z);
			if (b1 < 0)
				dns.insert(z);
		}
	}
	lint ans = 1e9;
	for (int i = l; i <= r; i++)
		ans = min(ans, bit.query(i));
	cout << ans << "\n";
}