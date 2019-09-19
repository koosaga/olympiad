#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define move fuck
using namespace std;
const int MAXN = 305;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;
int n, k, a[MAXN][MAXN], pos[MAXN][MAXN];
lint fact[MAXN * MAXN], invf[MAXN * MAXN];
vector<tuple<short, short, int>> move[MAXN];
lint dp[MAXN];

vector<pi> gph[MAXN];

int f(int x, int y){
	for(int i=0; i<MAXN; i++) gph[i].clear();
	memset(dp, 0, sizeof(dp));

	for(auto [f, s, c] : move[y]){
		int p = pos[x][f];
		int q = pos[x][s];
		gph[q].emplace_back(p, c);
	}
	dp[0] = 1;
	for(int i=1; i<=n+1; i++){
		dp[i] = 0;
		for(auto &j : gph[i]){
			if(j.first != 0) dp[i] += mod - dp[j.first] * j.second % mod;
			else dp[i] += dp[j.first] * j.second % mod;
		}
		dp[i] %= mod;
		if(i != n + 1) dp[i] *= fact[y - x + 1];
		dp[i] %= mod;
	}
	return dp[n + 1] % mod;
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN*MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	scanf("%d %d",&k,&n);
	for(int i=1; i<=k; i++){
		iota(a[i] + 1, a[i] + n + 1, 1);
		random_shuffle(a[i] + 1, a[i] + n + 1);
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
			pos[i][a[i][j]] = j;
		}
		pos[i][n + 1] = n + 1;
	}
	int cnt = 0;
	lint ret = 0;
	for(int s=1; s<=k; s++){
		for(int i=0; i<=n+1; i++){
			for(int j=0; j<=n+1; j++){
				if(pos[s][i] >= pos[s][j]) continue;
				int e = s;
				while(e <= k && pos[e][i] < pos[e][j]) e++;
				int sum = 0;
				lint tot = 1;
				for(int t=s; t<e; t++){
					int idx = pos[t][j] - pos[t][i] - 1;
					tot *= invf[idx];
					tot %= mod;
					sum += idx;
					if(s < t) move[t].emplace_back(i, j, fact[sum] * tot % mod), cnt++;
				}
			}
		}
		for(int e=s+1; e<=k; e++){
			ret += f(s, e);
		}
		for(int i=0; i<MAXN; i++) move[i].clear();
	}
	cout << ret % mod << endl;
}
