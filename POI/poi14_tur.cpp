#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 20005;

struct state{
	int len, nei, on;
};

vector<state> idx[11];
int loc[11][1<<10][1<<10];

int n, m, a[MAXN];
vector<int> gph[MAXN];
int dp[1<<13], nxt[1<<13];
int dep[MAXN], vis[MAXN];

void dfs(int x){
	vis[x] = 1;
	int amsk = 1 << dep[x];
	for(auto &i : gph[x]){
		if(vis[i]) amsk |= (1 << dep[i]);
	}
	memset(nxt, 0x3f, sizeof(nxt));
	auto upd = [&](state &x, int v, int *w){
		int ptr = loc[x.len][x.nei][x.on] - 1;
		assert(ptr >= 0);
		w[ptr] = min(w[ptr], v);
	};
	for(int j=0; j<sz(idx[dep[x]]); j++){
		state s1 = idx[dep[x]][j]; s1.len++;
		if(s1.on & amsk) s1.nei |= (1<<dep[x]);
		state s2 = (state){s1.len, s1.nei | amsk, s1.on | (1<<dep[x])};
		upd(s1, dp[j], nxt);
		upd(s2, dp[j] + a[x], nxt);
	}
	memcpy(dp, nxt, sizeof(dp));
	for(auto &i : gph[x]){
		if(vis[i]) continue;
		dep[i] = dep[x] + 1;
		dfs(i);
	}
	memset(nxt, 0x3f, sizeof(nxt));
	for(int j=0; j<sz(idx[dep[x] + 1]); j++){
		state s = idx[dep[x] + 1][j];
		if((s.nei >> dep[x]) & 1){
			s.nei &= ~(1<<dep[x]);
			s.on &= ~(1<<dep[x]);
			s.len--;
			upd(s, dp[j], nxt);
		}
	}
	memcpy(dp, nxt, sizeof(dp));
}

int main(){
	for(int i=0; i<=10; i++){
		for(int j=0; j<(1<<i); j++){
			for(int k=j; ; k=(k-1)&j){
				bool good = 1;
				for(int x = 1; x < i; x++){
					int prvSt = (j >> (x - 1)) % 2 + (k >> (x - 1)) % 2;
					int nxtSt = (j >> x) % 2 + (k >> x) % 2;
					if(prvSt == 0 && nxtSt == 2){
						good = 0;
						break;
					}
					if(prvSt == 2 && nxtSt == 0){
						good = 0;
						break;
					}
				}
				if(good){
					idx[i].push_back({i, j, k});
					loc[i][j][k] = sz(idx[i]);
				}
				if(k == 0) break;
			}
		}
	}
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(vis[i]) continue;
		memset(dp, 0x3f, sizeof(dp));
		dp[0] = 0;
		dfs(i);
		ret += dp[0];
	}
	cout << ret << endl;
}
