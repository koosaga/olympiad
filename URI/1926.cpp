// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1926
#include <cstdio>
const int MAXN = 1e6 + 11;
bool crivo[MAXN+10];
int soma[MAXN+10];
int Q;
int main(){
	crivo[0] = true;
	crivo[1] = true;
	for(int i=2;i<MAXN;i++){
		if(!crivo[i]){
			long long checar = (long long) i;
			checar *= checar;
			if(checar >= MAXN) continue;
			for(int j=i*i;j < MAXN;j += i){
				crivo[j] = true;
			}
		}
	}
	for(int i=2;i<MAXN;i++){
		if(!crivo[i]) soma[i] = soma[i-1] + int(!crivo[i-2] || !crivo[i+2]);
		else soma[i] = soma[i-1];
	}
	scanf("%d",&Q);
	while(Q--){
		int a,b;
		scanf("%d %d",&a,&b);
		if(a > b){
			int temp = b;
			b = a;
			a = temp;
		}
		printf("%d\n",soma[b] - soma[a-1]);
	}
	return 0;
}
