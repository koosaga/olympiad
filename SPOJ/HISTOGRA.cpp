// Ivan Carvalho
// Solution to https://www.spoj.com/problems/HISTOGRA/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 100010;
int vetor[MAXN],antes[MAXN],depois[MAXN],n;
long long resposta;
int main(){
	while(scanf("%d",&n) && n){
		resposta = 0;
		for(int i = 1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		vetor[0] = -1;vetor[n+1] = -1;
		stack<ii> pilha;
		pilha.push(ii(-1,0));
		for(int i = 1;i<=n+1;i++){
			ii davez = ii(vetor[i],i);
			while(pilha.top().first > davez.first ){
				depois[pilha.top().second] = i;
				pilha.pop();
			}
			if(pilha.top().first == davez.first){
				antes[i] = antes[pilha.top().second];
			}
			else{
				antes[i] = pilha.top().second;
			}
			pilha.push(davez);
		}
		for(int i = 1;i<=n;i++){
			antes[i]++;depois[i]--;
			resposta = max(resposta, 1LL*(depois[i] - antes[i] + 1)*vetor[i] );
		}
		printf("%lld\n",resposta);
	}
	return 0;
}