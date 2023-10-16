#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;

int main(){
	int n;
	scanf("%d",&n);
	vector<vector<lint>> a(n, vector<lint>(n, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%lld",&a[i][j]);
		}
	}
	vector<lint> R(n), C(n);
	for(int i = 1; i < n-1; i++){
		C[i] = (a[0][i+1] - 2 * a[0][i] + a[0][i-1]) / 2;
		R[i] = (a[i+1][0] - 2 * a[i][0] + a[i-1][0]) / 2;
	}
	lint sum[2][2] = {};
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			int x = i * (n - 1);
			int y = j * (n - 1);
			lint val = a[x][y];
			for(int k = 1; k < n-1; k++){
				val -= abs(x - k) * R[k];
				val -= abs(y - k) * C[k];
			}
			val /= n - 1;
			sum[i^1][j^1] = val;
		}
	}
	// total = R[0] + R[1] - C[0] - C[1];
	lint total = accumulate(all(C), 0ll) - accumulate(all(R), 0ll);
	total += sum[0][0] + sum[1][1];
	total /= 2; // total = R[0] + R[1]
	R[0] = (total + sum[0][0] - sum[1][0]) / 2;
	R[n - 1] = total - R[0];
	C[0] = sum[0][0] - R[0];
	C[n - 1] = sum[1][1] - R[n - 1];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			lint tmp = min(R[i], C[j]);
			printf("%lld ", tmp);
			R[i] -= tmp;
			C[j] -= tmp;
		}
		puts("");
	}
}
