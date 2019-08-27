#include <cstdio>
using namespace std;

#define P 1000000007
typedef unsigned long long int64;

int64 n, k, i, j, sum, ans, p, C[30][30], B[30], ss[110000];

int64 Pow(int64 x, int64 y) {
	int64 ans = 1;
	x %= P;
	for (int64 i = 1; i <= y; i *= 2, x = x * x % P)	if (i & y)	ans = ans * x % P;
	return ans;
}

int main() {
	scanf("%llu%llu", &n, &k);
	for (C[0][0] = 1, i = 1; i <= 20; i++)
		for (C[i][0] = 1, j = 1; j <= i; j++)	C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
	for (B[0] = 1, i = 1; i <= 20; i++) {
		for (sum = 0, j = 0; j < i; j++)	sum = (sum + C[i + 1][j] * B[j]) % P;
		B[i] = (P - sum) * Pow(C[i + 1][i], P - 2) % P;
	}
	for (i = 1; i <= n; i++) {
		scanf("%llu", &p);
		p %= P;
		for (sum = 0, j = 0; j <= k; j++)	sum = (sum + C[k + 1][j] * B[j] % P * Pow(p + 2, k + 1 - j)) % P;
		sum = sum * Pow(k + 1, P - 2) % P;
		ans = ans * sum % P;
	}
}