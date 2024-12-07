#include "sprout.h"
const int MAXN = 2005;
using lint = long long;
using namespace std;

int sum[31][MAXN][MAXN];
lint avg[MAXN][MAXN];

int diff(int K, std::vector<std::vector<int>> V) {
	int N = V.size();
	for (int i = 0; i <= 30; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				sum[i][j][k] = sum[i][j - 1][k] + sum[i][j][k - 1] - sum[i][j - 1][k - 1] + (V[j - 1][k - 1] <= i);
			}
		}
	}
	for (int j = 1; j <= N; j++) {
		for (int k = 1; k <= N; k++) {
			avg[j][k] = avg[j - 1][k] + avg[j][k - 1] - avg[j - 1][k - 1] + (V[j - 1][k - 1]);
		}
	}
	lint ans = 0;
	for (int i = K; i <= N; i++) {
		for (int j = K; j <= N; j++) {
			lint sums = avg[i][j] - avg[i - K][j] - avg[i][j - K] + avg[i - K][j - K];
			for (int x = 0; x <= 30; x++) {
				int d = sum[x][i][j] - sum[x][i - K][j] - sum[x][i][j - K] + sum[x][i - K][j - K];
				if (d * 2 >= K * K) {
					sums -= x * K * K;
					break;
				}
			}
			ans = max(ans, abs(sums));
		}
	}
	return ans;
}
