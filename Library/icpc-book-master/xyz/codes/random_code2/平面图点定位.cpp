#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

#define N 200010
#define eps 1e-9

struct aa {
	int x, y;
} pai[N];
struct Point {
	double x, y;
	Point() {
	}
	Point(double _x, double _y) {
		x = _x; y = _y;
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
} p[N], q[N][2];
struct Line {
	Point x, y;
	Line() {
	}
	Line(Point _x, Point _y) {
		x = _x; y = _y;
	}
	inline double f(double X) {
		if (abs(x.x - y.x) < eps && abs(x.y - y.y) < eps)	return x.y;
		return (y.y - x.y) * (X - x.x) / (y.x - x.x) + x.y;
	}
};
map <Line, int> mymap;

int n, m, i, j, len, x, y, h, k, k1, n1, Q, limit, len1, H[N], fa[N][20], ma[N][20], ff[N], ha[N][2], tx[N], to[N], down[N], zhan[N], till[N], f[N], next[N], go[N], next1[N], go1[N], f1[N], till1[N];
bool used[N], Tree[N];
double nowX;

bool operator < (Line a, Line b) {
	return a.f(nowX) < b.f(nowX);
}

bool cmp1(int x, int y) {
	return atan2(p[go[x]].y - p[i].y, p[go[x]].x - p[i].x) < atan2(p[go[y]].y - p[i].y, p[go[y]].x - p[i].x);
}

bool cmp2(aa x, aa y) {
	return q[x.x][x.y].x < q[y.x][y.y].x;
}

bool cmp3(int x, int y) {
	return p[x].x < p[y].x;
}

bool cmp4(int x, int y) {
	return f1[x] < f1[y];
}

void add(int x, int y, int z) {
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
	f[len] = z;
}

void add1(int x, int y, int z) {
	next1[++len1] = till1[x];
	till1[x] = len1;
	go1[len1] = y;
	f1[len1] = z;
}

void FindPlane(int x) {
	if (used[x])	return ;
	to[x] = n1;
	used[x] = true;
	if (p[go[x ^ 1]].x < p[go[x]].x)	down[x] = down[x ^ 1] = n1;
	FindPlane(next[x ^ 1]);
}

int gf(int x) {
	if (ff[x] != x)	ff[x] = gf(ff[x]);
	return ff[x];
}

void dfs(int k, int Fa, int ss) {
	H[k] = H[Fa] + 1;
	ma[k][0] = ss;
	fa[k][0] = Fa;
	for (int i = 1; i <= limit; i++)	fa[k][i] = fa[fa[k][i - 1]][i - 1];
	for (int i = 1; i <= limit; i++)	ma[k][i] = max(ma[k][i - 1], ma[fa[k][i - 1]][i - 1]);
	for (int i = till1[k]; i; i = next1[i])
	if (Tree[i] && go1[i] != Fa)	dfs(go1[i], k, f1[i]);
}

int getmax(int x, int y) {
	int ans = 0;
	if (H[x] < H[y])	swap(x, y);
	for (int i = limit; i >= 0; i--)
	if (H[fa[x][i]] >= H[y])	ans = max(ans, ma[x][i]), x = fa[x][i];
	if (x == y)	return ans;
	for (int i = limit; i >= 0; i--)
	if (fa[x][i] != fa[y][i])	ans = max(ans, ma[x][i]), ans = max(ans, ma[y][i]), x = fa[x][i], y = fa[y][i];
	ans = max(ans, ma[x][0]);
	ans = max(ans, ma[y][0]);
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++)	p[i].read(), p[i].x += p[i].y * eps;
	len = 1;
	for (i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &h);
		add(x, y, h);
		add(y, x, h);
	}
	for (i = 1; i <= n; i++) {
		zhan[0] = 0;
		for (j = till[i]; j; j = next[j])	zhan[++zhan[0]] = j;
		sort(zhan + 1, zhan + zhan[0] + 1, cmp1);
		for (j = 1; j < zhan[0]; j++)	next[zhan[j]] = zhan[j + 1];
		next[zhan[zhan[0]]] = zhan[1];
	}
	n1 = 0;
	for (k = 1, i = 2; i <= n; i++)
	if (p[i].x < p[k].x)	k = i;
	i = till[k];
	k1 = i;
	while (true) {
		if (atan2(p[go[k1]].y - p[k].y, p[go[k1]].x - p[k].x) > atan2(p[go[i]].y - p[k].y, p[go[i]].x - p[k].x))	k1 = i;
		i = next[i];
		if (i == till[k])	break;
	}
	FindPlane(k1);
	for (i = 2; i <= 1 + 2 * m; i++)
	if (!used[i])	n1++, FindPlane(i);
	for (i = 1; i <= n; i++) {
		k = next[till[i]];
		next[till[i]] = 0;
		till[i] = k;
	}
	len1 = 1;
	for (i = 2; i <= 1 + 2 * m; i += 2)	if (to[i] && to[i ^ 1])	add1(to[i], to[i ^ 1], f[i]), add1(to[i ^ 1], to[i], f[i]);

	scanf("%d", &Q);
	for (i = 1; i <= Q; i++) q[i][0].read(), q[i][0].x += q[i][0].y * eps, q[i][1].read(), q[i][1].x += q[i][1].y * eps;
	len = 0;
	for (i = 1; i <= Q; i++)
		for (j = 0; j < 2; j++)
			len++, pai[len].x = i, pai[len].y = j;
	sort(pai + 1, pai + len + 1, cmp2);
	for (i = 1; i <= n; i++)	tx[i] = i;
	sort(tx + 1, tx + n + 1, cmp3);
	mymap[Line(Point(-1e7 + 1e7 * eps, 1e7), Point(1e7 + 1e7 * eps, 1e7))] = 0;
	h = 1;
	nowX = -1e7;
	for (i = 1; i <= n; i++) {
		while (h <= len && q[pai[h].x][pai[h].y].x <= p[tx[i]].x) {
			nowX = q[pai[h].x][pai[h].y].x;
			ha[pai[h].x][pai[h].y] = mymap.upper_bound(Line(q[pai[h].x][pai[h].y], q[pai[h].x][pai[h].y])) -> second;
			h++;
		}
		for (j = till[tx[i]]; j; j = next[j])
		if (p[go[j]].x < p[tx[i]].x)	mymap.erase(Line(p[go[j]], p[tx[i]]));
		nowX = (p[tx[i]].x + p[tx[i + 1]].x) / 2;
		for (j = till[tx[i]]; j; j = next[j])
		if (p[go[j]].x > p[tx[i]].x)	mymap[Line(p[tx[i]], p[go[j]])] = down[j];
	}
	
	for (i = 1; i <= n1; i++) ff[i] = i;
	for (i = 2; i <= len1; i++)	tx[i] = i;
	sort(tx + 2, tx + len1 + 1, cmp4);
	for (i = 2; i <= len1; i++)
	if (gf(go1[tx[i]]) != gf(go1[tx[i] ^ 1])) {
		Tree[tx[i]] = Tree[tx[i] ^ 1] = true;
		ff[gf(go1[tx[i]])] = gf(go1[tx[i] ^ 1]);
	}
	limit = int(log(n1) / log(2));
	dfs(1, 0, 0);

	for (i = 1; i <= Q; i++) {
		if (!ha[i][0] || !ha[i][1])	printf("-1\n");
		else	if (ha[i][0] == ha[i][1])	printf("0\n");
		else	printf("%d\n", getmax(ha[i][0], ha[i][1]));
	}
}
