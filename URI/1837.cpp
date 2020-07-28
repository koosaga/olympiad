// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1837
#include <cstdio>
#include <cstdlib>
int main(){
	int a,b,q,r;
	scanf("%d %d",&a,&b);
	q = a/b;
	r = a % b;
	if (r < 0){
		for(r=0;r<=abs(b);r++){
			q = (a-r)/b;
			if (a== b*q + r) break;
		}
	}
	printf("%d %d\n",q,r);
	return 0;
}
