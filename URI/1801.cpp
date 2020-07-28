// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1801
#include <cstdio>
#include <cstring>
#define MAXN 10
typedef long long ll;
ll x,y,auxiliar;
int frequencia[MAXN],referencia[MAXN],resposta,digitos,digitos_auxiliar;
const ll MAXIMO = 1e13 + 1;
int main(){
	scanf("%lld",&x);
	auxiliar = x;
	while(auxiliar > 0){
		referencia[auxiliar % 10]++;
		auxiliar /= 10;
		digitos++;
	}
	for(ll n = 1; n*n <= MAXIMO;n++){
		y = n*n - x;
		if(y <= 0LL) continue;
		digitos_auxiliar = 0;
		memset(frequencia,0,sizeof(frequencia));
		bool flag = false;
		auxiliar = y;
		while(auxiliar > 0){
			frequencia[auxiliar % 10]++;
			auxiliar /= 10;
			digitos_auxiliar++;
		}
		if(digitos_auxiliar > digitos) break;
		for(int i=0;i<MAXN;i++){
			if(frequencia[i] != referencia[i]){
				flag = true;
				break;
			}
		}
		if(flag) continue;
		resposta++;
	}
	printf("%d\n",resposta);
	return 0;
}
