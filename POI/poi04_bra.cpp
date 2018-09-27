#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

int n, deg[MAXN], bal[MAXN], vis[MAXN];
vector<int> gph[MAXN];

void dfs(int v, int w){
	if(w >= bal[v]) return;
	int dif = w - bal[v];
	bal[v] = w;
	for(auto &j : gph[v]){
		deg[j] += dif;
		if(deg[j] == 0){
			dfs(j, 0);
		}
		if(deg[j] < 0){
			dfs(j, -1);
		}
	}
}

vector<int> maximize(int bad){
	fill(bal, bal + n, 1);
	fill(deg, deg + n, 0);
	for(int i=0; i<n; i++){
		for(auto &j : gph[i]) deg[j]++;
	}
	dfs(bad, -1);
	return vector<int>(bal, bal + n);
}

int main(){
	scanf("%d",&n);
	for(int i=2; i<n; i++){
		scanf("%d",&deg[i]);
		for(int j=0; j<deg[i]; j++){
			int x; scanf("%d",&x);
			gph[x].push_back(i);
		}
	}
	auto v1 = maximize(0);
	auto v2 = maximize(1);
	for(auto &i : v2) i = -i;
	for(int i=0; i<n; i++){
		if(v1[i] != v2[i]) puts("?");
		else if(v1[i] < 0) puts("0");
		else if(v1[i] == 0) puts("1/2");
		else puts("1");
	}
}