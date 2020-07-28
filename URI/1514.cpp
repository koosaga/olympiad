// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1514
#include <cstdio>
#define MAXN 110
int problemasresolvidos[MAXN];
int main(){
	int n,m;
	while(scanf("%d %d",&n,&m) && (n||m)){
		for(int i=0;i<m;i++) problemasresolvidos[i]=0;
		int condicao1 = 1, condicao2 = 1, condicao3 = 1, condicao4 = 1;
		for(int i=0;i<n;i++){
			int resolvidos = 0;
			for(int j=0;j<m;j++){
				int x;
				scanf("%d",&x);
				if (x){
					resolvidos++;
					problemasresolvidos[j]++;
				}
			}
			if (resolvidos == 0) condicao4 = 0;
			if (resolvidos == m) condicao1 = 0;
		}
		for(int i=0;i<m;i++){
			if (problemasresolvidos[i]==n) condicao3 = 0;
			if (problemasresolvidos[i]==0) condicao2 = 0;
		}
		printf("%d\n",condicao1+condicao2+condicao3+condicao4);
	}
	return 0;
}
