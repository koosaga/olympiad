#include <cstdio>
#include <cstring>
using namespace std;

int T, n, i, j, len, p, ans, son[510000][26], ss[510000], next[510000], n1[510000], du[510000];
char S[1100000];
bool touch[510000];

void insert(char *S, int l) {
	int p = 1;
	for (int i = 0; i < l; i++) {
		if (!son[p][S[i] - 'a'])	son[p][S[i] - 'a'] = ++len;
		p = son[p][S[i] - 'a'];
	}
	ss[p]++;
}

void buildAC() {
	int q, h, i;
	n1[q = h = 1] = 1;
	next[1] = 1;
	for (; q <= h; q++)
		for (i = 0; i < 26; i++)
		if (son[n1[q]][i]) {
			n1[++h] = son[n1[q]][i];
			if (q > 1)	next[n1[h]] = son[next[n1[q]]][i];
			else	next[n1[h]] = 1;
		}else	if (q > 1)	son[n1[q]][i] = son[next[n1[q]]][i];
		else	son[n1[q]][i] = 1;
}

void Bfs() {
	int q, h = 0, i;
	for (i = 1; i <= len; i++)	du[i] = 0;
	for (i = 2; i <= len; i++)	du[next[i]]++;
	for (i = 1; i <= len; i++)	if (!du[i])	n1[++h] = i;
	for (q = 1; q <= h; q++) {
		touch[next[n1[q]]] |= touch[n1[q]];
		if (!(--du[next[n1[q]]]))	n1[++h] = next[n1[q]];
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (i = 1; i <= len; i++)
		for (j = 0; j < 26; j++)	son[i][j] = 0, ss[i] = 0;
		len = 1;
		while (n--) {
			scanf("%s", S);
			insert(S, strlen(S));
		}
		buildAC();
		scanf("%s", S);
		int k = strlen(S);
		for (i = 1; i <= len; i++)	touch[i] = false;
		for (p = 1, ans = i = 0; i < k; i++)
			p = son[p][S[i] - 'a'], touch[p] = true;
		Bfs();
		for (i = 1; i <= len; i++)	ans += touch[i] * ss[i];
		printf("%d\n", ans);
	}
}
