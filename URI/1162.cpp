// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1162
#include <cstdio>
#include <set>
#include <iterator>
using namespace std;
int main(){
	int casos,n;
	scanf("%d",&casos);
	for(int j=0;j<casos;j++){
		scanf("%d",&n);
		multiset<int> conjunto;
		int inversoes = 0;
		for(int i=1;i<=n;i++) {
			int davez;
			scanf("%d",&davez);
			conjunto.insert(davez);
			inversoes += distance(conjunto.upper_bound(davez),conjunto.end());
		}
		printf("Optimal train swapping takes %d swaps.\n",inversoes);
	}
	return 0;
}
