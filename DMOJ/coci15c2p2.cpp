// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c2p2
#include <cstdio>
#define MAXN 20
int nao_pode[MAXN];
int main(){
	int n,m,resp = 0;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		u--;
		v--;
		nao_pode[u] |= (1 << v);
		nao_pode[v] |= (1 << u);
	}
	for(int bitmask = 0;bitmask < (1 << n);bitmask++){
		int pode = 1;
		for(int i=0;i<n;i++){
			if((bitmask & (1 << i)) && (bitmask & nao_pode[i])){
				pode = 0;
				break;
			}
		}
		resp += pode;
	}
	printf("%d\n",resp);
	return 0;
}