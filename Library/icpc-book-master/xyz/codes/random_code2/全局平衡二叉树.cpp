#include <cstdio>
#include <algorithm>
using namespace std;

#define N 61000
int n, i, a, b, len, q, x, y, w[N], till[N], go[N], next[N], zhan[N], S[N], z[N], son[N][2], ss[N], ma[N], sum[N], sum1[N], root[N], F[N], fa[N], d[N], n1[N];
bool used[N];
char SS[100];

void add(int x, int y) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
}

void update(int k) {
	ma[k] = max(ma[son[k][0]], ma[son[k][1]]);
	ma[k] = max(ma[k], z[k]);
	sum[k] = sum[son[k][0]] + sum[son[k][1]] + z[k];
}

void mkt(int &k, int q, int h) {
	k = ++len;
	ss[k] = h - q + 1;
	int mid, s = S[h] - S[q - 1];
	for (mid = q; mid <= h; mid++)	if (S[mid - 1] - S[q - 1] <= s / 2 && S[h] - S[mid] <= s / 2)	break;
	z[k] = w[zhan[mid]];
	if (q < mid)	mkt(son[k][1], q, mid - 1);
	if (mid < h)	mkt(son[k][0], mid + 1, h);
	update(k);
}

void modify(int k, int x, int y) {
	if (x <= ss[son[k][0]])	modify(son[k][0], x, y), update(k);
	else	if (x > ss[son[k][0]] + 1) modify(son[k][1], x - ss[son[k][0]] - 1, y), update(k);
	else	z[k] = y, update(k);
}

int quesum(int k, int x, int y) {
	int sum1 = 0, s = ss[son[k][0]];
	if (x == 1 && y == ss[k])	return sum[k];
	if (x <= s + 1 && y >= s + 1)	sum1 = z[k];
	if (x <= s)	sum1 += quesum(son[k][0], x, min(y, s));
	if (y > s + 1)	sum1 += quesum(son[k][1], max(x - s - 1, 1), y - s - 1);
	return sum1;
}


int quemax(int k, int x, int y) {
	int ma1 = -31000, s = ss[son[k][0]];
	if (x == 1 && y == ss[k])	return ma[k];
	if (x <= s + 1 && y >= s + 1)	ma1 = z[k];
	if (x <= s)	ma1 = max(ma1, quemax(son[k][0], x, min(y, s)));
	if (y > s + 1)	ma1 = max(ma1, quemax(son[k][1], max(x - s - 1, 1), y - s - 1));
	return ma1;
}

int getsum(int x, int y) {
	int sum = 0;
	while (F[x] != F[y]) {
		if (d[F[x]] >= d[F[y]])	sum += quesum(root[F[x]], 1, d[x] - d[F[x]] + 1), x = fa[F[x]];
		else	sum += quesum(root[F[y]], 1, d[y] - d[F[y]] + 1), y = fa[F[y]];
	}
	if (d[x] > d[y])	swap(x, y);
	sum += quesum(root[F[y]], d[x] - d[F[x]] + 1, d[y] - d[F[y]] + 1);
	return sum;
}

int getmax(int x, int y) {
	int ma = -31000;
	while (F[x] != F[y]) {
		if (d[F[x]] >= d[F[y]])	ma = max(ma, quemax(root[F[x]], 1, d[x] - d[F[x]] + 1)), x = fa[F[x]];
		else	ma = max(ma, quemax(root[F[y]], 1, d[y] - d[F[y]] + 1)), y = fa[F[y]];
	}
	if (d[x] > d[y])	swap(x, y);
	ma = max(ma, quemax(root[F[y]], d[x] - d[F[x]] + 1, d[y] - d[F[y]] + 1));
	return ma;
}

void bfs() {
	int q, h, i, j, k;
	for (n1[q = h = 1] = 1, used[1] = true, d[1] = 1; q <= h; q++)
		for (i = till[n1[q]]; i; i = next[i])	if (!used[go[i]])	used[n1[++h] = go[i]] = true, d[go[i]] = d[n1[q]] + 1, fa[go[i]] = n1[q];
	for (i = n; i; i--)
		for (sum1[n1[i]]++, used[n1[i]] = false, j = till[n1[i]]; j; j = next[j])
			if (used[go[j]])	sum1[go[j]] += sum1[n1[i]];
	for (i = 1; i <= n; i++) {
		if (!F[n1[i]])	F[n1[i]] = n1[i];
		if (sum1[n1[i]] > 1) {
			for (k = 0, j = till[n1[i]]; j; j = next[j])
				if (d[go[j]] > d[n1[i]] && (!k || sum1[k] < sum1[go[j]]))	k = go[j];
			F[k] = F[n1[i]];
			sum1[n1[i]] -= sum1[k];
		}else {
			k = n1[i]; h = 0;
			while (F[k] == F[n1[i]]) {
				zhan[++h] = k;
				S[h] = S[h - 1] + sum1[k];
				k = fa[k];
			}
			mkt(root[F[n1[i]]], 1, h);
		}
	}
}

int main() {
	scanf("%d", &n);
	for (i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	len = 0;
	for (i = 1; i <= n; i++)	scanf("%d", &w[i]);
	ma[0] = -31000;
	bfs();
	scanf("%d", &q);
	while (q--) {
		scanf("%s%d%d", SS, &x, &y);
		if (SS[1] == 'H')	modify(root[F[x]], d[x] - d[F[x]] + 1, y);
		else	if (SS[1] == 'M')	printf("%d\n", getmax(x, y));
		else	printf("%d\n", getsum(x, y));
	}
}
