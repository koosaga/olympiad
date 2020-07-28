// Ivan Carvalho
// Solution to https://dmoj.ca/problem/odd
#include <cstdio>
int main(){
	int n,resp = 0;
	scanf("%d",&n);
	while(n--){
		int d;
		scanf("%d",&d);
		resp ^= d;
	}
	printf("%d\n",resp);
	return 0;
}