#include <cstdio>
#include <cmath>
#include <algorithm>
#include <memory.h>
using namespace std;

#define N 50000
int v, n, m, i, j, len, a, b, c, d, len1, zhan[N], till[N], go[N], f[N], next[N], x[N], y[N], to[N], s1[N], s2[N], cost, prep[N], l[N], mincost[N];
bool used[N], cir[N], in[N];

bool cmp(int a, int b) {
	return atan2(y[go[a]] - y[i], x[go[a]] - x[i]) > atan2(y[go[b]] - y[i], x[go[b]] - x[i]);
}

void add(int x, int y, int z) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
	f[len] = z;
}

void add1(int x, int y, int z) {
	len++;
	s1[len] = x;
	s2[len] = y;
	l[len] = z;
}

void FindPlane(int x) {
	if (used[x])	return ;
	to[x] = v;
	used[x] = true;
	FindPlane(next[x ^ 1]);
}

void dfs(int k) {
	zhan[++len1] = k;
	used[k] = in[k] = true;
	if (!used[prep[k]])	dfs(prep[k]);
}

int main() {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++)	scanf("%d%d", &x[i], &y[i]);
	len = 1;
	for (i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		add(a, b, c);
		add(b, a, d);
	}
	for (i = 1; i <= n; i++) {
		len1 = 0;
		for (j = till[i]; j; j = next[j])	zhan[++len1] = j;
		sort(zhan + 1, zhan + len1 + 1, cmp);
		for (j = 1; j < len1; j++)	next[zhan[j]] = zhan[j + 1];
		next[zhan[len1]] = zhan[1];
	}
	for (i = 2; i <= 2 * m + 1; i++)
	if (!used[i]) v++, FindPlane(i);
	
	len = 0;
	for (i = 2; i <= 2 * m + 1; i++)
	if (f[i])	add1(to[i], to[i ^ 1], f[i]);
	v++;
	for (i = 1; i < v; i++)	add1(v, i, 1000000000);
	while (true) {
		for (i = 1; i <= v; i++)	mincost[i] = 2000000000;
		for (i = 1; i <= len; i++)	if (s1[i] != s2[i] && l[i] < mincost[s2[i]])	mincost[s2[i]] = l[i], prep[s2[i]] = s1[i];
		memset(used, 0, sizeof(used));
		memset(cir, 0, sizeof(cir));
		bool Find = false;
		to[v] = v;
		used[0] = true;
		for (i = 1; i < v; i++)	
			if (mincost[i] < 2000000000 && !used[i]) {
				len1 = 0;
				dfs(i);
				if (in[prep[zhan[len1]]]) {
					Find = true;
					zhan[len1 + 1] = 0; 
					for (j = len1; zhan[j + 1] != prep[zhan[len1]]; j--)	to[zhan[j]] = zhan[len1], cost += mincost[zhan[j]];
					for (; j; j--)	to[zhan[j]] = zhan[j];
					cir[zhan[len1]] = true;
				}else	for (j = 1; j <= len1; j++)	to[zhan[j]] = zhan[j];
				for (j = 1; j <= len1; j++)	in[zhan[j]] = false;
			}
		if (!Find) {
			for (i = 1; i < v; i++)
				if (mincost[i] < 2000000000)	cost += mincost[i];
			break;
		}
		for (i = 1; i <= len; i++) {
			if (cir[to[s2[i]]])	l[i] -= mincost[s2[i]];
			s1[i] = to[s1[i]];
			s2[i] = to[s2[i]];
		}
	}
	printf("%d\n", cost - 1000000000);
}
