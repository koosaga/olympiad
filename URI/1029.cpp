// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1029
#include <cstdio>
long long int resp[50],fib[50];
long long int fibo(int x){
	if (fib[x]!=-1) return fib[x];
	fib[x] = fibo(x-1) + fibo(x-2);
	return fib[x];
}
long long int calls(int y){
	if (resp[y]!=-1) return resp[y];
	resp[y] = 2 + calls(y-1) + calls(y-2);
	return resp[y];
}
int main(){
	int casos,i,davez,temp;
	for (int i=0;i<50;i++) {
		resp[i]=-1;
		fib[i]=-1;
	}
	fib[0]=0;
	fib[1]=1;
	fib[2]=1;
	resp[0]=0;
	resp[1]=0;
	resp[2]=2;
	scanf("%d",&casos);
	for(i=0;i<casos;i++){
		scanf("%d",&davez);
		printf("fib(%d) = %lld calls = %lld\n",davez,calls(davez),fibo(davez));
	}
	return 0;
}
