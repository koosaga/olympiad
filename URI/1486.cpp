// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1486
#include <cstdio>
int vetor[1001][1001],m,n,p;
int main(){
	while(scanf("%d %d %d",&n,&m,&p) && (n||m||p)){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&vetor[i][j]);
			}
		}
		int resp = 0;
		for(int i=1;i<=n;i++){
			int jaforam = 0;
			for(int j=1;j<=m;j++){
				if(vetor[j][i] == 1){
					jaforam++;
				}
				else{
					resp += (jaforam>=p);
					jaforam = 0;
				}
			}
			resp += (jaforam>=p);
		}
		printf("%d\n",resp);
	}
	return 0;
}
