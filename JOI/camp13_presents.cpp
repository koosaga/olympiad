#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;

int n, a[100005], b[100005], c[100005], d[100005];
vector<int> gph[100005];
int vis[100005], indeg[100005];

lint dp[100005][2];

lint f(int x, int p, int col){
	if(~dp[x][col]) return dp[x][col];
	lint ret = 0;
	for(auto &i : gph[x]){
		if(i == p || indeg[i]) continue;
		ret += max(f(i, x, col) + 1ll * c[x] * b[i], f(i, x, 1 - col) + 1ll * d[x] * b[i]);
	}
	return dp[x][col] = ret;
}

lint tmp[100005][2];

lint solve(int x){
	vector<int> cyc;
	cyc.push_back(x);
	vis[x] = 1;
	for(int i=a[x]; i!=x; i=a[i]){
		cyc.push_back(i);
		vis[i] = 1;
	}
	lint ret = 0;
	for(int i=0; i<2; i++){
		tmp[0][1-i] = 1ll * d[cyc[0]] * b[cyc.back()] + f(cyc[0], -1, 1-i);
		tmp[0][i] = 1ll * c[cyc[0]] * b[cyc.back()] + f(cyc[0], -1, i);
		for(int j=1; j<cyc.size(); j++){
			for(int k=0; k<2; k++){
				tmp[j][k] = tmp[j-1][k] + 1ll * c[cyc[j]] * b[cyc[j-1]];
				tmp[j][k] = max(tmp[j][k], tmp[j-1][1-k] + 1ll * d[cyc[j]] * b[cyc[j-1]]);
				tmp[j][k] += f(cyc[j], -1, k);
			}
		}
		ret = max(ret, tmp[cyc.size()-1][i]);
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
		indeg[a[i]]++;
		gph[a[i]].push_back(i);
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(indeg[i] == 0){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		indeg[a[x]]--;
		if(indeg[a[x]] == 0){
			que.push(a[x]);
		}
	}
	memset(dp, -1, sizeof(dp));
	lint ret = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i] && indeg[i]) ret += solve(i);
	}
	cout << ret;
}