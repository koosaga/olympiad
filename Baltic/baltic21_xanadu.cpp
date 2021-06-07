#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int n;
vector<int> gph[MAXN];

struct node{
	int a[2][2]; // (v click, sum of clicked)
	node(){
		memset(a, 0x3f, sizeof(a));
	}
	node operator+(const node &x){
		node ret;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				for(int k = 0; k < 2; k++){
					ret.a[i][j^k] = min(ret.a[i][j^k], a[i][j] + x.a[i][k]);
				}
			}
		}
		return ret;
	}
}dp[MAXN];

int val[MAXN];

void solve(int x, int p = -1){
	node cur;
	cur.a[0][0] = 0;
	cur.a[1][1] = 1;
	for(auto &y : gph[x]){
		if(y == p) continue;
		solve(y, x);
		node rearr;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				rearr.a[val[y] ^ j][i] = dp[y].a[i][j];
			}
		}
		cur = cur + rearr;
	}
	dp[x] = cur;
}

int main(){
	scanf("%d",&n);
	for(int i = 1; i < n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i = 1; i <= n; i++) scanf("%d",&val[i]);
	solve(1);
	int ans = min(dp[1].a[0][val[1]], dp[1].a[1][val[1]]);
	if(ans > 1e7) puts("impossible");
	else cout << ans << endl;
}
 
