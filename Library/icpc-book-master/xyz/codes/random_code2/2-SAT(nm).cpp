#include <cstdio>
#include <memory.h>
using namespace std;

#define N 100000
int n, m, i, a, b, len, j, till[N], go[N], next[N], zhan[N];
bool ok[N], used[N];

void add(int x, int y) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
}

int s(int x, int y) {
	return (x - 1) * 2 + y;
}

bool dfs(int k) {
	used[k] = true;
	zhan[++zhan[0]] = k;
	if (used[k ^ 1])	return false;
	for (int i = till[k]; i; i = next[i])
		if (!used[go[i]] && !dfs(go[i]))	return false;
	return true;
}

int main() {
	while (scanf("%d%d", &n, &m) != -1) {
		len = 0;
		memset(till, 0, sizeof till);
		memset(ok, false, sizeof ok);
		memset(used, false, sizeof used);
		for (i = 1; i <= 2 * n; i += 2)	add(s(i, 0), s(i + 1, 1)), add(s(i, 1), s(i + 1, 0)), add(s(i + 1, 0), s(i, 1)), add(s(i + 1, 1), s(i, 0));
		while (m--) {
			scanf("%d%d", &a, &b);
			add(s(a, 1), s(b, 0));
			add(s(b, 1), s(a, 0));
		}
		for (i = 1; i <= 2 * n; i++) {
			zhan[0] = 0;
			if (used[s(i, 1)] || dfs(s(i, 1)))	ok[i] = true;
			else {
				for (j = 1; j <= zhan[0]; j++)	used[zhan[j]] = false;
				zhan[0] = 0;
				if (!used[s(i, 0)] && !dfs(s(i, 0)))	break;
			}
		}
		if (i <= 2 * n)	printf("NIE\n");
		else
		for (i = 1; i <= 2 * n; i++)
			if (ok[i])	printf("%d\n", i);
	}
}
