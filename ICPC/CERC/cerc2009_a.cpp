#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3100000;

char buf[MAXN];
bool goodPos[MAXN];
int q;

vector<int> read(bool saveGoodPos) {
	scanf("%d\n", &q);
	map<string, int> last;
	vector<int> val;
	int idx = 0;
	for (int i = 0; i < q; i++) {
		fgets(buf, sizeof(buf), stdin);
		for (int j = 0; buf[j];) {
			if (isspace((unsigned char)buf[j])) {
				j++;
				continue;
			}
			int e = j;
			while (buf[e] && !isspace((unsigned char)buf[e]))
				e++;
			idx++;
			if (e == j + 1 && buf[j] == '=') {
				val.push_back(-1e9 - 69);
			} else if (e == j + 1 && buf[j] == '+') {
				val.push_back(-1e9 - 420);
			} else if (isdigit((unsigned char)buf[j])) {
				int ret = 0;
				for (int k = j; k < e; k++)
					ret = ret * 10 + buf[k] - '0';
				val.push_back(-ret);
			} else {
				string tok;
				for (int k = j; k < e; k++)
					tok.push_back(buf[k]);
				int locc = 0;
				auto it = last.find(tok);
				if (it != last.end()) {
					locc = it->second;
					it->second = idx;
				} else {
					last[tok] = idx;
				}
				val.push_back(idx - locc);
			}
			j = e;
		}
		if (saveGoodPos)
			goodPos[sz(val)] = 1;
	}
	return val;
}

int sz;
int dp[MAXN];
map<int, int> trie[MAXN];
int dep[MAXN], fail[MAXN];
int joolLength[50005], pos[50005];

void solve() {
	for (int i = 0; i < MAXN; i++) {
		dep[i] = fail[i] = 0;
		trie[i].clear();
		goodPos[i] = 0;
		dp[i] = 1e9;
	}
	sz = 0;
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		auto y = read(0);
		joolLength[i] = q;
		int p = 0;
		for (auto &i : y) {
			if (!trie[p][i]) {
				trie[p][i] = ++sz;
				dep[trie[p][i]] = dep[p] + 1;
			}
			p = trie[p][i];
		}
		pos[i] = p;
	}
	auto x = read(1);
	queue<int> que;
	for (auto &[i, j] : trie[0])
		que.push(j);
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		for (auto &[i, j] : trie[x]) {
			int p = fail[x];
			while (p && !trie[p][min(i, dep[p] + 1)])
				p = fail[p];
			p = trie[p][min(i, dep[p] + 1)];
			fail[j] = p;
			que.push(j);
		}
	}
	int p = 0;
	int idx = 0;
	int row = 0;
	for (auto &i : x) {
		idx++;
		while (p && !trie[p][min(i, dep[p] + 1)])
			p = fail[p];
		p = trie[p][min(i, dep[p] + 1)];
		if (!goodPos[idx])
			continue;
		dp[p] = min(dp[p], ++row);
	}
	for (int i = sz; i > 0; i--) {
		dp[fail[i]] = min(dp[fail[i]], dp[i]);
	}
	for (int i = 0; i < k; i++) {
		if (dp[pos[i]] < 1e8)
			printf("%d\n", dp[pos[i]] - joolLength[i] + 1);
		else
			puts("NONE");
	}
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		solve();
	}
}