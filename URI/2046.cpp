// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2046
#include <cstdio>
#include <cstdlib>
#define MAXN 1000010
int coordx[MAXN],coordy[MAXN];
int main(){
	int instancia=1,n,m;
	while(scanf("%d %d",&n,&m) && (n || m)){
		if (instancia!=1) printf("\n");
		printf("Instancia %d\n",instancia++);
		int k,l;
		scanf("%d",&k);
		for(int i=0;i<k;i++) scanf("%d %d",&coordx[i],&coordy[i]);
		scanf("%d",&l);
		while(l--){
			int u,v;
			int idx = 0 , idy = 0, minimo = MAXN;
			scanf("%d %d",&u,&v);
			for(int i=0;i<k;i++){
				int distancia = abs(u-coordx[i]) + abs(v-coordy[i]);
				if (distancia == minimo){
					if (coordx[i]==idx){
						if (coordy[i]<idy){
							minimo = distancia;
							idx = coordx[i];
							idy = coordy[i];
						}
					}
					if (coordx[i]<idx) {
						minimo = distancia;
						idx = coordx[i];
						idy = coordy[i];
					}
				}
				if (distancia < minimo){
					minimo = distancia;
					idx = coordx[i];
					idy = coordy[i];
				}
			}
			printf("%d %d\n",idx,idy);
		}
	}
	return 0;
}
