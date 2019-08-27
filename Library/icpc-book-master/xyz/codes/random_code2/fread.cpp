#include <cstdio>
#include <algorithm>
using namespace std;
int n, i, l, r, len, k, m, tx[110000], a[110000], b[110000];
char S[10];
char *ch, *ch1, buf[35*1024000+5], buf1[35*1024000+5];

void read(int &x) {
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
}

void out(int x) {
	if (!x)	*(++ch1) = '0';
	else {
		char *ch0 = ch1, *ch = ch1 + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}

bool cmp(int x, int y) {
	return a[x] < a[y];
}

int main() {
	ch = buf - 1;
	ch1 = buf1 - 1;
	fread(buf, 1, 1000 * 35 * 1024, stdin);
	read(n);
	for (i = 1; i <= n; i++)	read(a[i]);
	for (i = 1; i <= n; i++)	tx[i] = i;
	sort(tx + 1, tx + n + 1, cmp);
	read(m); read(k);
	m += k;
	while (m--) {
		for (++ch; *ch <= 32; ++ch);
		if (*ch == 's') {
			ch += 3;
			read(l); read(r);
			for (len = 0, i = 1; i <= n; i++)
				if (l <= tx[i] && tx[i] <= r)	b[++len] = tx[i];
		}else {
			read(l);
			out(a[b[l]]);
		}
	}
	fwrite(buf1,1,ch1 - buf1 + 1,stdout);
}
