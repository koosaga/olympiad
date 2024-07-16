#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXQ = 200'005;
const int MAXN= 5'010;

typedef long double ld;

ld dp[MAXN][MAXN];
int main() {
	ios_base::sync_with_stdio(0);
	int R, C, P;
	cin>>R>>C>>P;
	int i, j;
	if(R>C) swap(R, C);
	for(j=2;j<=C;j++) {
		dp[1][j] = dp[1][j-1]/2+((ld)P/2+dp[1][j-1])/2;
	}
	for(i=2;i<=C;i++){
		for(j=i;j<=C;j++) {
			if(i == j) {
				dp[i][j]= dp[i-1][j];
				continue;
			}
			ld d1, d2;
			d1 = dp[i-1][j];
			d2 = dp[i][j-1];
			dp[i][j] = (d1+d2)/2;
			if(d1>d2) {
				ld mn = 0;
				ld t = d1-d2;
				t = min(t, (ld)P);
				mn = min(mn, t*t+2*(d2-d1)*t);
				dp[i][j]+=mn/(4*(ld)P);
			}
		}
	}
	cout.precision(20);
	cout<<fixed;
	cout<<dp[R][C];
	return 0;
}