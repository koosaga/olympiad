#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef long long int64;
struct T {
	int x, height, min, to;
	int64 l, r, mid;
	T *son[2];
} f2[110000], *f1 = f2, *f[110000], *null, *root, *next, *prep;

int i, TT, n;
char S[110000];
int64 ans;

bool g(T *x, T *y) {
	if (S[x -> to] != S[y -> to])	return S[x -> to] < S[y -> to];
	return f[x -> to + 1] -> mid < f[y -> to + 1] -> mid;
}

int query(T *x, int64 l, int64 r) {
	if (x == null || r < x -> l || l > x -> r)	return 1000000000;
	if (l <= x -> l && r >= x -> r)	return x -> min;
	int s = 1000000000;
	if (l <= x -> mid && r >= x -> mid)	s = x -> height;
	s = min(s, query(x -> son[0], l, r));
	s = min(s, query(x -> son[1], l, r));
	return s;
}

int calc(int x, int y) {
	if (S[x] != S[y])	return 0;
	return query(root, f[x + 1] -> mid + 1, f[y + 1] -> mid) + 1;
}

void update(T *x) {
	x -> min = min(x -> height, min(x -> son[0] -> min, x -> son[1] -> min));
}

void rotate(T *&x, bool t) {
	T *y = x -> son[t];
	x -> son[t] = y -> son[!t];
	y -> son[!t] = x;
	update(x);
	y -> l = x -> l;
	y -> r = x -> r;
	x = y;
}

void insert(T *&k, T *y, int64 l, int64 r) {
	if (k == null) {
		y -> x = rand();
		y -> l = l;
		y -> r = r;
		y -> mid = (l + r) >> 1;
		y -> height = calc(prep -> to, y -> to);
		if (next != null)	next -> height = calc(y -> to, next -> to);
		y -> min = y -> height;
		y -> son[0] = y -> son[1] = null;
		k = y;
	}else	if (g(k, y)) {
		prep = k;
		insert(k -> son[1], y, k -> mid, k -> r);
		if (k -> son[1] -> x > k -> x)	rotate(k, 1);
		update(k);
	}else {
		next = k;
		insert(k -> son[0], y, k -> l, k -> mid);
		if (k -> son[0] -> x > k -> x)	rotate(k, 0);
		update(k);
	}
}

void dfs(T *x, int64 l, int64 r) {
	x -> l = l;
	x -> r = r;
	x -> mid = (l + r) >> 1;
	if (x -> son[0] != null)	dfs(x -> son[0], l, x -> mid);
	if (x -> son[1] != null)	dfs(x -> son[1], x -> mid, r);
}

int main() {
	null = new T;
	null -> son[0] = null -> son[1] = null;
	null -> min = 1000000000;
	null -> x = -1;
	for (i = 0; i <= 100000; i++)	f[i] = ++f1, f[i] -> to = i;
	scanf("%d", &TT);
	while (TT--) {
		scanf("%s", S);
		n = strlen(S);
		S[n] = 0;
		root = f[n];
		root -> x = rand();
		root -> l = -1000000000000000000LL; root -> r = 1000000000000000000LL; root -> mid = 0;
		root -> height = 0;
		root -> min = 0;
		root -> son[0] = root -> son[1] = null;
		for (i = n - 1; i >= 0; i--) {
			next = prep = null;
			insert(root, f[i], -1000000000000000000LL, 1000000000000000000LL);
			dfs(f[i], f[i] -> l, f[i] -> r);
		}
		for (ans = 0, i = 0; i < n; i++)	ans += n - i - f[i] -> height;
		printf("%lld\n", ans);
	}
}