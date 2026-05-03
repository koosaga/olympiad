#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using pi = pair<real_t, real_t>;
const int MAXN = 100005;

int n, m;
real_t a[MAXN];
int nxt[MAXN];
real_t dp[MAXN];

int main(){
	while(true){
		scanf("%d",&n);
		if(n == 0) break;
		int offset = -1;
		nxt[0] = 1;
		for(int i=1; i<=n; i++){
			cin >> a[i];
			if(a[i] > 0.9999) nxt[i] = nxt[i-1];
			else nxt[i] = i + 1;
		}
		for(int i=1; i<=n; i++){
			dp[i] = 1e18;
			real_t dap = 1;
			real_t ret = 1;
			int itr = 0;
			for(int j=i; j>0 && itr < 69; j--){
				if(ret > 1e18) break;
				itr++;
				if(a[j] > 0.999){
					dap += (j - nxt[j]) * ret;
					j = nxt[j];
				}
				ret *= 1.0L / a[j];
				dap += ret;
				dp[i] = min(dp[i], dp[j-1] + dap);
			}
		}
		printf("%.10Lf\n", dp[n] + offset);
	}
}


