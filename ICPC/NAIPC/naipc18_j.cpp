#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;

int n, m;
int dfn[MAXN], low[MAXN], vis[MAXN], dx[MAXN], piv, c;
vector<int> gph[MAXN];
vector<int> bcc[MAXN], cmp[MAXN];

void color(int x, int p){
	if(p){
		bcc[p].push_back(x);
		cmp[x].push_back(p);
	}
	for(auto &i : gph[x]){
		if(cmp[i].size()) continue;
		if(low[i] >= dfn[x]){
			bcc[++c].push_back(x);
			cmp[x].push_back(c);
			color(i, c);
		}
		else color(i, p);
	}
}

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			if(!dfn[i]){
				dfs(i, x);
				low[x] = min(low[x], low[i]);
			}
			else{
				low[x] = min(low[x], dfn[i]);
				if(dfn[i] < dfn[x]){
					dx[x]++;
					dx[i]--;
				}
			}
		}
	}
}

void sum(int x, int p){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(i != p){
			if(!vis[i]){
				sum(i, x);
				dx[x] += dx[i];
			}
		}
	}
	if(dx[x] > 1){
		puts("-1");
		exit(0);
	}
}

int dp[MAXN][3][3];
int compat[8][3][3];
int compat2[8][3];

void solve(int c);

vector<int> point_merge(int c, int v){
	vector<int> msk(8, 1e9);
	msk[0] = 0;
	for(auto &j : cmp[v]){
		if(c == j) continue;
		solve(j);
		vector<int> nxt(8, 1e9);
		for(int l=0; l<3; l++){
			for(int k=0; k<3; k++){
				for(int m=0; m<8; m++){
					if(bcc[j].size() > 2 && compat[m][l][k]){
						nxt[m | (1<<l) | (1<<k)] = min(nxt[m | (1<<l) | (1<<k)], msk[m] + dp[j][l][k]);
					}
					if(bcc[j].size() == 2 && compat2[m][l]){
						nxt[m | (1<<l)] = min(nxt[m | (1<<l)], msk[m] + dp[j][l][l]);
					}
				}
			}
		}
		msk = nxt;
	}
	return msk;
}

void solve(int c){
	if(bcc[c].size() == 2){
		vector<int> msk = point_merge(c, bcc[c][1]);
		for(int i=0; i<3; i++){
			for(int j=0; j<8; j++){
				if(compat2[j][i]){
					dp[c][i][i] = min(dp[c][i][i], msk[j] + i);
				}
			}
		}
		return;
	}
	int vdp[3][3][2] = {};
	memset(vdp, 0x3f, sizeof(vdp));
	vdp[0][0][0] = 0;
	vdp[1][1][1] = 1;
	vdp[2][2][0] = 2;
	for(int i=1; i<bcc[c].size(); i++){
		int v = bcc[c][i];
		vector<int> msk = point_merge(c, v);
		int nvdp[3][3][2];
		memset(nvdp, 0x3f, sizeof(nvdp));
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				for(int k=0; k<2; k++){
					for(int l=0; l<3; l++){
						for(int m=0; m<8; m++){
							if(compat[m][j][l]){
								nvdp[i][l][(k + l) % 2] = min(nvdp[i][l][(k + l) % 2], vdp[i][j][k] + msk[m] + l);
							}
						}
					}
				}
			}
		}
		memcpy(vdp, nvdp, sizeof(vdp));
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if((i + j) % 3 == 1) dp[c][i][j] = 1e9;
			else dp[c][i][j] = vdp[i][j][1];
		}
	}
}

int main(){
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<8; i++){
		for(int j=0; j<3; j++){
			vector<int> v = {j};
			for(int m=0; m<3; m++){
				if((i >> m) & 1) v.push_back(m);
			}
			bool fucked = false;
			for(int i=0; i<v.size(); i++){
				for(int j=0; j<i; j++){
					if((v[i] + v[j]) % 3 == 1){
						fucked = true;
					}
				}
			}
			compat2[i][j] = !fucked;
			for(int k=0; k<3; k++){
				vector<int> v = {j, k};
				for(int m=0; m<3; m++){
					if((i >> m) & 1) v.push_back(m);
				}
				bool fucked = false;
				for(int i=0; i<v.size(); i++){
					for(int j=0; j<i; j++){
						if((v[i] + v[j]) % 3 == 1){
							fucked = true;
						}
					}
				}
				compat[i][j][k] = !fucked;
			}
		}
	}
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(!dfn[i]){
			dfs(i, 0);
			sum(i, 0);
			color(i, 0);
			vector<int> msk = point_merge(-1, i);
			ret += *min_element(msk.begin(), msk.end());
			if(ret > m * 3){
				puts("-1");
				return 0;
			}
		}
	}
	cout << ret << endl;
}
