// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1548
#include <cstdio>
#include <algorithm>
int vetorzao[1010],auxiliar[1010];
using namespace std;
bool compara (int x, int y){
	if (x>y) return true;
	return false;
}
int main(){
	int casos,davez,i,j;
	scanf("%d",&casos);
	for(i=0;i<casos;i++){
		int resp=0;
		scanf("%d",&davez);
		for(j=1;j<=davez;j++){
			scanf("%d",&auxiliar[j]);
			vetorzao[j]=auxiliar[j];
		}
		sort(vetorzao+1,vetorzao+davez+1,compara);
		for(j=1;j<=davez;j++){
			if (vetorzao[j]==auxiliar[j]) resp++;
		}
		printf("%d\n",resp);
	}
	return 0;
}
