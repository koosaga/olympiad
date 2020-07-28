// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1483
#include <cstdio>
int grupo[101];
int main(){
	grupo[0] = -1;
	for(int i=1;i<=100;i++){
		grupo[i] = (i-1)/4;
	}
	double v;
	int n,m;
	while(scanf("%lf %d %d",&v,&n,&m) && (n||m||v)){
		if(n % 10000 == m % 10000){
			printf("%.2lf\n",v*3000);
		}
		else if(n % 1000 == m % 1000){
			printf("%.2lf\n",v*500);
		}
		else if(n % 100 == m % 100){
			printf("%.2lf\n",v*50);
		}
		else{
			if(grupo[n % 100] == grupo[m % 100]){
				printf("%.2lf\n",v*16);
			}
			else{
				printf("0.00\n");
			}
		}
	}
	return 0;
}
