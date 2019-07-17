#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
 
int n, k;
int nxt[20][MAXN];
int ans[20][MAXN];
vector<int> gph[MAXN];
int deg[MAXN], up[MAXN];
 
void dfs(int x){
	for(auto &i : gph[x]){
		if(!deg[i]){
			up[i] = up[x] + 1;
			dfs(i);
		}
	}
}
 
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&nxt[0][i]);
		gph[nxt[0][i]].push_back(i);
		deg[nxt[0][i]]++;
	}
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++) nxt[i][j] = nxt[i-1][nxt[i-1][j]];
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[nxt[0][x]]--;
		if(deg[nxt[0][x]] == 0){
			que.push(nxt[0][x]);
		}
	}
	for(int i=1; i<=n; i++){
		if(deg[i]){
			int cnt = 1;
			for(int j=nxt[0][i]; j!=i; j=nxt[0][j]) cnt++;
			for(int j=i; !up[j]; j=nxt[0][j]){
				up[j] = cnt;
				dfs(j);
			}
			for(int j=i; deg[j]; j=nxt[0][j]) deg[j] = 0;
		}
	}
	for(int i=1; i<=n; i++){
		int pos = i;
		up[i] = min(up[i], k + 1);
		for(int j=0; j<20; j++){
			if((up[i] >> j) & 1){
				ans[j][pos]++;
				pos = nxt[j][pos];
			}
		}
	}
	for(int i=19; i; i--){
		for(int j=1; j<=n; j++){
			ans[i - 1][j] += ans[i][j];
			ans[i - 1][nxt[i-1][j]] += ans[i][j];
		}
	}
	for(int i=1; i<=n; i++) printf("%d\n", ans[0][i]);
}