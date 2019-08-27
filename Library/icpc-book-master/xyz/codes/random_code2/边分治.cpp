#include <cstdio>
#include <memory.h>
#include <algorithm>
using namespace std;
#define N 200000
#define INF 1000000000
int m, n, a, b, c, mi, w, len, len1, i, j, ROOT, ll, lll, r, s, sum[N], till[N], du[N], next[N * 2], go[N * 2], till1[N], next1[N * 2], go1[N * 2], f[N * 2], f1[N * 2];
int zhan[N], high[N], to[N][20], ffa[N][20], l[N][20], ma[N * 20], son[N * 20][2], fa[N * 20], z[N * 20], FA[N * 2], MA[N * 2], SON[N * 2][2], ans[N * 2], ff[N * 2], root[N * 2][2];
bool used[N], white[N];
char k;

void read(int &x){
	bool fu = false;
	char k;
	for (k = getchar(); k <= 32; k = getchar());
	if (k == '-')	fu = true, k = getchar();
	for (x = 0; '0' <= k; k = getchar())	x = x * 10 + k - '0';
	if (fu)	x = -x;
}

void add(int x, int y, int z){
	next[++len] = till[x];
	till[x] = len;
	go[len] = y;
	f[len] = z;
}

void add1(int x, int y, int z){
	du[x]++;
	next1[++len1] = till1[x];
	till1[x] = len1;
	go1[len1] = y;
	f1[len1] = z;
}

void dfs1(int x, int fa){
	for (int i = till[x]; i; i = next[i])
	if (go[i] != fa)	add1(x, go[i], f[i]), dfs1(go[i], x);
}

void make_new_tree(int k){
	while (du[k] > 2){
		int p1 = go1[till1[k]], p2 = go1[next1[till1[k]]];
		n++;
		add1(n, p1, f1[till1[k]]); add1(n, p2, f1[next1[till1[k]]]);
		till1[k] = next1[next1[till1[k]]];
		du[k] -= 2;
		add1(k, n, 0);
	}
	for (int i = till1[k]; i; i = next1[i])	make_new_tree(go1[i]);
}

void dfs_sum(int k, int h){
	sum[k] = 1;
	ffa[k][h] = ll;
	used[k] = true;
	for (int i = till[k]; i; i = next[i])
	if (!used[go[i]])	dfs_sum(go[i], h), sum[k] += sum[go[i]];
	used[k] = false;
}

void dfs_calc(int k, int S){
	used[k] = true;
	for (int i = till[k]; i; i = next[i])
	if (!used[go[i]]){
		if (abs(2 * sum[go[i]] - S) < mi){
			mi = abs(2 * sum[go[i]] - S);
			a = k;
			b = go[i];
			c = f[i];
		}
		dfs_calc(go[i], S);
	}
	used[k] = false;
}

void dfs_l(int k, int ll, int h){
	zhan[++r] = k;
	l[k][h] = ll;
	used[k] = true;
	for (int i = till[k]; i; i = next[i])
	if (!used[go[i]])	dfs_l(go[i], ll + f[i], h);
	used[k] = false;
}

void update(int k){
	ma[k] = max(ma[son[k][0]], ma[son[k][1]]);
	ma[k] = max(ma[k], z[k]);
}

void mkt(int &k, int q, int h, int hh){
	int mid = (q + h) / 2;
	k = to[zhan[mid]][hh] = ++lll;
	if (white[zhan[mid]])	z[lll] = l[zhan[mid]][hh]; else	z[lll] = -INF;
	if (q < mid)	mkt(son[k][0], q, mid - 1, hh), fa[son[k][0]] = k;
	if (mid < h)	mkt(son[k][1], mid + 1, h, hh), fa[son[k][1]] = k;
	update(k);
}

void dfs(int k, int h){
	ll++;
	dfs_sum(k, h);
	if (sum[k] == 1){
		high[k] = h;
		to[k][h] = ll;
		if (white[k])	ans[ll] = 0;
		else	ans[ll] = -INF;
		return ;
	}
	mi = INF;
	dfs_calc(k, sum[k]);
	int x = a, y = b;
	ff[ll] = c;
	used[y] = true;	r = 0; dfs_l(x, 0, h); mkt(root[ll][0], 1, r, h);used[y] = false;
	used[x] = true;	r = 0; dfs_l(y, 0, h); mkt(root[ll][1], 1, r, h);used[x] = false;
	ans[ll] = ma[root[ll][0]] + ma[root[ll][1]] + ff[ll];
	
	used[y] = true; dfs(x, h + 1); used[y] = false;
	used[x] = true; dfs(y, h + 1); used[x] = false;
}

void UPDATE(int k){
	MA[k] = max(MA[SON[k][0]], MA[SON[k][1]]);
	MA[k] = max(MA[k], ans[k]);
}

void MKT(int &k, int q, int h){
	k = (q + h) / 2;
	if (q < k)	MKT(SON[k][0], q, k - 1), FA[SON[k][0]] = k;
	if (k < h)	MKT(SON[k][1], k + 1, h), FA[SON[k][1]] = k;
	UPDATE(k);
}

void modify(int k){
	while (k)	update(k), k = fa[k];
}

void MODIFY(int k){
	while (k)	UPDATE(k), k = FA[k];
}
void change(int k){
	if (white[k])	ans[ffa[k][high[k]]] = 0;
	else	ans[ffa[k][high[k]]] = -INF;
	MODIFY(ffa[k][high[k]]);
	for (int i = high[k] - 1; i >= 0; i--){
		if (white[k])	z[to[k][i]] = l[k][i];
		else	z[to[k][i]] = -INF;
		modify(to[k][i]);
		ans[ffa[k][i]] = ma[root[ffa[k][i]][0]] + ma[root[ffa[k][i]][1]] + ff[ffa[k][i]];
		MODIFY(ffa[k][i]);
	}
}

int main(){
	read(n);
	ma[0] = MA[0] = -INF;
	for (i = 1; i <= n; i++)	white[i] = true;
	for (i = 1; i < n; i++){
		read(a); read(b); read(w);
		add(a, b, w);
		add(b, a, w);
	}
	dfs1(1, 0);
	len = 0;
	memset(till, 0, sizeof(till));
	make_new_tree(1);
	for (i = 1; i <= n; i++)
	for (j = till1[i]; j; j = next1[j])	add(i, go1[j], f1[j]), add(go1[j], i, f1[j]);
	
	dfs(1, 0);
	MKT(ROOT, 1, ll);
	
	read(m);
	while (m--){
		for (k = getchar(); k <= 32; k = getchar());
		if (k == 'A'){
			if (MA[ROOT] >= 0)		printf("%d\n", MA[ROOT]);
			else	printf("They have disappeared.\n");
		}else{
			read(s);
			white[s] = !white[s];
			change(s);
		}
	}
}
