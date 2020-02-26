#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 51;
const int MAXM = 4005;

struct kek{
	int s, e, x;
}a[MAXM];

int n, m;
int psum[MAXM][MAXN][MAXN];
int dp[MAXM][MAXN][MAXN];
int opt[MAXM][MAXN][MAXN];
int ans[MAXN];

vector<int> crd;

int f(int x, int s, int e){
	if(s > e) return 0;
	if(x == m) return -2e9;
	if(~dp[x][s][e]) return dp[x][s][e];
	int ret = f(x + 1, s, e);
	opt[x][s][e] = -1;
	for(int i=s; i<=e; i++){
		int foo = f(x, s, i-1) + f(x, i+1, e)
		+ (psum[x][i][e] - psum[x][i][i-1] - psum[x][s-1][e] + psum[x][s-1][i-1]) * crd[x];
		if(ret < foo){
			ret = foo;
			opt[x][s][e] = i;
		}
	}
	return dp[x][s][e] = ret;
}

void track(int x, int s, int e){
	if(s > e) return;
	assert(x != m);
	if(~opt[x][s][e]){
		ans[opt[x][s][e]] = x;
		track(x, s, opt[x][s][e] - 1);
		track(x, opt[x][s][e] + 1, e);
	}
	else track(x + 1, s, e);
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		cin >> a[i].s >> a[i].e >> a[i].x;
		crd.push_back(a[i].x);
	}
	sort(all(crd));
	crd.resize(unique(all(crd)) - crd.begin());
	crd.push_back(500001);
	for(int i=0; i<m; i++){
		a[i].x = lower_bound(all(crd), a[i].x) - crd.begin();
		for(int j=0; j<=a[i].x; j++){
			psum[j][a[i].s][a[i].e] += 1;
		}
	}
	for(int i=0; i<=m; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				psum[i][j][k] += psum[i][j-1][k] + psum[i][j][k-1] - psum[i][j-1][k-1];
			}
		}
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0, 1, n) << endl;
	track(0, 1, n);
	for(int i=1; i<=n; i++) printf("%d ", min(500000, crd[ans[i]]));
}
