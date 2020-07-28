// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc09s1
#include <cstdio>
inline int pow(int a){
	return a*a*a*a*a*a;
}
int main(){
	int a,b;
	scanf("%d %d",&a,&b);
	int resp = 0;
	for(int i=1;i<=23;i++){
		if(pow(i) >= a && pow(i) <= b) resp++;
	}
	printf("%d\n",resp);
	return 0;
}