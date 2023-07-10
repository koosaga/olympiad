#include <bits/stdc++.h>
using namespace std;

int n, m, a[1000005], b[1000005], cand[2000005];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		cand[i] = a[i];
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &b[i]);
		cand[i + n] = b[i];
	}
	auto cmp = [&](const int &a, const int &b) { return a > b; };
	sort(a, a + n, cmp);
	sort(b, b + m, cmp);
	sort(cand, cand + n + m, cmp);
	long long rhi = 0, rlo = 0, ca = 0, cb = 0;
	for (int i = 0; i < n + m; i++) {
		int hi = cand[i] - cand[i + 1];
		while (ca < n && a[ca] >= cand[i])
			ca++;
		while (cb < m && b[cb] >= cand[i])
			cb++;
		if (1ll * ca * cb == 0) {
			puts("NIE");
			return 0;
		}
		rhi += hi * (ca * cb);
	}
	printf("%lld\n", rhi);
}