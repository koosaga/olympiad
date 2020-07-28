// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c5p1
#include <cstdio>
int main(){
	int a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	if(a + b == c){
		printf("%d+%d=%d\n",a,b,c);
		return 0;
	}
	if(a == b + c){
		printf("%d=%d+%d\n",a,b,c);
		return 0;
	}
	if(a - b == c){
		printf("%d-%d=%d\n",a,b,c);
		return 0;
	}
	if(a == b - c){
		printf("%d=%d-%d\n",a,b,c);
		return 0;
	}
	if(a*b==c){
		printf("%d*%d=%d\n",a,b,c);
		return 0;
	}
	if(a==b*c){
		printf("%d=%d*%d\n",a,b,c);
		return 0;
	}
	if(b != 0 && a / b == c){
		printf("%d=%d/%d\n",a,b,c);
		return 0;
	}
	if(c != 0 && a == b /c){
		printf("%d=%d/%d\n",a,b,c);
	}
	return 0;
}