#include <cstdio>
#include <algorithm>
using namespace std;

int n, i, j, max1, max2, a[1100000], b[1100000], sg1[1100000], sg2[1100000], prod[2100][2100];
bool used[1100000];
long long ss[1100000];
int f[1000][1000];
   
int nim(int x,int y);

int _nim(int x, int y) {
	if (!x || !y)	return 1 << (x + y);
	if (f[x][y] != -1)	return f[x][y];
	int ret = 1, e = 1;
	for (int i = 0; i <= 4; i++)
		if ((x ^ y) & (1 << i))	e *= (1 << (1 << i));
		else	if (x & (1 << i))	ret = nim(ret, 3 * (1 << (1 << i)) / 2);
	f[x][y] = nim(ret, e);
	return f[x][y];
}

int nim(int x, int y) {
	int ret = 0;
	for (int i = 0; i <= 20; i++)
		if (x & (1 << i))
			for (int j = 0; j <= 20; j++)
				if (y & (1 << j))	ret ^= _nim(i, j);
	return ret;
}

int main() {
	scanf("%d", &n);
	for (sg1[0] = 0, i = 1; i <= n; i++) {
		for (j = 1; i - j * j >= 0; j++)	used[sg1[i - 1] ^ sg1[i - j * j]] = true;
		for (j = 0; used[j]; j++);
		sg1[i] = sg1[i - 1] ^ j;
		for (j = 1; i - j * j >= 0; j++)	used[sg1[i - 1] ^ sg1[i - j * j]] = false;
	}
	for (sg2[0] = 0, i = 1; i <= n; i++) {
		for (j = 1; i - (j + 1) * j / 2 >= 0; j++)	used[sg2[i - 1] ^ sg2[i - (j + 1) * j / 2]] = true;
		for (j = 0; used[j]; j++);
		sg2[i] = sg2[i - 1] ^ j;
		for (j = 1; i - (j + 1) * j / 2 >= 0; j++)	used[sg2[i - 1] ^ sg2[i - (j + 1) * j / 2]] = false;
	}
	for (i = 1; i <= n; i++)
		for (j = 1; i - j * j >= 0; j++)	a[sg1[i] ^ sg1[i - j * j]]++;
	for (i = 1; i <= n; i++)
		for (j = 1; i - (j + 1) * j / 2 >= 0; j++)	b[sg2[i] ^ sg2[i - (j + 1) * j / 2]]++;
	for (i = 0; i <= n; i++)	if (a[i])	max1 = i;
	max1 = max(max1, sg1[n]);
	for (i = 0; i <= n; i++)	if (b[i])	max2 = i;
	max2 = max(max2, sg2[n]);
	for (i = 0; i <= max1; i++)
		for (j = 0; j <= max2; j++)	f[i][j] = -1;
	for (i = 0; i <= max1; i++)
		for (j = 0; j <= max2; j++)
			prod[i][j] = nim(i, j);
	for (i = 0; i <= max1; i++)
		for (j = 0; j <= max2; j++)	ss[prod[i][j]] += 1LL * a[i] * b[j];
	printf("%lld\n", ss[prod[sg1[n]][sg2[n]]]);
}
