// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1471
#include <cstdio>
#include <set>
using namespace std;
int main(){
	int n,m;
	while(scanf("%d %d",&n,&m)!=EOF){
		set<int> conjunto;
		int perdidos = 0;
		for(int i=0;i<m;i++){
			int davez;
			scanf("%d",&davez);
			conjunto.insert(davez);
		}
		for(int i=1;i<=n;i++) if(!conjunto.count(i)) {
			printf("%d ",i);
			perdidos++;
		}
		if (!perdidos) printf("*"); 
		printf("\n");
	}
	return 0;
}
