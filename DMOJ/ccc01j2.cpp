// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc01j2
#include <cstdio>
int main(){
	int x,m;
	scanf("%d %d",&x,&m);
	for(int i=1;i<m;i++){
		if((x*i) % m == 1){
			printf("%d\n",i);
			return 0;
		}
	}
	printf("No such integer exists.\n");
	return 0;
}