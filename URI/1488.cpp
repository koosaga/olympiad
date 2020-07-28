// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1488
#include <cstdio>
int main(){
	int n,instancia=0;
	while(scanf("%d",&n) && n){
		int possivel = 0,p1,p2,p3,p4,resp;
		for(int m=1;m*m<=n;m++){
			if(n % ((m+1)*(m+1)) == 0){
				int tp3 = n / ((m+1)*(m+1));
				int tp4 = tp3 * m * m;
				int tp2 = (tp3+1)*m;
				int tp1 = (tp3 - 1)*m;
				if(tp1 > 0 && tp2 > 0 && tp3 > 0 && tp4 > 0 && (tp1+tp2+tp3+tp4) == n){
					p1 = tp1;
					p2 = tp2;
					p3 = tp3;
					p4 = tp4;
					resp = m;
					possivel = 1;
				}
			}
		}
		printf("Instancia %d\n",++instancia);
		if(possivel) printf("%d %d %d %d %d\n",resp,p1,p2,p3,p4);
		else printf("%d nao e quadripartido\n",n);
		printf("\n");
	}
	return 0;
}
