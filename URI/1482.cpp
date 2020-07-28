// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1482
#include <cstdio>
#include <algorithm>
using namespace std;
int matriz[20][20],custo[20],ordenado[20],n,lista[20][20],davezsort;
int menor[20][(1<<20)+1],resp,cota;
void solve(int museu,int bitmask,int tempo,int acesos){
	if(menor[museu][bitmask] <= tempo) return;
	menor[museu][bitmask] = tempo;
	resp = max(resp,acesos);
	if(bitmask == (1 << n) - 1) return;
	for(int i = 1;i < n;i++){
		int proximo = lista[museu][i];
		if(!(bitmask & (1 << proximo))){
			solve(proximo,bitmask | (1 << proximo),tempo + matriz[museu][proximo],acesos+1);
			if(resp == cota) return;
		}
	}
}
bool comp(int a,int b){
	return matriz[davezsort][a] < matriz[davezsort][b];
}
bool comp2(int a,int b){
	return custo[a] < custo[b];
}
int main(){
	while(scanf("%d",&n) && n){
		resp = 0;
		cota = 0;
		for(int i=0;i<n;i++){
			scanf("%d",&custo[i]);
			ordenado[i] = i;
			for(int j=0;j<n;j++){
				lista[i][j] = j;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		for(int k=0;k<n;k++){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					matriz[i][j] = min(matriz[i][j],matriz[i][k] + matriz[k][j]);
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				matriz[i][j] += custo[j];
			}
			davezsort = i;
			sort(lista[i],lista[i]+n,comp);
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<(1<<n);j++){
				menor[i][j] = 421;
			}
		}
		sort(ordenado,ordenado+n,comp2);
		for(int i=0, temporestante= 420 ;i < n && temporestante > 0;i++){
			cota++;
			temporestante -= custo[ordenado[i]];
		}
		for(int j=0;j<n;j++){
			int i = ordenado[j];
			solve(i,(1<<i),custo[i],1);
		}
		printf("%d\n",resp);
	}
	return 0;
}
