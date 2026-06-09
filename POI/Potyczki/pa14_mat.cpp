#include <bits/stdc++.h>
using namespace std;
char str[1010101];
int N;
int cnt[26];
int nonzero = 0;
void update(char x, int a) {
	if (x == '*')
		return;
	if (cnt[x - 'A'] != 0)
		nonzero--;
	cnt[x - 'A'] += a;
	if (cnt[x - 'A'] != 0)
		nonzero++;
}

int main() {
	scanf("%s", str);
	N = strlen(str);
	int j = 0, ans = N + 1;
	for (int i = 0; i < N; i++) {
		while (j < N && nonzero <= 1) {
			update(str[j++], 1);
		}
		if (nonzero > 1)
			ans = min(ans, j - i);
		update(str[i], -1);
	}
	printf("%d\n", N + 2 - ans);
}
