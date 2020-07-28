// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc13s4
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 1000001
using namespace std;
vector<int> grafo[MAXN];
int processado[MAXN],alvo,n,m;
int dfs(int v){
	processado[v] = 1;
	if(v==alvo) return 1;
	int ret = 0;
	for(int u : grafo[v]){
		if(processado[u]) continue;
		ret |= dfs(u);
	}
	return ret;
}
int main(){
	scanf("%d %d",&n,&m);
	while(m--){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
	}
	int a,b;
	scanf("%d %d",&a,&b);
	alvo = b;
	if(dfs(a)){
		printf("yes\n");
		return 0;
	}
	memset(processado,0,sizeof(processado));
	alvo = a;
	if(dfs(b)){
		printf("no\n");
		return 0;
	}
	printf("unknown\n");
	return 0;
}