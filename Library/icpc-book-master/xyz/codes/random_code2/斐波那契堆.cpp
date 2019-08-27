#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

struct T {
	long long dat;
	int du, to;
	bool mark;
	T *next, *prep, *fa, *son;
} f[1100000], *f1 = f, *root, *null, *Q[1000], *ff[1100000];

int Limit;

void Link(T *x, T *&y) {
	if (y == null)	y = x, y -> prep = y -> next = x;
	else {
		y -> prep -> next = x;
		x -> prep = y -> prep;
		y -> prep = x;
		x -> next = y;
	}
}

void del(T *x) {
	T *y = x -> fa;
	y -> du--;
	if (x -> next == x)	y -> son = null;
	else {
		if (x == y -> son)	y -> son = x -> next;
		x -> next -> prep = x -> prep;
		x -> prep -> next = x -> next;
	}
}

void Insert(long long x) {
	T *p = ++f1;
	p -> son = p -> fa = null;
	p -> du = p -> mark = 0;
	p -> dat = x;
	Link(p, root);
	if (p -> dat < root -> dat)	root = p;
}

int GetMin() {
	return root -> dat;
}

T *Merge(T *x, T *y) {
	if (x -> dat < y -> dat) {
		Link(y, x -> son);
		y -> fa = x;
		x -> du++;
		return x;
	}
	else {
		Link(x, y -> son);
		x -> fa = y;
		y -> du++;
		return y;
	}
}

void Extract() {
	T *p;
	for (p = root -> next; p != root; p = p -> next) {
		p -> prep = Q[p -> du];
		Q[p -> du] = p;
	}
	if (root -> son != null)
	for (p = root -> son; ;) {
		p -> prep = Q[p -> du];
		Q[p -> du] = p;
		p -> mark = false;
		p = p -> next;
		if (p == root -> son)	break;
	}
	root = null;
	for (int i = 0; i <= Limit; i++)
	while (Q[i] != null) {
		if (Q[i] -> prep != null) {
			p = Q[i] -> prep -> prep;
			Q[i] = Merge(Q[i], Q[i] -> prep);
			Q[i] -> prep = Q[Q[i] -> du];
			Q[Q[i] -> du] = Q[i];
			Q[i] = p;
		}else {
			Link(Q[i], root);
			if (Q[i] -> dat < root -> dat)	root = Q[i];
			Q[i] -> fa = null;
			Q[i] = null;
		}
	}
}

void Derease(T *p, int x) {
	p -> dat = x;
	if (p -> fa == null) {
		if (p -> dat < root -> dat)	root = p;
	}else	if (p -> dat < p -> fa -> dat) {
		del(p);
		Link(p, root);
		p -> mark = false;
		if (p -> dat < root -> dat)	root = p;
		while (p -> fa -> fa != null && p -> fa -> mark) {
			T *q = p -> fa;
			p -> fa = null;
			del(q);
			Link(q, root);
			q -> mark = false;
			p = q;
		}
		p -> fa -> mark = true;
		p -> fa = null;
	}
}

#define N 1100000
#define M 11000000
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
int n, m, a, b, c, x, y, rxa, rxc, rya, ryc, rp, len, i, k, j, TT, till[N], go[M], fei[M], next[M];
T *to[N];
long long mi[N];

void add(int x, int y, int z) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
	fei[len] = z;
}

int main() {
	// freopen("xx.in", "r", stdin);
	null = new T;
	null -> next = null -> prep = null -> son = null -> fa = null;
	null -> du = null -> mark = 0;
	null -> dat = 2000000000000000000LL;
	root = null;
	Limit = 30;
	for (i = 0; i <= Limit; i++)	Q[i] = null;

	//begin write here
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d%d%d", &TT, &rxa, &rxc, &rya, &ryc, &rp);
	for (i = 1; i <= TT; i++) {
		x = (1LL * x * rxa + rxc) % rp;
		y = (1LL * y * rya + ryc) % rp;
		a = min(x % n + 1, y % n + 1);
		b = max(x % n + 1, y % n + 1);
		add(a, b, 100000000 - 100 * a);
	}
	for (i = 1; i <= m - TT; i++) {
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
	}
	for (i = 1; i <= n; i++) {
		mi[i] = 2000000000000000000LL;
		Insert(mi[i]);
		to[i] = f1;
		f1 -> to = i;
	}
	mi[1] = 0;
	Derease(to[1], 0);
	for (i = 1; i <= n; i++) {
		k = root -> to;
		Extract();
		for (j = till[k]; j; j = next[j])
			if (mi[k] + fei[j] < mi[go[j]]) {
				mi[go[j]] = mi[k] + fei[j];
				Derease(to[go[j]], mi[go[j]]);
			}
	}
	printf("%lld\n", mi[n]);
}
