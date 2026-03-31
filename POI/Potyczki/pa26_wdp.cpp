#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
const int MAXN = 10000005;

mt19937 rng(0x14004);
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }

int lp[MAXN];
array<int, 3> primes[MAXN];

int que[MAXN], gde[MAXN], tot;
int counts[MAXN], ans;
int pivot = 2;
int fuck[MAXN];

int query() { return ans; }

void reinit() {
	for (int j = 0; j < tot; j++) {
		counts[que[j] % pivot]--;
	}
	for (int j = 0; j <= ans; j++)
		fuck[j] = 0;
	ans = 0;
	if (tot >= 2) {
		int p = abs(que[0] - que[1]);
		int l = 0;
		while (l < 3 && primes[p][l])
			l++;
		if (l == 0)
			pivot = 2;
		else {
			pivot = primes[p][randint(0, l - 1)];
		}
	}
	for (int j = 0; j < tot; j++) {
		int moded = que[j] % pivot;
		fuck[counts[moded]]--;
		counts[moded]++;
		fuck[counts[moded]]++;
		if (ans < counts[moded]) {
			ans = counts[moded];
		}
	}
}

void insert(int x) {
	int moded = x % pivot;
	fuck[counts[moded]]--;
	counts[moded]++;
	fuck[counts[moded]]++;
	if (ans < counts[moded]) {
		ans = counts[moded];
	}
	que[tot++] = x;
	int par = randint(0, tot - 1);
	swap(que[par], que[tot - 1]);
	gde[que[par]] = par;
	gde[que[tot - 1]] = tot - 1;
	if (par != tot - 1) {
		if (par < 2 || tot - 1 < 2)
			reinit();
	}
}

void remove(int x) {
	int moded = x % pivot;
	fuck[counts[moded]]--;
	if (ans == counts[moded] && fuck[ans] == 0)
		ans--;
	counts[moded]--;
	fuck[counts[moded]]++;
	int pos = gde[x];
	tot--;
	if (pos != tot) {
		swap(que[pos], que[tot]);
		gde[que[pos]] = pos;
		if (pos < 2 || tot < 2)
			reinit();
	}
}

void clear() {
	for (int j = 0; j < tot; j++) {
		counts[que[j] % pivot]--;
	}
	for (int j = 0; j <= ans; j++)
		fuck[j] = 0;

	ans = 0;
	tot = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> pr;
	for (int i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; i * pr[j] <= n; ++j) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i]) {
				break;
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		primes[i] = primes[i / lp[i]];
		if (lp[i] > 47) {
			for (int j = 0; j < 3; j++) {
				if (primes[i][j] == lp[i])
					break;
				if (primes[i][j] == 0) {
					primes[i][j] = lp[i];
					break;
				}
			}
		}
	}
	vector<int> pos(q);
	for (auto &x : pos)
		cin >> x, x--;
	vector<int> ans(q);
	bitset<MAXN> marks = 0;
	pi cnt = {};
	for (int i = 0; i < q; i++) {
		marks[pos[i]].flip();
		if (marks[pos[i]])
			cnt[pos[i] & 1]++;
		else
			cnt[pos[i] & 1]--;
		ans[i] = max(cnt[0], cnt[1]);
	}
	for (int i = 1; i < sz(pr) && pr[i] <= 47; i++) {
		int cnt[47] = {};
		int P = pr[i];
		marks = 0;
		int mx = 0;
		int tcnt = 0;
		for (int i = 0; i < q; i++) {
			marks[pos[i]].flip();
			int moded = pos[i] % P;
			if (marks[pos[i]]) {
				fuck[cnt[moded]]--;
				cnt[moded]++;
				fuck[cnt[moded]]++;
				tcnt++;
				if (mx < cnt[moded]) {
					mx = cnt[moded];
				}
			} else {
				tcnt--;
				fuck[cnt[moded]]--;
				if (mx == cnt[moded] && fuck[mx] == 0)
					mx--;
				cnt[moded]--;
				fuck[cnt[moded]]++;
			}
			ans[i] = max(ans[i], mx);
		}
		for (int i = 0; i <= mx; i++)
			fuck[i] = 0;
	}
	int iters = 0;
	for (int i = 0; clock() < 9.5 * CLOCKS_PER_SEC; i++) {
		marks = 0;
		iters++;
		for (int i = 0; i < q; i++) {
			marks[pos[i]].flip();
			if (marks[pos[i]]) {
				insert(pos[i]);
			} else {
				remove(pos[i]);
			}
			ans[i] = max(ans[i], query());
		}
		clear();
	}
	// cerr << "iterations: " << iters << endl;
	for (auto &x : ans)
		cout << x << "\n";
}