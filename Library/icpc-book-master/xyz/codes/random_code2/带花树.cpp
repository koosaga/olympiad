#include <cstdio>
#include <vector>
using namespace std;

#define N 230
int n, a, b, x, ans, i, h, to[N], to1[N], next[N], fa[N], se[N], n1[N], t1[N], t2[N];
vector <int> ve[N];
bool used[N];

void pei(int x) {
	if (next[x]) {
		int y = next[x];
		to1[y] = to[y];
		to[y] = x;
		to[x] = y;
		next[y] = next[x] = 0;
		pei(y);
	}else	if (to1[x])	pei(to1[x]);
}

int gf(int x) {
	if (fa[x] != x)	fa[x] = gf(fa[x]);
	return fa[x];
}

void goup(int x, int y) {
	while (x != y) {
		int a = to[x], b = next[a];
		if (gf(b) != y)	next[b] = a;
		if (se[a] == 1)	n1[++h] = a, used[a] = true, se[a] = 0;
		if (se[b] == 1)	n1[++h] = b, used[b] = true, se[b] = 0;
		if (gf(x) != gf(a))	fa[gf(x)] = a;
		if (gf(a) != gf(b))	fa[gf(a)] = b;
		x = b;
	}
}

bool Find(int x) {
	int i, q;
	for (i = 1; i <= n; i++)	next[i] = to1[i] = se[i] = used[i] = 0;
	for (i = 1; i <= n; i++)	fa[i] = i;
	for (n1[q = h = 1] = x, se[x] = 0, used[x] = true; q <= h; q++) {
		for (i = 0; i < ve[n1[q]].size(); i++) {
			int k = ve[n1[q]][i];
			if (!used[k] && !se[k]) {
				if (!to[k]) {
					to[k] = n1[q];
					if (to[n1[q]])	pei(to[n1[q]]);
					to[n1[q]] = k;
					return true;
				}else {
					n1[++h] = to[k];
					used[to[k]] = true;
					se[to[k]] = 0;
					next[k] = n1[q];
					se[k] = 1;
				}
			}else	if (se[k] == 0 && gf(k) != gf(n1[q])) {
				int y = gf(k), len1 = 0, len2 = 0;
				while (y)	t1[++len1] = y, y = gf(next[to[y]]);
				y = gf(n1[q]);
				while (y)	t2[++len2] = y, y = gf(next[to[y]]);
				for (y = 0; t1[len1 - y] == t2[len2 - y]; y++);
				y = t1[len1 - y + 1];
				if (gf(k) != y)	next[k] = n1[q];
				if (gf(n1[q]) != y)	next[n1[q]] = k;
				goup(k, y);
				goup(n1[q], y);
			}
		}
	}

	return false;
}

int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d", &n);
	while (scanf("%d%d", &a, &b) != -1) {
		if (a == b)	continue;
		ve[a].push_back(b);
		ve[b].push_back(a);
	}
	for (i = 1; i <= n; i++) {
		// for (int j = 1; j <= n; j++)	printf("%d ", to[j]);
		// printf("\n");
		if (!to[i] && Find(i)) 	ans += 2;
	}
	printf("%d\n", ans);
	for (i = 1; i <= n; i++)
		if (to[i])	printf("%d %d\n", i, to[i]), x = to[i], to[x] = to[i] = 0;
}