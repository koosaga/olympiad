#include <bits/stdc++.h>
using namespace std;

#define N 4100000
int root, n, m, len, x[N];
char S[1100];


struct T{
	int value, size, sum;
	int left_max, right_max, max_sum;
	bool rr, same;
	int same_value;
	int fa, son[2];

	void update();
	void downdate();
} a[N];

void T::update() {
	if (son[0] != 0)
		a[son[0]].downdate();
	if (son[1] != 0)
		a[son[1]].downdate();
	T *l = &a[son[0]], *r = &a[son[1]];
	size = l->size + r->size + 1;
	sum = l->sum + r->sum + value;
	left_max = max(l->left_max, l->sum +value + r->left_max);
	right_max = max(r->right_max, r->sum + value + l->right_max);
	max_sum = max(l->max_sum, max(r->max_sum, l->right_max + value + r->left_max));
}

void T::downdate() {
	if (this == &a[0])
		return ;
	if (rr) {
		swap(son[0], son[1]);
		a[son[0]].rr ^= 1;
		a[son[1]].rr ^= 1;
		swap(left_max, right_max);
		rr = false;
	}
	if (same) {
		value = same_value;
		sum = size * same_value;
		left_max = max(0, sum);
		right_max = max(0, sum);
		max_sum = max(same_value, sum);
		a[son[0]].same = true;
		a[son[0]].same_value = same_value;
		a[son[1]].same = true;
		a[son[1]].same_value = same_value;
		same = false;
	}
}

void rotate(int x, int t, int &root) {
	int y = a[x].fa, z = a[y].fa;
	a[x].fa = a[y].fa;
	if (y == root) {
		root = x;
	}else {
		a[z].son[y == a[z].son[1]] = x;
	}

	a[y].son[t] = a[x].son[1 - t];
	a[a[x].son[1 - t]].fa = y;
	a[x].son[1 - t] = y;
	a[y].fa = x;
	a[y].update();
	a[x].update();
}

void splay(int x, int &root) {
	int y, z;
	while (x != root) {
		y = a[x].fa;
		z = a[y].fa;
		int t1 = (x == a[y].son[1]), t2 = (y == a[z].son[1]);
		if (y == root)
			rotate(x, t1, root);
		else if (t1 == t2) {
			rotate(y, t2, root);
			rotate(x, t2, root);
		}else {
			rotate(x, t1, root);
			rotate(x, t2, root);
		}
	}
}

int get(int k, int x) {
	a[k].downdate();
	if (x <= a[a[k].son[0]].size)
		return get(a[k].son[0], x);
	else if (x == a[a[k].son[0]].size + 1)
		return k;
	else
		return get(a[k].son[1], x - a[a[k].son[0]].size - 1);
}

int maketree(int l, int r) {
	int mid = (l + r) / 2;
	int k = ++len;
	a[k].value = x[mid];
	if (l < mid)
		a[k].son[0] = maketree(l, mid - 1), a[a[k].son[0]].fa = k;
	if (mid < r)
		a[k].son[1] = maketree(mid + 1, r), a[a[k].son[1]].fa = k;
	a[k].update();
	return k;
}

void GET(int l, int r) {
	l++;
	r++;
	splay(get(root, l), root);
	splay(get(root, r), a[root].son[1]);
	assert (get(root, l) == root);
	assert (get(root, r) == a[root].son[1]);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		len = 0;
		memset(a, 0, sizeof a);
		a[0].max_sum = -1000000000;

		scanf("%d%d", &n, &m);
		x[0] = 0;
		x[n + 1] = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &x[i]);
		root = maketree(0, n + 1);
		while (m--) {
			scanf("%s", S);
			if (S[0] == 'I') {
				int i, t;
				scanf("%d%d", &i, &t);
				for (int j = 1; j <= t; j++)
					scanf("%d", &x[j]);
				GET(i, i + 1);
				int k = maketree(1, t);
				assert (a[a[root].son[1]].son[0] == 0);
				a[a[root].son[1]].son[0] = k;
				a[k].fa = a[root].son[1];
				a[a[root].son[1]].update();
				a[root].update();
			}else if (S[0] == 'D') {
				int i, t;
				scanf("%d%d", &i, &t);
				GET(i - 1, i + t);
				a[a[root].son[1]].son[0] = 0;
				a[a[root].son[1]].update();
				a[root].update();
			}else if (S[0] == 'R') {
				int i, t;
				scanf("%d%d", &i, &t);
				GET(i - 1, i + t);
				a[a[a[root].son[1]].son[0]].rr ^= 1;
				a[a[root].son[1]].update();
				a[root].update();
			}else if (S[0] == 'G') {
				int i, t;
				scanf("%d%d", &i, &t);
				GET(i - 1, i + t);

				a[a[a[root].son[1]].son[0]].downdate();
				printf("%d\n", a[a[a[root].son[1]].son[0]].sum);
			}else if (S[2] == 'K') {

				int i, t, c;
				scanf("%d%d%d", &i, &t, &c);
				GET(i - 1, i + t);
				a[a[a[root].son[1]].son[0]].same = true;
				a[a[a[root].son[1]].son[0]].same_value = c;
			}else if (S[2] == 'X') {
				GET(0, a[root].size - 1);

				a[a[a[root].son[1]].son[0]].downdate();
				printf("%d\n", a[a[a[root].son[1]].son[0]].max_sum);
			}else {
				assert(false);
			}
		}
	}
}
