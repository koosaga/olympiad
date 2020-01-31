#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

int n, a[MAXN], dp[MAXN][2];
int lis[MAXN], piv;

pi gph[MAXN]; int X;
int chkv, chks;
 
int solve(int x){
	chkv = -a[x];
	piv = 0;
	lis[piv++] = x;
	for(int i=0; i<piv; i++){
		int x = lis[i];	
		auto l = lower_bound(gph, gph + X, pi(x, -1)) - gph;
		while(l < X && gph[l].first == x) lis[piv++] = gph[l++].second;
	}
	reverse(lis, lis + piv);
	int ret = -1e8;
	for(int chks = 0; chks < 2; chks++){
		for(int xx = 0; xx < piv; xx++){
			int x = lis[xx];
			for(int d = 0; d < 2; d++){
				dp[x][d] = d;
				int up = -1e8;
				auto l = lower_bound(gph, gph + X, pi(x, -1)) - gph;
				while(l < X && gph[l].first == x){
					int i = gph[l++].second;
					if(d == 0){
						dp[x][d] += max(dp[i][0], dp[i][1]);
					}
					else{
						dp[x][d] += max(dp[i][0], dp[i][1]);
						up = max(up, dp[i][0] - max(dp[i][0], dp[i][1]));
					}
				}
				if(x == chkv && chks == 0){
					up = max(up, 0);
				}
				if(d == 1) dp[x][d] += up;
				if(dp[x][d] < -1e8) dp[x][d] = -1e8;
			}
		}
		ret = max(ret, dp[x][chks]);
	}
	for(int i=0; i<piv; i++) dp[lis[i]][0] = dp[lis[i]][1] = 0;
	return ret;
}
 
 static char buf[1 << 11]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}


int main(){
	n = _readInt();
	for(int i=1; i<=n; i++){
		a[i] = _readInt();
		dp[a[i]][0]++;
	}
	for(int i=1; i<=n; i++){
		if(!dp[i][0]){
			lis[piv++] = i;
		}
	}
	for(int i=0; i<piv; i++){
		int x = lis[i];
		dp[a[x]][0]--;
		if(dp[a[x]][0] == 0){
			lis[piv++] = a[x];
		}
	}
	for(int i=1; i<=n; i++){
		if(dp[i][0]){
			for(int j=i; dp[j][0]; j = a[j]) dp[j][0] = 0;
			a[i] *= -1;
		}
	}
	piv = 0;
	for(int i=1; i<=n; i++){
		if(a[i] > 0){
			dp[a[i]][0]++;
			gph[X++] = pi(a[i], i);
		}
	}
	sort(gph, gph + X);
	for(int i=1; i<=n; i++){
		if(!dp[i][0]){
			lis[piv++] = i;
		}
	}
	for(int i=0; i<piv; i++){
		int x = lis[i];
		if(a[x] < 0) continue;
		dp[a[x]][0]--;
		if(dp[a[x]][0] == 0){
			lis[piv++] = a[x];
		}
	}
	int ret = 0;
	piv = 0;
	for(int i=1; i<=n; i++){
		if(a[i] < 0) ret += solve(i);
	}
	cout << ret << endl;
}
