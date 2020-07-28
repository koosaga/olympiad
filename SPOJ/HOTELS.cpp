// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HOTELS/
#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
int main(){
	int soma = 0,resposta=0,n,m;
	deque<int> janela;
	scanf("%d %d",&n,&m);
	while(n--){
		int davez;
		scanf("%d",&davez);
		soma += davez;
		janela.push_back(davez);
		while(soma > m){
			soma -= janela.front();
			janela.pop_front();
		}
		resposta = max(resposta,soma);
	}
	printf("%d\n",resposta);
	return 0;
}