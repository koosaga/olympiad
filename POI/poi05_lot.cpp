#include <algorithm>
#include <assert.h>
#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <limits.h>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, int> pi;

int n, p[1000005], d[1000005];
lint ps[1000005], ds[1000005];
bitset<1000005> dap1, dap2;

int dq[2000000];

inline lint get_val(int idx, lint q) {
	if (idx <= n) {
		return ps[idx - 1] - ds[idx - 1];
	}
	idx -= n;
	return q + ps[idx - 1] - ds[idx - 1];
}

void solve(bitset<1000005> &ans) {
	int hd = 0, tl = 0;
	lint q = ps[n] - ds[n];

	for (int i = 1; i <= n; i++) {
		lint v = get_val(i, q);
		while (hd < tl && get_val(dq[tl - 1], q) >= v) {
			tl--;
		}
		dq[tl++] = i;
	}

	for (int i = 1; i <= n; i++) {
		int nxt = i + n;
		lint v = get_val(nxt, q);

		while (hd < tl && get_val(dq[tl - 1], q) >= v) {
			tl--;
		}
		dq[tl++] = nxt;

		if (hd < tl && get_val(dq[hd], q) < ps[i - 1] - ds[i - 1])
			ans[i] = 0;
		else
			ans[i] = 1;

		if (hd < tl && dq[hd] == i)
			hd++;
	}
}

static char buf[1 << 19];
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

int main() {
	n = _readInt();

	for (int i = 1; i <= n; i++) {
		p[i] = _readInt();
		d[i] = _readInt();
	}

	for (int i = 1; i <= n; i++) {
		ps[i] = ps[i - 1] + p[i];
		ds[i] = ds[i - 1] + d[i];
	}

	solve(dap1);

	reverse(p + 1, p + n + 1);
	reverse(d + 1, d + n + 1);
	rotate(d + 1, d + 2, d + n + 1);

	for (int i = 1; i <= n; i++) {
		ps[i] = ps[i - 1] + p[i];
		ds[i] = ds[i - 1] + d[i];
	}

	solve(dap2);

	for (int i = 1; i <= n; i++) {
		if (dap1[i] || dap2[n + 1 - i])
			puts("TAK");
		else
			puts("NIE");
	}
}