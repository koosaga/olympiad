// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1030
#include <cstdio>
int josephus(int n, int k){
	if (n==1) return 1;
	return (josephus(n-1,k)+k-1) % n + 1;
}
int main(){
	int cases;
	scanf("%d",&cases);
	for(int i=1;i<=cases;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		printf("Case %d: %d\n",i,josephus(u,v));
	}
	return 0;
}
