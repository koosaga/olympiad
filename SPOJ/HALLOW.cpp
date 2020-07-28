// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HALLOW/
#include <cstdio>
#define MAXN 100010
typedef long long ll;
ll vetor[MAXN],contem[MAXN],c,n,total;
int main(){
	while(scanf("%lld %lld",&c,&n) && (c||n)){
		total = 0;
		for(ll i=0;i<=c;i++){
			contem[i] = -1;
		}
		contem[0] = 0;
		for(ll i=1;i<=n;i++){
			scanf("%lld",&vetor[i]);
		}
		for(ll i=1;i<=n;i++){
			total += vetor[i];
			total %= c;
			if(contem[total] == -1){
				contem[total] = i;
			}
			else{
				printf("%lld",contem[total]+1);
				for(int j=contem[total]+2;j<=i;j++){
					printf(" %d",j);
				}
				printf("\n");
				break;
			}
		}
	}
	return 0;
}