#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 2005;
const int MAXQ = 100005;
const int mod = 998244353;

struct qry{
	int x, y, t, idx;
	bool operator<(const qry &q)const{
		return t < q.t;
	}
}a[MAXQ];

int q;
vector<qry> Q[MAXN];
lint ret[MAXQ];

int solve(int x, int y){
	if(x < y) swap(x, y);
	int st = 1, ed = MAXN;
	while(st != ed){
		int m = (st+ed)/2;
		if((x + m - 1) / m <= y + 1) ed = m;
		else st = m + 1;
	}
	return st;
}

lint dp[MAXN][MAXN][2];
lint sum[MAXN][MAXN][2];
int main(){
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		if(a[i].x > a[i].y) swap(a[i].x, a[i].y);
		a[i].t = solve(a[i].x, a[i].y);
		a[i].idx = i;
		Q[a[i].t].push_back(a[i]);
	}
	for(int i=1; i<MAXN; i++){
		if(!sz(Q[i])) continue;
		int mx = 0, my = 0;
		for(auto &j : Q[i]){
			mx = max(mx, j.x);
			my = max(my, j.y);
		}
		int T = i;
		for(int i=0; i<=mx; i++){
			for(int j=0; j<=my; j++){
				if(i + j == 0){
					dp[0][0][0] = dp[0][0][1] = 1;
					sum[0][0][0] = sum[0][0][1] = 1;
				}
				else{
					if(i > 0){
						dp[i][j][0] = sum[i-1][j][1] - (i > T ? sum[i-T-1][j][1] : 0) + mod;
					}
					if(j > 0){
						dp[i][j][1] = sum[i][j-1][0] - (j > T ? sum[i][j-T-1][0] : 0) + mod;
					}
				}
				if(dp[i][j][0] >= mod) dp[i][j][0] -= mod;
				if(dp[i][j][1] >= mod) dp[i][j][1] -= mod;
				sum[i][j][0] = (j ? sum[i][j-1][0] : 0) + dp[i][j][0];
				sum[i][j][1] = (i ? sum[i-1][j][1] : 0) + dp[i][j][1];
				if(sum[i][j][0] >= mod) sum[i][j][0] -= mod;
				if(sum[i][j][1] >= mod) sum[i][j][1] -= mod;
			}
		}
		for(auto &j : Q[i]){
			ret[j.idx] = (dp[j.x][j.y][0] + dp[j.x][j.y][1]) % mod;
		}
		for(int i=0; i<=mx; i++){
			for(int j=0; j<=my; j++){
				for(int k=0; k<2; k++){
					dp[i][j][k] = sum[i][j][k] = 0;
				}
			}
		}
	}
	for(int i=0; i<q; i++) printf("%lld\n", ret[i]);
}
