// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1531
#include <bits/stdc++.h>
using namespace std;
map<int,int> pisano;
int calcula_periodo(int modulo){
	if(pisano.count(modulo)) return pisano[modulo];
	int f0 = 0,f1 = 1;
	for(int passo = 1;passo<=7*modulo;passo++){
		int nf = (f1 + f0) % modulo;
		f0 = f1;
		f1 = nf;
		if(f0 == 0 && f1 == 1){
			pisano[modulo] = passo;
			return passo;
		}
	}
	return -1;
}
int calcula_fib(int n,int modulo){
	if(n == 0) return 0;
	if(n == 1) return 1;
	int f0 = 0,f1 = 1;
	for(int i = 2;i<=n;i++){
		int nf = (f1 + f0) % modulo;
		f0 = f1;
		f1 = nf;
	}
	return f1;
}
int main(){
	int n,m;
	while(scanf("%d %d",&n,&m) != EOF){
		int c = calcula_periodo(m);
		int d = calcula_periodo(c);
		int fn = calcula_fib(n % d,c);
		int ans = calcula_fib(fn % c,m);
		printf("%d\n",ans);
	}
	return 0;
}
