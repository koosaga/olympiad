#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 300005;

int n, p[MAXN];
set<pi> s;

int NX(int x, int y = 1){ return (x + y) % n; }
int PV(int x, int y = 1){ return (x + n - y) % n; }
int NP(int m, int x, int y = 1){ return m ? NX(x, y) : PV(x, y); }
bool extend(int s, int e, int x){ return PV(s) == x || NX(e) == x; }

void report(int pos, vector<int> b){
	int s = pos, e = pos;
	int ps = p[pos], pe = p[pos];
	printf("%d ", b[pos]);
	for(int i=1; i<n; i++){
		if(extend(ps, pe, p[PV(s)])){
			s = PV(s);
			printf("%d ", b[s]);
			if(PV(ps) == p[s]) ps = PV(ps);
			else pe = NX(pe);
		}	
		else if(extend(ps, pe, p[NX(e)])){
			e = NX(e);
			printf("%d ", b[e]);
			if(PV(ps) == p[e]) ps = PV(ps);
			else pe = NX(pe);
		}
		else assert(0);
	}
	exit(0);
}

int dp[MAXN][2][2];

map<pi, int> mp;
int dfs(int x, int y, int ps, int pe){
	if(y - x + 1 >= n) return 1;
	if(mp.count(pi(x, y))) return mp[pi(x, y)];
	pi mem = pi(x, y);
	if(PV(ps) == p[x-1]){
		int unt = dp[x-1][0][0];
		ps = PV(ps, x - unt);
		return mp[mem] = dfs(unt, y, ps, pe);
	}
	if(NX(pe) == p[x-1]){
		int unt = dp[x-1][0][1];
		pe = NX(pe, x - unt);
		return mp[mem] = dfs(unt, y, ps, pe);
	}
	if(PV(ps) == p[y+1]){
		int unt = dp[y+1][1][0];
		ps = PV(ps, unt - y);
		return mp[mem] = dfs(x, unt, ps, pe);
	}
	if(NX(pe) == p[y+1]){
		int unt = dp[y+1][1][1];
		pe = NX(pe, unt - y);
		return mp[mem] = dfs(x, unt, ps, pe);
	}
	return mp[mem] = 0;
}

int main(){
	scanf("%d",&n);
	vector<int> ra(n), a(n), b(n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		ra[a[i]-1] = i;
	}
	for(int i=0; i<n; i++){
		scanf("%d",&b[i]);
		p[i+n+n] = p[i+n] = p[i] = ra[b[i]-1];
	}
	for(int i=0; i<n*3; i++){
		for(int j=0; j<2; j++){
			dp[i][0][j] = i;
			if(i && p[i-1] == NP(j, i)) dp[i][0][j] = dp[i-1][0][j];
		}
	}
	for(int i=3*n-1; i>=0; i--){
		for(int j=0; j<2; j++){
			dp[i][1][j] = i;
			if(i+1<3*n && p[i+1] == NP(j, i)) dp[i][1][j] = dp[i+1][1][j];
		}
	}
	if(dp[3*n-1][0][0] == 0 || dp[3*n-1][0][1] == 0) report(0, b);
	for(int i=0; i<n; i++){
		if(dfs(i+n, i+n, p[i], p[i])) report(i, b);
	}
	puts("-1");
}
