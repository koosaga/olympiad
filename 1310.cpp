// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1310
#include <cstdio>
#define max(A,B) (A>B) ? (A) : (B)
int main(){
	int n,m;
	while(scanf("%d",&n)!=EOF){
		scanf("%d",&m);
		int max_so_far = 0, max_until_here = 0;
		for(int i=0;i<n;i++){
			int davez;
			scanf("%d",&davez);
			davez -= m;
			max_until_here = max(max_until_here+davez,0);
			max_so_far = max(max_so_far,max_until_here);
		}
		printf("%d\n",max_so_far);
	}
	return 0;
}
