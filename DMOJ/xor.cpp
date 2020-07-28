// Ivan Carvalho
// Solution to https://dmoj.ca/problem/xor
#include <cstdio>
int xor1(int x){
	if(x % 4 ==0) return x;
	if(x%4==1) return 1;
	if(x%4==2) return x+1;
	return 0;
}
int main(){
	int T,a,b;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&a,&b);
		printf("%d\n",xor1(a-1)^xor1(b));
	}
	return 0;
}