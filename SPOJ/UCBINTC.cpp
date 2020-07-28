// Ivan Carvalho
// Solution to https://www.spoj.com/problems/UCBINTC/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5010;
const int ADD = 200000;
int vetor[MAXN],possivel[2*ADD + 10],n,resp;
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&vetor[i]);
		for(int j = 1;j<i;j++){
			if(possivel[vetor[i] - vetor[j] + ADD]){
				resp++;
				break;
			}
		}
		for(int j = 1;j<=i;j++){
			possivel[vetor[i] + vetor[j] + ADD] = 1;
		}
	}
	printf("%d\n",resp);
	return 0;
}