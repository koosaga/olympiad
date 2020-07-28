// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bf3
#include <cstdio>
int primality(int x){
	if(x  <= 1) return 0; 
	if(x == 2 || x == 3) return 1;
	if(x % 2 == 0 || x % 3 == 0) return 0;
	for(int i = 5;i*i <= x;i += 6){
		if(x % i == 0) return 0;
		if(x % (i+2) == 0) return 0;
	}
	return 1;
}
int main(){
	int n;
	scanf("%d",&n);
	int limit = 0;
	for(int i=0;i<=30;i++) limit += (1<<i);
	for(int i = n;i<=limit;i++){
		if(primality(i)){
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}