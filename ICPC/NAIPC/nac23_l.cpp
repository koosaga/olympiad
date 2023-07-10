#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int TC, N;
int A[110];

int main() {
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d", &N);
		bool tf = false;

		if (N & 1) {
			scanf("%d", &A[1]);
			for (int i = 2; i <= N; i++) {
				scanf("%d", &A[i]);
				if ((A[i] & -A[i]) != (A[i - 1] & -A[i - 1]))
					tf = true;
			}
			printf("%d\n", tf);
		} else {
			for (int i = 1; i <= N; i++) {
				scanf("%d", &A[i]);
				if (A[i] % 2 == 0)
					tf = true;
			}
			printf("%d\n", tf);
		}
	}
	return 0;
}