// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1301
#include <cstdio>
#include <cstring>
#define MAXN 100100
#define LSOne(S) (S&(-S))
int zero[MAXN],menos[MAXN],vetor[MAXN];
void updatezero(int pos,int val){
	while(pos<MAXN){
		zero[pos]+=val;
		pos += LSOne(pos);
	}
}
void updateminus(int pos,int val){
	while(pos<MAXN){
		menos[pos]+=val;
		pos += LSOne(pos);
	}
}
int somazero(int pos){
	int resultado = 0;
	while(pos>0){
		resultado += zero[pos];
		pos -= LSOne(pos);
	}
	return resultado;
}
int somamenos(int pos){
	int resultado = 0;
	while(pos>0){
		resultado += menos[pos];
		pos -= LSOne(pos);
	}
	return resultado;
}
int main(){
	int n,k;
	while(scanf("%d %d",&n,&k)!=EOF){
		memset(zero,0,sizeof(zero));
		memset(menos,0,sizeof(menos));
		for(int i=1;i<=n;i++){
			int davez;
			scanf("%d",&davez);
			if (davez>0){
				vetor[i] = 1;
			}
			else if (davez == 0){
				vetor[i] = 0;
				updatezero(i,1);
			}
			else {
				vetor[i] = -1;
				updateminus(i,1);
			}
		}
		while(k--){
			char op;
			int u,v;
			getchar();
			scanf("%c %d %d",&op,&u,&v);
			//printf("Caracter : %c\n",op);
			//for(int i=1;i<=n;i++) printf("%d ",vetor[i]);
			//printf("\n");
			if (op=='C'){
				if (v > 0) v = 1;
				else if (v < 0) v = -1;
				if (vetor[u]==v) continue;
				if (v == 1){
					if (vetor[u]==0) updatezero(u,-1);
					else updateminus(u,-1);
				}
				else if (v == 0){
					if (vetor[u]==-1) updateminus(u,-1);
					updatezero(u,1);
				}
				else {
					if (vetor[u]==0) updatezero(u,-1);
					updateminus(u,1);
				}
				vetor[u] = v;
			}
			else {
				int zertotal = somazero(v);
				int zeranterior = somazero(u-1);
				int nulos = zertotal - zeranterior;
				//printf("%d %d\n",zertotal,zeranterior);
				if (nulos==0){
					int negtotal = somamenos(v);
					int neganterior = somamenos(u-1);
					//printf("%d %d\n",negtotal,neganterior);
					int negativos = negtotal - neganterior;
					if (negativos % 2 == 0) printf("+");
					else printf("-");
				}
				else printf("0");
			}
		}
		printf("\n");
	}
	return 0;
}
