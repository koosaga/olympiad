#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
using llf = long double;
// source: https://github.com/justiceHui/icpc-teamnote/blob/master/code/Math/Matrix.cpp

const int mod = 998244353; // 1e9 + 7;//993244853;

// I don't remember the credit of modint, but it's not mine.
// I don't remember the credit of FFT, but it's probably mine.
// Polynomial library is due to adamant:
// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
// To use polynomial sqrt, need to amend sqrt for modint.

struct mint {
	int val;
	mint() { val = 0; }
	mint(const lint &v) {
		val = (-mod <= v && v < mod) ? v : v % mod;
		if (val < 0)
			val += mod;
	}

	friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
	friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

	mint operator-() const { return mint(-val); }
	mint &operator+=(const mint &m) {
		if ((val += m.val) >= mod)
			val -= mod;
		return *this;
	}
	mint &operator-=(const mint &m) {
		if ((val -= m.val) < 0)
			val += mod;
		return *this;
	}
	mint &operator*=(const mint &m) {
		val = (lint)val * m.val % mod;
		return *this;
	}
	friend mint ipow(mint a, lint p) {
		mint ans = 1;
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	mint inv() const { return ipow(*this, mod - 2); }
	mint &operator/=(const mint &m) { return (*this) *= m.inv(); }

	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
	operator int64_t() const { return val; }
};

template <typename T> bool IsZero(T x) { return x == mint(0); }
template <typename T> T Add(T a, T b) { return a + b; }
template <typename T> T Sub(T a, T b) { return a - b; }
template <typename T> T Mul(T a, T b) { return a * b; }
template <typename T> T Div(T a, T b) { return a / b; }

template <typename T, bool calc_inv> // return {rref, rank, det, inv}
tuple<vector<vector<T>>, int, T, vector<vector<T>>> Gauss(vector<vector<T>> a) {
	int n = a.size(), m = a[0].size(), rank = 0;
	assert(n == m || !calc_inv);
	vector<vector<T>> out(n, vector<T>(m, 0));
	T det = T(1);
	if constexpr (calc_inv)
		for (int i = 0; i < n; i++)
			out[i][i] = T(1);
	for (int i = 0; i < m; i++) {
		if (rank == n)
			break;
		if (IsZero(a[rank][i])) {
			T mx = T(0);
			int idx = -1; // fucking precision error
			for (int j = rank + 1; j < n; j++) {
				if (a[j][i].val != 0)
					idx = j;
			}
			if (idx == -1 || IsZero(a[idx][i])) {
				det = 0;
				continue;
			}
			for (int k = 0; k < m; k++) {
				a[rank][k] = Add(a[rank][k], a[idx][k]);
				if constexpr (calc_inv)
					out[rank][k] = Add(out[rank][k], out[idx][k]);
			}
		}
		det = Mul(det, a[rank][i]);
		T coeff = Div(T(1), a[rank][i]);
		for (int j = 0; j < m; j++)
			a[rank][j] = Mul(a[rank][j], coeff);
		if constexpr (calc_inv)
			for (int j = 0; j < m; j++)
				out[rank][j] = Mul(out[rank][j], coeff);
		for (int j = 0; j < n; j++) {
			if (rank == j)
				continue;
			T t = a[j][i]; // Warning: [j][k], [rank][k]
			for (int k = 0; k < m; k++)
				a[j][k] = Sub(a[j][k], Mul(a[rank][k], t));
			if constexpr (calc_inv)
				for (int k = 0; k < m; k++)
					out[j][k] = Sub(out[j][k], Mul(out[rank][k], t));
		}
		rank++; // linear system: warning len(A) != len(A[0])
	}
	return {a, rank, det, out}; // linear system: get RREF(A|b)
} // 0 0 ... 0 b[i]: inconsistent, rank < len(A[0]): multiple
// code written by https://loj.ac/u/teapotd
// TODO: has bug - don't work with duplicate edges

template <class flow_t> struct HLPP {
	struct Edge {
		int to, inv;
		flow_t rem, cap;
	};

	vector<vector<Edge>> G; // Don't use basic_string here, it will fuck up your entire life
	vector<flow_t> excess;
	vector<int> hei, arc, prv, nxt, act, bot;
	queue<int> Q;
	int n, high, cut, work;

	// Initialize for n vertices
	HLPP(int k) : G(k) {}

	int addEdge(int u, int v, flow_t cap, flow_t rcap = 0) {
		G[u].push_back({v, sz(G[v]), cap, cap});
		G[v].push_back({u, sz(G[u]) - 1, rcap, rcap});
		return sz(G[u]) - 1;
	}

	void raise(int v, int h) {
		prv[nxt[prv[v]] = nxt[v]] = prv[v];
		hei[v] = h;
		if (excess[v] > 0) {
			bot[v] = act[h];
			act[h] = v;
			high = max(high, h);
		}
		if (h < n)
			cut = max(cut, h + 1);
		nxt[v] = nxt[prv[v] = h += n];
		prv[nxt[nxt[h] = v]] = v;
	}

	void global(int s, int t) {
		hei.assign(n, n * 2);
		act.assign(n * 2, -1);
		iota(all(prv), 0);
		iota(all(nxt), 0);
		hei[t] = high = cut = work = 0;
		hei[s] = n;
		for (int x : {t, s})
			for (Q.push(x); !Q.empty(); Q.pop()) {
				int v = Q.front();
				for (auto &e : G[v]) {
					if (hei[e.to] == n * 2 && G[e.to][e.inv].rem)
						Q.push(e.to), raise(e.to, hei[v] + 1);
				}
			}
	}

	void push(int v, Edge &e, bool z) {
		auto f = min(excess[v], e.rem);
		if (f > 0) {
			if (z && !excess[e.to]) {
				bot[e.to] = act[hei[e.to]];
				act[hei[e.to]] = e.to;
			}
			e.rem -= f;
			G[e.to][e.inv].rem += f;
			excess[v] -= f;
			excess[e.to] += f;
		}
	}

	void discharge(int v) {
		int h = n * 2, k = hei[v];

		for (int j = 0; j < sz(G[v]); j++) {
			auto &e = G[v][arc[v]];
			if (e.rem) {
				if (k == hei[e.to] + 1) {
					push(v, e, 1);
					if (excess[v] <= 0)
						return;
				} else
					h = min(h, hei[e.to] + 1);
			}
			if (++arc[v] >= sz(G[v]))
				arc[v] = 0;
		}

		if (k < n && nxt[k + n] == prv[k + n]) {
			for (int j = k; j < cut; j++) {
				while (nxt[j + n] < n)
					raise(nxt[j + n], n);
			}
			cut = k;
		} else
			raise(v, h), work++;
	}

	// Compute maximum flow from src to dst
	flow_t flow(int src, int dst) {
		excess.assign(n = sz(G), 0);
		arc.assign(n, 0);
		prv.assign(n * 3, 0);
		nxt.assign(n * 3, 0);
		bot.assign(n, 0);
		for (auto &e : G[src]) {
			excess[src] = e.rem, push(src, e, 0);
		}

		global(src, dst);

		for (; high; high--)
			while (act[high] != -1) {
				int v = act[high];
				act[high] = bot[v];
				if (v != src && hei[v] == high) {
					discharge(v);
					if (work > 4 * n)
						global(src, dst);
				}
			}

		return excess[dst];
	}

	// Get flow through e-th edge of vertex v
	flow_t getFlow(int v, int e) { return G[v][e].cap - G[v][e].rem; }

	// Get if v belongs to cut component with src
	bool cutSide(int v) { return hei[v] >= n; }
};

template <class T> struct Circulation {
	const T INF = numeric_limits<T>::max() / 2;
	T lowerBoundSum = 0;
	HLPP<T> mf;

	// Initialize for n vertices
	Circulation(int k) : mf(k + 2) {}
	void addEdge(int s, int e, T l, T r) {
		mf.addEdge(s + 2, e + 2, r - l);
		if (l > 0) {
			mf.addEdge(0, e + 2, l);
			mf.addEdge(s + 2, 1, l);
			lowerBoundSum += l;
		} else {
			mf.addEdge(0, s + 2, -l);
			mf.addEdge(e + 2, 1, -l);
			lowerBoundSum += -l;
		}
	}
	bool solve(int s, int e) {
		//       mf.addEdge(e+2, s+2, INF); // to reduce as maxflow with lower bounds, in circulation problem skip this line
		return lowerBoundSum == mf.flow(0, 1);
		// to get maximum LR flow, run maxflow from s+2 to e+2 again
	}
};
template <class T> struct MinCostCirculation {
	const int SCALE = 3; // scale by 1/(1 << SCALE)
	const T INF = numeric_limits<T>::max() / 2;
	struct EdgeStack {
		int s, e;
		T l, r, cost;
	};
	struct Edge {
		int pos, rev;
		T rem, cap, cost;
	};
	int n;
	vector<EdgeStack> estk;
	Circulation<T> circ;
	vector<vector<Edge>> gph;
	vector<T> p;
	MinCostCirculation(int k) : circ(k), gph(k), p(k) { n = k; }
	void addEdge(int s, int e, T l, T r, T cost) { estk.push_back({s, e, l, r, cost}); }
	pair<bool, T> solve() {
		for (auto &i : estk) {
			if (i.s != i.e)
				circ.addEdge(i.s, i.e, i.l, i.r);
		}
		if (!circ.solve(-1, -1)) {
			return make_pair(false, T(0));
		}
		vector<int> ptr(n);
		T eps = 0;
		for (auto &i : estk) {
			T curFlow;
			if (i.s != i.e)
				curFlow = i.r - circ.mf.G[i.s + 2][ptr[i.s]].rem;
			else
				curFlow = i.r;
			int srev = sz(gph[i.e]);
			int erev = sz(gph[i.s]);
			if (i.s == i.e)
				srev++;
			gph[i.s].push_back({i.e, srev, i.r - curFlow, i.r, i.cost * (n + 1)});
			gph[i.e].push_back({i.s, erev, -i.l + curFlow, -i.l, -i.cost * (n + 1)});
			eps = max(eps, abs(i.cost) * (n + 1));
			if (i.s != i.e) {
				ptr[i.s] += 2;
				ptr[i.e] += 2;
			}
		}
		while (true) {
			auto cost = [&](Edge &e, int s, int t) { return e.cost + p[s] - p[t]; };
			eps = 0;
			for (int i = 0; i < n; i++) {
				for (auto &e : gph[i]) {
					if (e.rem > 0)
						eps = max(eps, -cost(e, i, e.pos));
				}
			}
			if (eps <= T(1))
				break;
			eps = max(T(1), eps >> SCALE);
			bool upd = 1;
			for (int it = 0; it < 5 && upd; it++) {
				upd = false;
				for (int i = 0; i < n; i++) {
					for (auto &e : gph[i]) {
						if (e.rem > 0 && p[e.pos] > p[i] + e.cost + eps) {
							p[e.pos] = p[i] + e.cost + eps;
							upd = true;
						}
					}
				}
				if (!upd)
					break;
			}
			if (!upd)
				continue;
			vector<T> excess(n);
			queue<int> que;
			auto push = [&](Edge &e, int src, T flow) {
				e.rem -= flow;
				gph[e.pos][e.rev].rem += flow;
				excess[src] -= flow;
				excess[e.pos] += flow;
				if (excess[e.pos] <= flow && excess[e.pos] > 0) {
					que.push(e.pos);
				}
			};
			vector<int> ptr(n);
			auto relabel = [&](int v) {
				ptr[v] = 0;
				p[v] = -INF;
				for (auto &e : gph[v]) {
					if (e.rem > 0) {
						p[v] = max(p[v], p[e.pos] - e.cost - eps);
					}
				}
			};
			for (int i = 0; i < n; i++) {
				for (auto &j : gph[i]) {
					if (j.rem > 0 && cost(j, i, j.pos) < 0) {
						push(j, i, j.rem);
					}
				}
			}
			while (sz(que)) {
				int x = que.front();
				que.pop();
				while (excess[x] > 0) {
					for (; ptr[x] < sz(gph[x]); ptr[x]++) {
						Edge &e = gph[x][ptr[x]];
						if (e.rem > 0 && cost(e, x, e.pos) < 0) {
							push(e, x, min(e.rem, excess[x]));
							if (excess[x] == 0)
								break;
						}
					}
					if (excess[x] == 0)
						break;
					relabel(x);
				}
			}
		}
		T ans = 0;
		for (int i = 0; i < n; i++) {
			for (auto &j : gph[i]) {
				j.cost /= (n + 1);
				ans += j.cost * (j.cap - j.rem);
			}
		}
		return make_pair(true, ans / 2);
	}
	void bellmanFord() {
		fill(all(p), T(0));
		bool upd = 1;
		while (upd) {
			upd = 0;
			for (int i = 0; i < n; i++) {
				for (auto &j : gph[i]) {
					if (j.rem > 0 && p[j.pos] > p[i] + j.cost) {
						p[j.pos] = p[i] + j.cost;
						upd = 1;
					}
				}
			}
		}
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	MinCostCirculation<lint> mf(n);
	for (int i = 0; i < n; i++) {
		int q;
		cin >> q;
		while (q--) {
			int j, c;
			cin >> j >> c;
			j--;
			mf.addEdge(i, j, 1, 1e5, c);
		}
		if (i)
			mf.addEdge(i, 0, 0, 1e5, 0);
	}
	cout << mf.solve().second << "\n";
}