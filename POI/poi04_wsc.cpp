#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, e, w;

// CSR adjacency
int head[MAXN + 5];
int adj[2 * MAXN + 5];

// Reused arrays
int buf1[MAXN + 5]; // deg -> ptr -> cnt
int buf2[MAXN + 5]; // edge_u -> parent -> vl
int buf3[MAXN + 5]; // edge_v -> order -> vr
int dep[MAXN + 5];

int main() {
	scanf("%d %d %d", &n, &e, &w);

	for (int i = 0; i < n - 1; i++) {
		int s, t;
		scanf("%d %d", &s, &t);
		buf2[i] = s;
		buf3[i] = t;
		buf1[s]++;
		buf1[t]++;
	}

	head[1] = 0;
	for (int i = 1; i <= n; i++) {
		head[i + 1] = head[i] + buf1[i];
	}

	for (int i = 1; i <= n; i++) {
		buf1[i] = head[i]; // ptr
	}

	for (int i = 0; i < n - 1; i++) {
		int s = buf2[i];
		int t = buf3[i];
		adj[buf1[s]++] = t;
		adj[buf1[t]++] = s;
	}

	// buf1 is now cnt
	memset(buf1, 0, sizeof(int) * (n + 2));

	int *cnt = buf1;
	int *par = buf2;
	int *ord = buf3;

	// iterative dfs from 1
	int osz = 0;
	ord[osz++] = 1;
	par[1] = 0;
	dep[1] = 0;

	for (int it = 0; it < osz; it++) {
		int x = ord[it];
		for (int p = head[x]; p < head[x + 1]; p++) {
			int y = adj[p];
			if (y == par[x]) continue;
			par[y] = x;
			dep[y] = dep[x] + 1;
			ord[osz++] = y;
		}
	}

	int cur = -1, pos = 1;

	for (int it = osz - 1; it >= 0; it--) {
		int x = ord[it];
		cnt[x] += (x >= n - w + 1);

		if (cnt[x] == w && cur < dep[x]) {
			cur = dep[x];
			pos = x;
		}

		if (par[x]) cnt[par[x]] += cnt[x];
	}

	// iterative dfs from pos, overwrite dep with dep2
	osz = 0;
	ord[osz++] = pos;
	par[pos] = 0;
	dep[pos] = 0;

	for (int it = 0; it < osz; it++) {
		int x = ord[it];
		for (int p = head[x]; p < head[x + 1]; p++) {
			int y = adj[p];
			if (y == par[x]) continue;
			par[y] = x;
			dep[y] = dep[x] + 1;
			ord[osz++] = y;
		}
	}

	int *vl = buf2;
	int *vr = buf3;

	for (int i = 0; i < w; i++) {
		vl[i] = dep[n - w + 1 + i];
	}

	int q;
	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		int x;
		scanf("%d", &x);
		vr[i] = dep[x];
	}

	sort(vl, vl + w);
	sort(vr, vr + q);

	int low = -1;
	for (int i = 0; i < q; i++) {
		if (low < vl[i]) {
			low = vl[i];
		} else {
			low++;
			vl[i] = low;
		}
	}

	low = -1;
	for (int i = 0; i < q; i++) {
		if (low < vr[i]) {
			low = vr[i];
		} else {
			low++;
			vr[i] = low;
		}
	}

	int ret = 0;
	for (int i = 0; i < q; i++) {
		ret = max(ret, vl[i] + vr[q - i - 1]);
	}

	printf("%d\n", ret);
}