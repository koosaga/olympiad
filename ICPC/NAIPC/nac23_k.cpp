#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using ll = long long;
using pll = pair<ll, ll>;

int N, ans = -1;
int A[1010], B[1010], D[1010];
char S[1010];

int main() {
	int d = 0, t = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%s", S);
		int a = 0, b = 0, t = 0;
		for (t = 0; S[t]; t++) {
			if (S[t] == 's')
				b++;
			if (S[t] == 't')
				a++;
		}
		if (S[t - 1] == '}')
			d--;
		if (d == 0 && (a || b)) {
			puts("-1");
			return 0;
		}
		A[i] = a, B[i] = b, D[i] = d;
		if (S[t - 1] == '{')
			d++;
	}
	int x = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (A[i] * D[j] - A[j] * D[i] == 0) {
				if (B[j] * D[i] - B[i] * D[j]) {
					puts("-1");
					return 0;
				}
				continue;
			}
			x = A[i] * D[j] - A[j] * D[i];
			if ((B[j] * D[i] - B[i] * D[j]) % x) {
				puts("-1");
				return 0;
			}
			t = (B[j] * D[i] - B[i] * D[j]) / x;
			if ((A[i] * t + B[i]) % D[i]) {
				puts("-1");
				return 0;
			}
			x = (A[i] * t + B[i]) / D[i];
			if (t <= 0 || x <= 0) {
				puts("-1");
				return 0;
			}
			break;
		}
		if (x)
			break;
	}
	if (!x) {
		for (int i = 1; i <= N; i++) {
			if (!D[i])
				continue;
			if (A[i]) {
				for (int j = 1; j<=1000000; j++) {
					if ((A[i] * j + B[i]) % D[i] == 0) {
						t = j;
						x = (A[i] * j + B[i]) / D[i];
					}
				}
				if (!x){
					puts("-1");
					return 0;
				}
			}
			break;
		}
		for (int i = 1; i <= N; i++) {
			if (!D[i])
				continue;
			{
				if (B[i] % D[i]) {
					puts("-1");
					return 0;
				}
				x = B[i] / D[i];
				t = 1;
			}
			break;
		}
	}
	if (!x) {
		puts("1");
		return 0;
	}
	for (int i = 1; i <= N; i++) {
		if (A[i] * t + B[i] == D[i] * x)
			continue;
		puts("-1");
		return 0;
	}
	printf("%d\n", t);
	return 0;
}