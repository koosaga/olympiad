#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

static char buf[1 << 19]; // size : any number geq than 1024 
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

int s[100005], e[100005], x[100005];
int typ[200005], val[200005];
int n, m, q;

int dp[1005][1005];
vector<pi> gph[1005];
int main(){
	memset(x, 0x3f, sizeof(x));
	n = _readInt();
	m = _readInt();
	q = _readInt();
	for(int i=1; i<=m; i++){
		s[i] = _readInt();
		e[i] = _readInt();
	}
	for(int i=0; i<q; i++){
		int c = _read();
		while (c <= 32) c = _read();
		if(c == 'U'){
			typ[i] = 1;
			val[i] = _readInt();
			x[val[i]] = i;
		}
		else{
			typ[i] = 2;
			val[i] = _readInt();
		}
	}
	for(int i=1; i<=m; i++){
		gph[s[i]].push_back(pi(x[i], e[i]));
	}
	fill(dp[0] + 1, dp[0] + n + 1, -1e9);
	dp[0][1] = 1e9;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			dp[i][j] = dp[i-1][j];
		}
		for(int j=1; j<=n; j++){
			for(auto &k : gph[j]){
				dp[i][k.second] = max(min(dp[i-1][j], k.first), dp[i][k.second]);
			}
		}
	}
	for(int i=0; i<q; i++){
		if(typ[i] == 2){
			int s = 0, e = n;
			while(s != e){
				int m = (s+e)/2;
				if(dp[m][val[i]] >= i) e = m;
				else s = m+1;
			}
			if(s == n) puts("-1");
			else printf("%d\n", s);
		}
	}
}