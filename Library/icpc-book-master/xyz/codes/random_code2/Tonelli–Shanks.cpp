#include <cstdio>
#include <algorithm>
using namespace std;

bool used[11000000];
long long Ans, n;

int Pow(int x, int y, int z) {
	int ans = 1;
	for (int i = 1; i <= y; i *= 2, x = 1LL * x * x % z)	if (i & y)	ans = 1LL * ans * x % z;
	return ans;
}

long long solve(int x, int p) {
	long long b = (1LL * p * p - 1LL * x * x + 3 * x + 1) % (1LL * p * p) / p, a = (2LL * x * p - 3 * p) % (1LL * p * p) / p;
	b = (b + p) % p;
	a = (a + p) % p;
	if (!a) {
		if (!b)	return x;
		else	return 1000000000000000000LL;
	}else	return 1LL * b * Pow(a, p - 2, p) % p * p + x;
}

long long solve2(int x, int p) {
	if ((x + 3) % 2 == 0)	return solve((x + 3) / 2, p);
	else	return solve((x + 3 + p) / 2, p);
}

long long solve1(long long p) {
	if (Pow(13, (p - 1) / 2, p) != 1)	return 1000000000000000000LL;
	long long n = 13, Q, S, z, R, t, M, c, b;
	for (Q = p - 1, S = 0; Q % 2 == 0; Q /= 2, S++);
	for (z = 1; Pow(z, (p - 1) / 2, p) == 1; z++);
	c = Pow(z, Q, p);
	R = Pow(n, (Q + 1) / 2, p);
	t = Pow(n, Q, p);
	M = S;
	while (t != 1) {
		long long i;
		for (i = 1; i < M; i++)	if (Pow(t, (1 << i), p) == 1)	break;
		b = Pow(c, (1 << (M - i - 1)), p);
		R = R * b % p;
		t = t * b % p * b % p;
		c = b * b % p;
		M = i;
	}
	return min(solve2(R, p), solve2(p - R, p));
}

int main() {
	scanf("%lld", &n);
	for (int i = 2; i <= n; i++)
		if (!used[i])
			for (int j = 2 * i; j <= n; j += i)	used[j] = true;
	for (int i = 2; i <= n && i <= 13; i++) if (!used[i]) {
		long long ans = 1000000000000000000LL;
		for (int j = 1; j <= i; j++)
			if ((j * j - 3 * j - 1) % i == 0)	ans = min(ans, solve(j, i));
		if (ans < 1000000000000000000LL)	Ans += ans;
	}
	for (int i = 14; i <= n; i++)	if (!used[i]) {
		long long tmp = solve1(i);
		if (tmp < 1000000000000000000LL)	Ans += tmp;
	}
	printf("%lld\n", Ans);
}
