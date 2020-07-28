// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1397
#include <cstdio>
int main(){
	int n;
	while(scanf("%d",&n) && n){
		int a = 0, b = 0;
		while(n--){
			int x,y;
			scanf("%d %d",&x,&y);
			a += int(x>y);
			b += int(x<y);
		}
		printf("%d %d\n",a,b);
	}
	return 0;
}
