#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 2005;

struct node {
	int a[4];
	node() { a[0] = a[1] = a[2] = a[3] = 0; }
	void insert(int x) {
		if (x == 0)
			return;
		if (a[3])
			return;
		x *= -1;
		auto it = lower_bound(a, a + 4, x) - a;
		if (it < 4 && a[it] != x) {
			a[3] = x;
			rotate(a + it, a + 3, a + 4);
		}
	}
	node operator+(const node &nd) const {
		if (a[3])
			return *this;
		if (nd.a[3])
			return nd;
		int b[8];
		merge(a, a + 4, nd.a, nd.a + 4, b);
		int k = unique(b, b + 8) - b;
		node ret;
		for (int i = 0; i < min(4, k); i++)
			ret.a[i] = b[i];
		return ret;
	}
} D[4][MAXN][MAXN];
int a[MAXN][MAXN];
int popcnt[1 << 16];

static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32)
		c = _read();
	if (c == '-')
		s = -1, c = _read();
	while (c > 32)
		x = 10 * x + (c - '0'), c = _read();
	if (s < 0)
		x = -x;
	return x;
}

int fuck[MAXN];

int main() {
	for (int i = 1; i < (1 << 16); i++)
		popcnt[i] = popcnt[i - (i & -i)] + 1;
	int n, k;
	n = _readInt();
	k = _readInt();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = _readInt();
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			D[0][i][j] = D[0][i - 1][j] + D[0][i][j - 1];
			D[0][i][j].insert(a[i][j]);
		}
		for (int j = n; j; j--) {
			D[1][i][j] = D[1][i - 1][j] + D[1][i][j + 1];
			D[1][i][j].insert(a[i][j]);
		}
	}
	for (int i = n; i; i--) {
		for (int j = 1; j <= n; j++) {
			D[2][i][j] = D[2][i + 1][j] + D[2][i][j - 1];
			D[2][i][j].insert(a[i][j]);
		}
		for (int j = n; j; j--) {
			D[3][i][j] = D[3][i + 1][j] + D[3][i][j + 1];
			D[3][i][j].insert(a[i][j]);
		}
	}
	memset(fuck, -1, sizeof(fuck));
	int dap = 0;
	int mask[16] = {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j])
				continue;
			vector<node *> sex = {&D[0][i - 1][j - 1], &D[1][i - 1][j + 1], &D[2][i + 1][j - 1], &D[3][i + 1][j + 1]};
			memset(mask, 0, sizeof(mask));
			int p = 0;
			bool ok = 1;
			for (int i = 0; i < 4; i++) {
				int siz = 0;
				for (int j = 0; j < 4 && sex[i]->a[j]; j++) {
					siz++;
					int x = -sex[i]->a[j];
					if (fuck[x] == -1) {
						fuck[x] = p++;
					}
					mask[1 << i] |= (1 << fuck[x]);
				}
				if (siz == 0) {
					ok = 0;
					break;
				}
			}
			if (ok) {
				for (int i = 1; i < 16; i++) {
					mask[i] = (mask[i - (i & -i)] | mask[i & -i]);
					if (popcnt[mask[i]] < popcnt[i]) {
						ok = 0;
						break;
					}
				}
				if (ok)
					dap++;
			}
			for (int i = 0; i < 4; i++) {
				int siz = 0;
				for (int j = 0; j < 4 && sex[i]->a[j]; j++) {
					int x = -sex[i]->a[j];
					fuck[x] = -1;
				}
			}
		}
	}
	printf("%d\n", dap);
}