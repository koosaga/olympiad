// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c4p4
#include <cstdio>
#include <set>
using namespace std;
set<int> cjt[2010];
int soma[100010],n,q,k;
int main(){
	scanf("%d %d %d",&n,&k,&q);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		cjt[davez+1001].insert(i);
		soma[i] = soma[i-1] + davez;
	}
	while(q--){
		int a,b,x,y;
		scanf("%d %d %d %d",&a,&b,&x,&y);
		set<int>::iterator it1 = cjt[a+1001].lower_bound(x);
		if(it1 == cjt[a+1001].end()){
			printf("No\n");
			continue;
		}
		else if(*it1 > y){
			printf("No\n");
			continue;
		}
		set<int>::iterator it2 = cjt[b+1001].lower_bound(x);
		if(it2 == cjt[b+1001].end()){
			printf("No\n");
			continue;
		}
		else if(*it2 > y){
			printf("No\n");
			continue;
		}
		if(soma[y] - soma[x-1] <= k){
			printf("No\n");
			continue;
		}
		printf("Yes\n");
	}
	return 0;
}