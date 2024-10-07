#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

struct strongly_connected {
	vector<vector<int>> gph;

	void init(int n) {
		gph.clear();
		gph.resize(n);
	}

	void add_edge(int s, int e) { gph[s].push_back(e); }

	vector<int> val, comp, z, cont;
	int Time, ncomps;
	template <class G, class F> int dfs(int j, G &g, F f) {
		int low = val[j] = ++Time, x;
		z.push_back(j);
		for (auto e : g[j])
			if (comp[e] < 0)
				low = min(low, val[e] ?: dfs(e, g, f));

		if (low == val[j]) {
			do {
				x = z.back();
				z.pop_back();
				comp[x] = ncomps;
				cont.push_back(x);
			} while (x != j);
			f(cont);
			cont.clear();
			ncomps++;
		}
		return val[j] = low;
	}
	template <class G, class F> void scc(G &g, F f) {
		int n = sz(g);
		val.assign(n, 0);
		comp.assign(n, -1);
		Time = ncomps = 0;
		for (int i = 0; i < n; i++)
			if (comp[i] < 0)
				dfs(i, g, f);
	}

	int piv;
	void get_scc(int n) {
		scc(gph, [&](vector<int> &v) {});
		for (int i = 0; i < n; i++) {
			comp[i] = ncomps - comp[i] - 1;
		}
		piv = ncomps;
	}
} scc;

struct twosat {
	strongly_connected scc;
	int n;
	void init(int _n) {
		scc.init(2 * _n);
		n = _n;
	}
	int NOT(int x) { return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y) {
		if ((x >> 31) & 1)
			x = (~x) + n;
		if ((y >> 31) & 1)
			y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(int *res) {
		scc.get_scc(2 * n);
		for (int i = 0; i < n; i++) {
			if (scc.comp[i] == scc.comp[NOT(i)])
				return 0;
			if (scc.comp[i] < scc.comp[NOT(i)])
				res[i] = 0;
			else
				res[i] = 1;
		}
		return 1;
	}
} twosat;
// fix a[0][0]
// (i > 0) a[0][i] = y_i, (i > 0) a[i][0] = x_i
// (i > 0, j > 0) a[i][j] = [y_j, -y_j, 0][i%3] + [x_i, -x_i, 0][j%3] + b[i][j]
// a[i][j] \in {0, 1}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m));
	vector<vector<int>> b(n + 1, vector<int>(m + 1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	auto fillme = [&]() {
		// imagine all nondet are zeros
		twosat.init(n + m);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int sum = a[i - 1][j - 1];
				for (int z = 0; z <= i && z <= 2; z++) {
					for (int w = 0; w <= j && w <= 2; w++) {
						if (z + w == 0)
							continue;
						sum -= b[i - z][j - w];
					}
				}
				b[i][j] = sum;
				if (i % 3 == 1)
					sum--;
				if (j % 3 == 1)
					sum--;
				sum *= -1;
				vector<int> clauses;
				if (i % 3 == 0)
					clauses.push_back(j - 1 + n);
				if (i % 3 == 1)
					clauses.push_back(~(j - 1 + n));
				if (j % 3 == 0)
					clauses.push_back(i - 1);
				if (j % 3 == 1)
					clauses.push_back(~(i - 1));
				if (i >= n || j >= m) {
					// special case, it should be just sum
					if (sum < 0 || sum > sz(clauses))
						return false;
					if (sum == 0) {
						for (auto &z : clauses)
							twosat.add_edge(z, ~z); // false
					} else if (sum == sz(clauses)) {
						for (auto &z : clauses)
							twosat.add_edge(~z, z); // true
					} else {
						twosat.add_edge(clauses[0], ~clauses[1]);
						twosat.add_edge(~clauses[0], clauses[1]);
					}
				} else {
					// it should be (sum, sum+1), so sum = {-1, 0, 1, 2}
					if (sum < -1 || sum > sz(clauses))
						return false;
					if (sum == -1) {
						for (auto &z : clauses)
							twosat.add_edge(z, ~z); // false
					}
					if (sum == 0) { // not both.
						if (sz(clauses) == 2)
							twosat.add_edge(clauses[0], ~clauses[1]);
					}
					if (sum == 1) { // at least one.
						if (sz(clauses) == 1) {
							twosat.add_edge(~clauses[0], clauses[0]);
						}
						if (sz(clauses) == 2) {
							twosat.add_edge(~clauses[0], clauses[1]);
						}
					}
					if (sum == 2) {
						for (auto &z : clauses)
							twosat.add_edge(~z, z); // true
					}
				}
			}
		}
		twosat.add_edge((n - 1), ~(n - 1));
		twosat.add_edge((n + m - 1), ~(n + m - 1));
		int res[6974];
		if (!twosat.satisfy(res))
			return false;
		for (int i = 1; i < n; i++)
			b[i][0] = res[i - 1];
		for (int i = 1; i < m; i++)
			b[0][i] = res[i + n - 1];
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				int sum = a[i - 1][j - 1];
				for (int z = 0; z <= i && z <= 2; z++) {
					for (int w = 0; w <= j && w <= 2; w++) {
						if (z + w == 0)
							continue;
						sum -= b[i - z][j - w];
					}
				}
				b[i][j] = sum;
				assert(sum >= 0 && sum <= 1);
			}
		}
		return true;
	};
	for (b[0][0] = 0; b[0][0] < 2; b[0][0]++) {
		if (fillme()) {
			cout << "1\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << (b[i][j] ? 'B' : 'W');
				}
				cout << "\n";
			}
			return 0;
		}
	}
	cout << "0\n";
}