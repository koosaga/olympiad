#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 500005;

vector<vector<pi>> gph;
vector<int> a;
map<lint, lint> pool[MAXN];
int piv;

struct node {
	int ptr;
	lint minv = 0, bsum = 0, absum = 0;
	pi func{1, 0};
	node() {
		ptr = piv++;
		minv = bsum = absum = 0;
		func = pi{1, 0};
	}
	pi F() {
		if (func[0] == 1) {
			auto [k, v] = *pool[ptr].begin();
			return pi{k + func[1], v};
		}
		if (func[0] == -1) {
			auto [k, v] = *pool[ptr].rbegin();
			return pi{-k + func[1], v};
		}
	}
	pi B() {
		if (func[0] == 1) {
			auto [k, v] = *pool[ptr].rbegin();
			return pi{k + func[1], v};
		}
		if (func[0] == -1) {
			auto [k, v] = *pool[ptr].begin();
			return pi{-k + func[1], v};
		}
	}
	void Ins(pi p) {
		p[0] -= func[1];
		p[0] *= func[0];
		pool[ptr][p[0]] += p[1];
	}
	node operator+(node &nd) {
		node ret;
		ret.minv = minv + nd.minv;
		ret.bsum = bsum + nd.bsum;
		ret.absum = absum + nd.absum;
		ret.ptr = ptr;
		if (sz(pool[ret.ptr]) < sz(pool[nd.ptr])) {
			swap(ret.ptr, nd.ptr);
			swap(nd.func, func);
		}
		ret.func = func;
		for (auto &[k, v] : pool[nd.ptr])
			ret.Ins(pi{k * nd.func[0] + nd.func[1], v});
		return ret;
	}
	void rev(lint thr) {
		while (bsum > thr) {
			auto g = B();
			lint d = min(bsum - thr, g[1]);
			bsum -= d;
			absum -= d * g[0];
			g[0] -= func[1];
			g[0] *= func[0];
			pool[ptr][g[0]] -= d;
			if (pool[ptr][g[0]] == 0)
				pool[ptr].erase(g[0]);
		}
		func[0] *= -1;
		func[1] *= -1;
		absum *= -1;
	}
	void up(int x) {
		absum += x * bsum;
		minv += x * bsum - absum;
		func[1] += x;
		lint d = 0;
		while (sz(pool[ptr]) && F()[0] <= 0) {
			auto g = F();
			d += g[1];
			minv += g[0] * g[1];
			absum -= g[0] * g[1];
			if (func[0] == 1)
				pool[ptr].erase(pool[ptr].begin());
			else
				pool[ptr].erase(--pool[ptr].end());
		}
		Ins({0, d});
		Ins({x, int(1e9)});
		absum += 1ll * x * int(1e9);
		bsum += lint(1e9);
	}
};

bool usacod = false;

node dfs(int x, int p) {
	node ret;
	int ch = 0;
	for (auto &[w, y] : gph[x]) {
		if (y == p)
			continue;
		ch++;
		auto z = dfs(y, x);
		z.up(w);
		ret = z + ret;
	}
	if (ch == 0) {
		ret.absum = lint(1e18);
		ret.bsum = lint(1e9);
		pool[ret.ptr][int(1e9)] = int(1e9);
	}
	ret.rev(a[x]);
	if (usacod && x > 0) {
		lint va = ret.minv - ret.absum;
		cout << va << "\n";
	}
	return ret;
}

void solve() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cr(a, n);
		cr(gph, n);
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < n - 1; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			u--;
			v--;
			gph[u].push_back({w, v});
			gph[v].push_back({w, u});
		}
		auto g = dfs(0, -1);
		cout << g.minv - g.absum << "\n";
	}
}

void usaco() {
	int n;
	cin >> n;
	cr(a, n);
	cr(gph, n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n; i++) {
		int w;
		cin >> w;
		gph[i - 1].push_back({w, i});
		gph[i].push_back({w, i - 1});
	}
	usacod = true;
	dfs(n - 1, -1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	usaco();
}