#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int m, n, k, a[20005];
char buf[20005];
int low[20005][55];
lint dp[55][20005];

lint getmin(lint *dp, int coeff, int s, int e){
	lint ret = 1e18;
	for(int i=s; i<=e; i++){
		ret = min(ret, dp[i] - coeff * a[i]);
	}
	return ret;
}

struct rmin{
	lint dq[20005];
	int idx[20005];
	int s, e, x;
	int rs, re;
	void init(int coeff){
		s = e = rs = re = 0;
		re = -1;
		x = coeff;
	}
	lint query(lint *dp, int qs, int qe){
		while(re < qe){
			re++;
			while(s < e && dq[e-1] >= dp[re] - 1ll * x * a[re]){
				e--;
			}
			dq[e] = dp[re] - 1ll * x * a[re];
			idx[e] = re;
			e++;
		}
		rs = qs;
		while(s < e && idx[s] < qs){
			s++;
		}
		if(s == e) return 1e18;
		return dq[s];
	}
}rmin[55];

int main(){
	freopen("popeala.in", "r", stdin);
	freopen("popeala.out", "w", stdout);
	cin >> m >> n >> k;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] += a[i-1];
	}
	for(int i=0; i<m; i++){
		scanf("%s", buf + 1);
		int pos = 0;
		for(int j=1; j<=n; j++){
			if(buf[j] == '0') pos = j;
			low[j][i] = pos;
		}
	}
	for(int i=1; i<=n; i++){
		sort(low[i], low[i] + m);
		low[i][m] = i;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=k; i++){
		for(int j=0; j<=m; j++){
			rmin[j].init(j);
		}
		// 0 ~ m deque structure init
		for(int j=1; j<=n; j++){
			dp[i][j] = rmin[0].query(dp[i-1], 0, low[j][0] - 1);
			for(int k=0; k<m; k++){
				dp[i][j] = min(dp[i][j], rmin[k+1].query(dp[i-1], low[j][k], low[j][k+1] - 1) + 1ll * (k+1) * a[j]);
			}
		}
		printf("%lld\n", dp[i][n]);
	}
}

