#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using P3 = array<lint, 3>;
using pi = array<lint, 2>;
const int MAXN = 1005;

struct mcmf {
	struct edg {
		int pos, cap, rev;
		lint cost;
	};
	vector<edg> gph[MAXN];
	void clear() {
		for (int i = 0; i < MAXN; i++)
			gph[i].clear();
	}
	void addEdge(int s, int e, int x, lint c) {
		gph[s].push_back({e, x, sz(gph[e]), c});
		gph[e].push_back({s, 0, sz(gph[s]) - 1, -c});
	}
	lint dist[MAXN];
	int pa[MAXN], pe[MAXN];
	bool inque[MAXN];
	bool spfa(int src, int sink) {
		memset(dist, 0x3f, sizeof(dist));
		memset(inque, 0, sizeof(inque));
		queue<int> que;
		dist[src] = 0;
		inque[src] = 1;
		que.push(src);
		bool ok = 0;
		while (sz(que)) {
			int x = que.front();
			que.pop();
			if (x == sink)
				ok = 1;
			inque[x] = 0;
			for (int i = 0; i < sz(gph[x]); i++) {
				edg e = gph[x][i];
				if (e.cap > 0 && dist[e.pos] > dist[x] + e.cost) {
					dist[e.pos] = dist[x] + e.cost;
					pa[e.pos] = x;
					pe[e.pos] = i;
					if (!inque[e.pos]) {
						inque[e.pos] = 1;
						que.push(e.pos);
					}
				}
			}
		}
		return ok;
	}
	lint match(int src, int sink) {
		lint ret = 0;
		while (spfa(src, sink)) {
			lint cap = 1e18;
			for (int pos = sink; pos != src; pos = pa[pos]) {
				cap = min(cap, (lint)gph[pa[pos]][pe[pos]].cap);
			}
			ret += cap * dist[sink];
			for (int pos = sink; pos != src; pos = pa[pos]) {
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= cap;
				gph[pos][rev].cap += cap;
			}
		}
		return ret;
	}
} mcmf;

int hung(vector<vector<int>> a) {
	int n = sz(a);
	for (int i = 0; i < n; i++) {
		mcmf.addEdge(0, i + 1, 1, 0);
		mcmf.addEdge(i + n + 1, n + n + 1, 1, 0);
		for (int j = 0; j < n; j++) {
			mcmf.addEdge(i + 1, j + n + 1, 1, a[i][j]);
		}
	}
	return mcmf.match(0, 2 * n + 1);
}

P3 operator-(P3 a, P3 b) {
	for (int i = 0; i < 3; i++)
		a[i] -= b[i];
	return a;
}

P3 norm(P3 a) {
	lint g = 0;
	for (int i = 0; i < 3; i++) {
		g = gcd(g, abs(a[i]));
	}
	assert(g > 0);
	for (int i = 0; i < 3; i++) {
		a[i] /= g;
	}
	return a;
}

P3 cross(const P3 &a, const P3 &b) { return P3{a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
P3 cross(const P3 &a, const P3 &b, const P3 &c) { return cross(b - a, c - a); }

bool isMult(const P3 &a, const P3 &b) {
	P3 c = cross(a, b);
	for (int i = 0; i < sz(c); i++) {
		if (c[i] != 0)
			return 0;
	}
	return 1;
}

bool collinear(const P3 &a, const P3 &b, const P3 &c) { return isMult(b - a, c - a); }

lint dist(P3 a, P3 b) {
	lint ans = 0;
	for (int i = 0; i < 3; i++)
		ans += (a[i] - b[i]) * (a[i] - b[i]);
	return ans;
}

lint dot(P3 a, P3 b) {
	lint ans = 0;
	for (int i = 0; i < 3; i++)
		ans += a[i] * b[i];
	return ans;
}

bool is_collinear(vector<P3> p) {
	for (int i = 2; i < sz(p); i++) {
		if (!collinear(p[0], p[1], p[i]))
			return false;
	}
	return true;
}

int haveSex(vector<P3> p, vector<P3> d, int n) {
	P3 arg = p[1] - p[0];
	int dap = 1557;
	for (int i = 0; i < 2; i++) {
		vector<int> ord(n);
		iota(all(ord), 0);
		sort(all(ord), [&](const int &x, const int &y) { return dot(p[x], arg) < dot(p[y], arg); });
		for (int i = 0; i < n; i++) {
			vector<int> remord = ord;
			remord.erase(remord.begin() + i);
			int isol = ord[i];
			vector<int> left(n - 1), right(n - 1);
			for (int i = 0; i < n - 1; i += 2) {
				int cnt = 0;
				if (norm(d[remord[i]]) != norm(p[remord[i + 1]] - p[remord[i]]))
					cnt++;
				if (norm(d[remord[i + 1]]) != norm(p[remord[i]] - p[remord[i + 1]]))
					cnt++;
				left[i + 1] += cnt;
				right[i] += cnt;
			}
			for (int i = 1; i < n - 1; i++)
				left[i] += left[i - 1];
			for (int i = n - 3; i >= 0; i--)
				right[i] += right[i + 1];
			vector<int> euhehe(n - 1);
			for (int i = 0; i < n - 2; i++) {
				P3 z = p[remord[i + 1]] - p[remord[i]];
				P3 head = d[remord[i]];
				if (norm(z) != norm(head))
					euhehe[i + 1] += 1;
				euhehe[i + 1] += euhehe[i];
			}
			for (int l = 0; l < n - 1; l += 2) {
				for (int r = l + 1; r < n - 1; r += 2) {
					int cost = 0;
					if (l > 0)
						cost += left[l - 1];
					if (r < n - 1)
						cost += right[r + 1];
					cost += euhehe[r] - euhehe[l];
					int isolCollinear = isMult(d[isol], arg);
					int backCollinear = isMult(d[remord[r]], arg);
					if (isolCollinear || backCollinear) {
						cost += isolCollinear;
						cost += backCollinear;
					} else {
						P3 a = arg;
						P3 b = d[remord[r]];
						P3 c = d[isol];
						if (isMult(b, c)) {
							cost++;
						} else {
							P3 cr1 = cross(a, b);
							P3 cr2 = cross(b, c);
							P3 cr3 = cross(c, a);

							if (norm(cr1) != norm(cr2) || norm(cr2) != norm(cr3))
								cost++;
						}
					}
					dap = min(dap, cost);
				}
			}
		}
		for (int j = 0; j < 3; j++)
			arg[j] = -arg[j];
	}
	return 1000 + dap;
}

int main() {
	int n;
	cin >> n;
	if (n == 1) {
		cout << "-1\n";
		return 0;
	}
	vector<P3> p(n), d(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++)
			cin >> p[i][j];
		for (int j = 0; j < 3; j++)
			cin >> d[i][j];
	}
	if (n == 2) {
		int ans = 0;
		if (norm(d[0]) != norm(p[1] - p[0]))
			ans++;
		if (norm(d[1]) != norm(p[0] - p[1]))
			ans++;
		cout << ans << "\n";
		return 0;
	}
	if (is_collinear(p) && n % 2 == 1) {
		cout << haveSex(p, d, n) << "\n";
		return 0;
	}
	vector<vector<int>> mtrx(n, vector<int>(n, 1e6));
	for (int i = 0; i < n; i++) {
		pi ans{lint(1e18), -1};
		vector<int> ord;
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			ord.push_back(j);
			if (norm(p[j] - p[i]) == norm(d[i])) {
				ans = min(ans, pi{dist(p[i], p[j]), j});
			}
		}
		sort(all(ord), [&](const int &x, const int &y) { return dist(p[i], p[x]) < dist(p[i], p[y]); });
		if (ans[0] < 1e15) {
			mtrx[i][ans[1]] = 0;
		}
		set<P3> s;
		for (int j = 0; j < sz(ord); j++) {
			auto nrm = norm(p[ord[j]] - p[i]);
			if (s.count(nrm))
				continue;
			s.insert(nrm);
			mtrx[i][ord[j]] = min(1, mtrx[i][ord[j]]);
		}
	}
	cout << hung(mtrx) << "\n";
}