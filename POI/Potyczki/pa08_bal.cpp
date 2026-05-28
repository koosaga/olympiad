// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int fuck[MAXN];
int n, m, a[MAXN], b[MAXN], c[MAXN], sa[MAXN];

void Do(int x) {
	if (x <= n)
		fuck[x] = c[x] - sa[n + 1 - x];
}

int main() {
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		sa[i] = a[i];
	}
	for (int i = 1; i <= m; i++) {
		c[b[i]]++;
	}
	for (int i = MAXN - 2; i >= 0; i--)
		c[i] += c[i + 1];
	sort(sa + 1, sa + n + 1);
	for (int i = 1; i <= n; i++)
		Do(i);
	lint sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += fuck[i];
		if (sum < 0) {
			cout << "NIE\n";
			return 0;
		}
	}
	cout << "TAK\n";
}
