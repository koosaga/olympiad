// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1429
#include <cstdio>
int main(){
	int n;
	while(scanf("%d",&n) && n){
		int resp = 0;
		for(int i=1;i<=5;i++){
			int temp = 1;
			for(int j=1;j<=i;j++) temp *= j;
			resp += (n % 10) * temp;
			n /= 10;
		}
		printf("%d\n",resp);
	}
	return 0;
}
