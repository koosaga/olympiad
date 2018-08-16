#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n, m, k, a[MAXN];
vector<int> gph[MAXN];
lint dp[32][MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i]--;
		dp[1 << a[i]][i] = 1;
	}
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	lint ret = 0;
	for(int i=2; i<(1<<k); i++){
		if(i == (i & -i)) continue;
		for(int j=1; j<=n; j++){
			if((i >> a[j]) & 1){
				for(auto &k : gph[j]){
					dp[i][j] += dp[i ^ (1 << a[j])][k];
				}
			}
			ret += dp[i][j];
		}
	}
	cout << ret << endl;
}
