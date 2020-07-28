// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ETF/
#include <cstdio>
const int MAXN = 1e6 + 10;
int totient[MAXN];
int main(){
	for(int i=1;i<MAXN;i++){
		totient[i] = i;
	}
	for(int i = 2;i<MAXN;i++){
		if(totient[i] == i)for(int j = i;j<MAXN;j += i){
			totient[j] -= totient[j]/i;
		}
	}
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int davez;
		scanf("%d",&davez);
		printf("%d\n",totient[davez]);
	}
	return 0;
}