// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1022
#include <cstdio>
int gcd(int x, int y){
	if(x<y){ 
		int tmp=y;
		y=x;
		x=tmp;
	}
	if((x%y)==0) return y;
	return gcd(y, x%y);
}
int mod (int k){
	if (k > 0) return k;
	return -1 * k;
}
int main(){
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		int n1,d1,n2,d2,cima,debaixo;
		char operador;
		scanf("%d %*c %d %c %d %*c %d",&n1,&d1,&operador,&n2,&d2);
		if (operador == '-') {
			cima = n1*d2 - n2*d1;
			debaixo = d1*d2;
		}
		if (operador=='+'){
			cima = n1*d2 + n2*d1;
			debaixo = d1*d2;
		}
		if (operador == '/') {
			cima = n1*d2;
			debaixo = n2*d1;
		}
		if (operador == '*'){
			cima = n1*n2;
			debaixo=d1*d2;
		}
		int comum = gcd(mod(cima),mod(debaixo));
		printf("%d/%d = %d/%d\n",cima,debaixo,cima/comum,debaixo/comum);
	}
	return 0;
}
