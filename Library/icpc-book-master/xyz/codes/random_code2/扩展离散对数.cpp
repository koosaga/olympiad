/*
	x^? mod z=y
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF 2000000000
#define max(x, y) ((x) > (y) ? (x) : (y))
int y, i, x, z, t, tmp, ha[3700000], ma[3700000], zhan[1000000];

int gcd(int x, int y) {
	if (!x)	return y;
	return gcd(y % x, x);
}

int Pow(int x, int y, int z) {
	int ans = 1;
	for (int i = 1; i <= y; i *= 2, x = 1LL * x * x % z)	if (i & y)	ans = 1LL * ans * x % z;
	return ans;
}

void ext_gcd(int a, int b, int c, int &x, int &y) {
	if (!a) {
		x = 0;
		y = c / b;
	}else {
		int t;
		ext_gcd(b % a, a, c % a, y, t);
		x = c / a - b / a * y + t;
	}
}

int hash(int x) {
	int p = x % 2999951, t = x % 19 + 1;
	while (ha[p] && ha[p] != x)	p += t;
	ha[p] = x;
	return p;
}

int solve(int a, int b, int c) {
	int r = 0, g = 1, t, x, y, d = 1, now, base, limit, ans, i;
	while (gcd(a, c) != 1) {
		t = gcd(a, c);
		if (b % t != 0)	return -1;
		r++; g *= t; b /= t; c /= t;
		d = 1LL * d * a / t % c;
	}
	if (gcd(c, d) > 1)	return -1;
	ext_gcd(d, c, 1, x, y);
	b = 1LL * b * x % c;
	b = (b + c) % c;

	limit = int(sqrt(double(c))) + 1;
	for (now = b, i = 0; i <= limit; i++, now = 1LL * now * a % c) {
		d = hash(now + 1);
		ma[d] = max(ma[d], i + 1);
		zhan[++zhan[0]] = d;
	}
	ans = INF;

	for (base = now = Pow(a, limit, c), i = limit; i <= c + limit; i += limit, now = 1LL * now * base % c) {
		d = hash(now + 1);
		zhan[++zhan[0]] = d;
		if (ma[d]) {
			ans = i - ma[d] + 1 + r;
			for (int i = 1; i <= zhan[0]; i++)	ma[zhan[i]] = ha[zhan[i]] = 0;
			zhan[0] = 0;
			return ans;
		}
	}

	for (int i = 1; i <= zhan[0]; i++)	ma[zhan[i]] = ha[zhan[i]] = 0;
	zhan[0] = 0;

	return -1;
}

int main() {
	// freopen("math.in", "r", stdin);
	// freopen("math.out", "w", stdout);
	while (scanf("%d%d%d", &x, &z, &y), x || y || z) {
		for (i = 0; i <= 50; i++)
		if (Pow(x, i, z) == y) {
			break;
		}
		if (i <= 50) {
			printf("%d\n", i);
			continue;
		}
		
		tmp = solve(x, y, z);
		if (tmp < 0)	printf("No Solution\n");
		else	printf("%d\n", tmp);
	}
}
