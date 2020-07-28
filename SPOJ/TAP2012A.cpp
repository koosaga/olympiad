// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2012A/
#include <cstdio>
#include <queue>
int vetor[600];
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n) && n != -1){
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		for(int i=n;i>=1;i--){
			if (vetor[i] % i == 0){
				int val = vetor[i] / i;
				for(int j=1;j<i;j++) vetor[j] += val;
				vetor[i] = 0;
			}
		}
		bool flag = true;
		for(int i=1;i<=n;i++){
			if (vetor[i] != 0){
				flag = false;
			}
		}
		printf("%c\n",flag ? 'S' : 'N');
	}
	return 0;
}