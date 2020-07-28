// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c3p5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e4 + 10;
const int MOD = 1e9;
ii dp[MAXN];
int n,m,componente[MAXN],tam[MAXN],compId,processado[MAXN],flag,chegano2[MAXN];
vector<int> grafo[MAXN],transposto[MAXN];
stack<int> pilha;
ii add(ii p1,ii p2){
	int v = p1.first + p2.first;
	int s = p1.second | p2.second;
	if(v > MOD){
		s = 1;
		v %= MOD;
	}
	return ii(v,s);
}
void dfs1(int x){
	processado[x] = 1;
	for(int v : grafo[x]) if(!processado[v]) dfs1(v);
	pilha.push(x);
}
void dfs2(int x){
	processado[x] = 1;
	componente[x] = compId;
	tam[compId]++;
	for(int v : transposto[x]) if(!processado[v]) dfs2(v);
}
void chega2(int x){
	processado[x] = 1;
	chegano2[x] = 1;
	for(int v : transposto[x])  if(!processado[v]) chega2(v);
}
void checa(int x){
	processado[x] = 1;
	if(tam[componente[x]] != 1 && chegano2[x])flag = 1;
	for(int v : grafo[x]) if(!processado[v]) checa(v);
}
ii solve(int v){
	if(tam[componente[v]] != 1) return ii(0,0);
	if(dp[v] != ii(-1,-1)) return dp[v];
	ii ans = ii(0,0);
	for(int u : grafo[v]){
		ans = add(ans,solve(u));
	}
	return dp[v] = ans;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		transposto[v].push_back(u);
	}
	for(int i=1;i<=n;i++) dp[i] = ii(-1,-1);
	dp[2] = ii(1,0);
	for(int i=1;i<=n;i++) if(!processado[i]) dfs1(i);
	for(int i=1;i<=n;i++) processado[i] = 0;
	while(!pilha.empty()){
		int i =pilha.top();
		pilha.pop();
		if(processado[i]) continue;
		compId++;
		dfs2(i);
	}
	for(int i=1;i<=n;i++) processado[i] = 0;
	chega2(2);
	for(int i=1;i<=n;i++) processado[i] = 0;
	checa(1);
	if(flag){
		printf("inf\n");
		return 0;
	}
	ii resp = solve(1);
	if(resp.second == 0){
		printf("%d\n",resp.first);
		return 0;
	}
	int digitos = 0;
	int temp = resp.first;
	while(temp != 0) digitos++,temp /= 10;
	digitos = 9 - digitos;
	while(digitos--) printf("0");
	printf("%d\n",resp.first);
	return 0;
}rst);
	return 0;
}