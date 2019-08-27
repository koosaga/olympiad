#include <cstdio>
#include <memory.h>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 1100000
int n, m, x, y, len, i, n1, len1, len2, Time, j, q, h, du[N], zhan[N], to[N], till[N], next[N], go[N], till1[N], next1[N], go1[N], till2[N], go2[N], next2[N], dfn[N], low[N];
bool sel[N], in[N];

int s(int x, int y) {
	return x * 2 + y;
}

void add(int x, int y) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
}

void add1(int x, int y) {
	next1[++len1] = till1[x];
	till1[x] = len1;
	go1[len1] = y;
}

void add2(int x, int y) {
	next2[++len2] = till2[x];
	till2[x] = len2;
	go2[len2] = y;
}

int get() {
	int x;
	char k;
	scanf("%d%c", &x, &k);
	x = x * 2;
	if (k == 'h')	x++;
	return x;
}

void xiao(int k) {
	zhan[zhan[0] + 1] = -1;
	n1++;
	while (zhan[zhan[0] + 1] != k) {
		int p = zhan[zhan[0]];
		in[p] = false;
		to[p] = n1;
		add1(n1, p);
		zhan[0]--;
	}
}

void tarjan(int k) {
	zhan[++zhan[0]] = k;
	in[k] = true;
	dfn[k] = low[k] = ++Time;
	for (int i = till[k]; i; i = next[i])
	if (!dfn[go[i]])	tarjan(go[i]), low[k] = min(low[k], low[go[i]]);
	else	if (in[go[i]])	low[k] = min(low[k], dfn[go[i]]);
	if (low[k] == dfn[k])	xiao(k);
}

void Cover(int k) {
	sel[k] = true;
	for (int i = till2[k]; i; i = next2[i])
		if (!sel[go2[i]])	Cover(go2[i]);
}

void out(int k) {
	if (k % 2 == 1)	printf("%dh ", (k - 1) / 2);
	else	printf("%dw ", k / 2);
}

int main() {
	while (scanf("%d%d", &n, &m), n) {
		len = n1 = len1 = len2 = 0;
		memset(till, 0, sizeof till);
		memset(sel, 0, sizeof sel);
		memset(dfn, 0, sizeof dfn);
		memset(du, 0, sizeof du);
		memset(till1, 0, sizeof till1);
		memset(till2, 0, sizeof till2);
		memset(zhan, 0, sizeof(zhan));
		add(s(0, 0), s(0, 1));
		for (i = 0; i < 2 * n; i++)	add(s(i, 0), s(i ^ 1, 1)), add(s(i, 1), s(i ^ 1, 0));
		while (m--) {
			x = get();
			y = get();
			add(s(x, 0), s(y, 1));
			add(s(y, 0), s(x, 1));
		}
		for (i = 0; i < 4 * n; i++)
			if (!dfn[i])	tarjan(i);
		for (i = 0; i < 4 * n; i++)	if (to[i] == to[i ^ 1])	break;
		if (i < 4 * n) {
			printf("bad luck\n");
			continue;
			// return 0;
		}
		for (i = 0; i < 4 * n; i++)
			for (j = till[i]; j; j = next[j])	if (to[i] != to[go[j]])	add2(to[go[j]], to[i]), du[to[i]]++;
		h = 0;
		for (i = 1; i <= n1; i++)
			if (!du[i])	zhan[++h] = i;
		for (q = 1; q <= h; q++)
		if (!sel[zhan[q]]) {
			for (i = till2[zhan[q]]; i; i = next2[i])
				if (!(--du[go2[i]]))	zhan[++h] = go2[i];
			for (i = till1[zhan[q]]; i; i = next1[i])
				if (!sel[to[go1[i] ^ 1]])	Cover(to[go1[i] ^ 1]);
		}
		for (i = 2; i < 2 * n; i++)
			if (!sel[to[s(i, 1)]])	out(i);
		printf("\n");
	}
}
