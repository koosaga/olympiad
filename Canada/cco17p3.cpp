#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXT = 12000005;
const int MAXN = 200005;
struct bit {
	int tree[MAXN];
	void add(int x, int v) {
		for (int i = x + 2; i < MAXN; i += i & -i)
			tree[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i = x + 2; i; i -= i & -i)
			ret += tree[i];
		return ret;
	}
} bit;

int trie[2][MAXT][2], piv[2], mark[2][MAXT];
int din[2][MAXT], dout[2][MAXT], pivs;

void dfs(int tr, int pos) {
	din[tr][pos] = pivs;
	if (mark[tr][pos]) {
		pivs++;
	}
	for (int i = 0; i < 2; i++) {
		if (trie[tr][pos][i])
			dfs(tr, trie[tr][pos][i]);
	}
	dout[tr][pos] = pivs;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pi> crd(n);
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		lint x[2];
		cin >> x[0] >> x[1] >> weights[i];
		for (int j = 0; j < 2; j++) {
			int pos = 0;
			while (x[j] > 1) {
				if (!trie[j][pos][x[j] & 1]) {
					trie[j][pos][x[j] & 1] = ++piv[j];
				}
				pos = trie[j][pos][x[j] & 1];
				x[j] >>= 1;
			}
			crd[i][j] = pos;
		}
	}
	vector<array<int, 3>> query(q);
	for (int i = 0; i < q; i++) {
		lint x[2];
		cin >> x[0] >> x[1];
		for (int j = 0; j < 2; j++) {
			int pos = 0;
			while (x[j] > 1) {
				if (!trie[j][pos][x[j] & 1]) {
					break;
				}
				pos = trie[j][pos][x[j] & 1];
				x[j] >>= 1;
			}
			query[i][j] = pos;
			mark[j][query[i][j]] = 1;
		}
		query[i][2] = i;
	}
	for (int i = 0; i < 2; i++)
		dfs(i, 0), pivs = 0;
	vector<vector<pi>> points(q + 1);
	vector<vector<pi>> queries(q + 1);
	vector<lint> ans(q);
	for (int i = 0; i < n; i++) {
		points[din[0][crd[i][0]]].push_back({din[1][crd[i][1]], weights[i]});
		points[din[0][crd[i][0]]].push_back({dout[1][crd[i][1]], -weights[i]});
		points[dout[0][crd[i][0]]].push_back({din[1][crd[i][1]], -weights[i]});
		points[dout[0][crd[i][0]]].push_back({dout[1][crd[i][1]], +weights[i]});
	}
	for (int i = 0; i < q; i++) {
		queries[din[0][query[i][0]]].push_back({din[1][query[i][1]], i});
	}
	for (int i = 0; i <= q; i++) {
		for (auto &[j, w] : points[i])
			bit.add(j, w);
		for (auto &[j, idx] : queries[i])
			ans[idx] = bit.query(j);
	}
	for (int i = 0; i < q; i++)
		cout << ans[i] << "\n";
}