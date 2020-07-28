// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1303
#include <cstdio>
#include <algorithm>
#define MAXN 110
using namespace std;
int times[MAXN],pontuacoes[MAXN];
double recebido[MAXN],marcado[MAXN];
bool compara(int x, int y){
	if (pontuacoes[x] == pontuacoes[y]){
		if (recebido[x]==0) recebido[x] = 1.0;
		if (recebido[y]==0) recebido[y] = 1.0;
		if (marcado[x]/recebido[x] == marcado[y]/recebido[y]){
			if (marcado[x]==marcado[y]) return x < y;
			return marcado[x] > marcado[y];
		}
		return marcado[x]/recebido[x] > marcado[y]/recebido[y];
	}
	return pontuacoes[x]>pontuacoes[y];
}
int main(){
	int casos,count=1,davez1,davez2,primeiro=1;
	double pont1,pont2;
	while(1){
		scanf("%d",&casos);
		if (casos == 0 ) break;
		for(int i=1;i<=casos;i++){
			times[i]=i;
			pontuacoes[i] = 0;
			recebido[i] = 0.0;
			marcado[i] = 0.0;
		}
		for(int i=0;i<((casos)*(casos-1))/2;i++){
			scanf("%d %lf %d %lf",&davez1,&pont1,&davez2,&pont2);
			if (pont1>pont2){
				pontuacoes[davez1] += 2;
				pontuacoes[davez2] += 1;
			}
			else {
				pontuacoes[davez1] += 1;
				pontuacoes[davez2] += 2;
			}
			marcado[davez1] += pont1;
			recebido[davez1] += pont2;
			marcado[davez2] += pont2;
			recebido[davez2] += pont1;
		}
		sort(times+1,times+casos+1,compara);
		if (primeiro==0) printf("\n");
		primeiro = 0;
		printf("Instancia %d\n",count++);
		for(int i=1;i<=casos;i++){
			if (i!=1) printf(" ");
			printf("%d",times[i]);
			if (i==casos) printf("\n");
		}	
	}
	return 0;
}
