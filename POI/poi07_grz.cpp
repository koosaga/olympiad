#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXV = MAXN * MAXN;

const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int n;
int a[MAXN][MAXN];
int pa[MAXV];
unsigned char flag[MAXV];
// bit 0: has higher neighbor
// bit 1: has lower neighbor

bool ok(int x, int y) { return x >= 0 && x < n && y >= 0 && y < n; }

int get(int x, int y) { return x * n + y; }

int find(int x) {
	int r = x;
	while (pa[r] >= 0)
		r = pa[r];

	while (x != r) {
		int y = pa[x];
		pa[x] = r;
		x = y;
	}
	return r;
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y)
		return;

	if (pa[x] > pa[y])
		swap(x, y); // x has larger size, since sizes are negative
	pa[x] += pa[y];
	pa[y] = x;
}

int main() {
	scanf("%d", &n);

	int N = n * n;
	for (int i = 0; i < N; i++)
		pa[i] = -1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	// Build components of equal values.
	// Only need to check previous cells in row-major order:
	// left, up-left, up, up-right.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int v = get(i, j);

			if (j > 0 && a[i][j - 1] == a[i][j])
				uni(v, get(i, j - 1));

			if (i > 0) {
				if (a[i - 1][j] == a[i][j])
					uni(v, get(i - 1, j));

				if (j > 0 && a[i - 1][j - 1] == a[i][j])
					uni(v, get(i - 1, j - 1));

				if (j + 1 < n && a[i - 1][j + 1] == a[i][j])
					uni(v, get(i - 1, j + 1));
			}
		}
	}

	// For each component, check whether it has higher/lower neighboring cells.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int r = find(get(i, j));

			for (int d = 0; d < 8; d++) {
				int x = i + dx[d];
				int y = j + dy[d];

				if (ok(x, y)) {
					if (a[x][y] > a[i][j])
						flag[r] |= 1;
					if (a[x][y] < a[i][j])
						flag[r] |= 2;
				}
			}
		}
	}

	int r1 = 0, r2 = 0;

	for (int i = 0; i < N; i++) {
		if (pa[i] < 0) {
			if (!(flag[i] & 1))
				r1++; // no higher neighbor
			if (!(flag[i] & 2))
				r2++; // no lower neighbor
		}
	}

	printf("%d %d\n", r1, r2);
}