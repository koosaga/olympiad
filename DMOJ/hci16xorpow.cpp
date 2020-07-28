// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16xorpow
#include <cstdio>
int freq[4048],n,k,tot,resp;
int main(){
	scanf("%d %d",&n,&k);
	freq[0] = 1;
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		tot ^= davez;
		//printf("%d\n",tot);
		for(int temp = k;temp <= 1024;temp *= k){
			resp += freq[tot^temp];
			//printf("T : %d\n",tot^temp);
		}
		freq[tot]++;
	}
	printf("%d\n",resp);
	return 0;
}