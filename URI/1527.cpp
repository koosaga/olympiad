// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1527
#include <cstdio>
#define MAXN 100100
int pai[MAXN],peso[MAXN],pontuacao[MAXN],n,m;
inline int find(int x){
	while (x!=pai[x]) x = pai[x];
	return x;
}
void join(int x, int y){
	x = find(x);
	y = find(y);
	if (peso[x]<peso[y]){
		pai[x]=y;
		pontuacao[y]+=pontuacao[x];
	}
	if (peso[x]>peso[y]){
		pai[y]=x;
		pontuacao[x]+=pontuacao[y];
	}
	else{
		pai[x]=y;
		pontuacao[y]+=pontuacao[x];
		peso[y]++;
	}
}
int main(){
	while(1){
		scanf("%d %d",&n,&m);
		if (n==0 && m==0) break;
		int resposta = 0;
		for(int i=1;i<=n;i++){
			scanf("%d",&pontuacao[i]);
			pai[i]=i;
			peso[i]=0;
		}
		while(m--){
			int op,g1,g2;
			scanf("%d %d %d",&op,&g1,&g2);
			if (op==1) join(g1,g2);
			else{
				g1=find(g1);g2=find(g2);
				if (g1==find(1) && pontuacao[g1]>pontuacao[g2]) resposta++;
				if (g2==find(1) && pontuacao[g2]>pontuacao[g1]) resposta++;
			}
		}
		printf("%d\n",resposta);
	}
	return 0;
}
