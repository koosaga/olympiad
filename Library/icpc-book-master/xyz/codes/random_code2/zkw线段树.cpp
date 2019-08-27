#include <cstdio>
#include <algorithm>
using namespace std;

int n, Q, M, i, x, y, t, a[410000];
char k;

void read(int &x) {
	char k;
	bool fu = false;
	for (k = getchar(); k <= 32; k = getchar());
	if (k == '-')	fu = true, k = getchar();
	for (x = 0; '0' <= k; k = getchar())	x = x * 10 + k - '0';
	if (fu)	x = -x;
}

void modify(int x, int y, int t) {
	int A;
	for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (~x & 1)	a[x ^ 1] += t;
		if (y & 1)	a[y ^ 1] += t;
		A = max(a[x], a[x ^ 1]), a[x] -= A, a[x ^ 1] -= A, a[x >> 1] += A;
		A = max(a[y], a[y ^ 1]), a[y] -= A, a[y ^ 1] -= A, a[y >> 1] += A;
	}
	for (; x > 1; x >>= 1)	A = max(a[x], a[x ^ 1]), a[x] -= A, a[x ^ 1] -= A, a[x >> 1] += A;
}

int query(int x, int y) {
	int lans = -2000000000, rans = -2000000000, ans;
	for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
		lans += a[x]; rans += a[y];
		if (~x & 1)	lans = max(lans, a[x ^ 1]);
		if (y & 1)	rans = max(rans, a[y ^ 1]);
	}
	ans = max(lans + a[x], rans + a[y]);
	while (x > 1)	ans += a[x >>= 1];
	return ans;
}

int main() {
	read(n); read(Q);
	for (M = 1; M < n + 2; M *= 2);
	for (i = 1; i <= n; i++)	read(a[i + M]);
	for (i = M - 1; i; i--)	a[i] = max(a[i + i], a[i + i + 1]);
	for (i = M * 2 - 1; i; i--)	a[i] -= a[i / 2];
	while (Q--) {
		for (k = getchar(); k <= 32; k = getchar());
		if (k == 'C') {
			read(x); read(y); read(t);
			modify(x, y, t);
		}else	read(x), read(y), printf("%d\n", query(x, y));
	}
}
