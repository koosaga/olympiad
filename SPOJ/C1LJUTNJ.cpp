// Ivan Carvalho
// Solution to https://www.spoj.com/problems/C1LJUTNJ/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int N,M;
vector<ii> guloso;
ll resposta;

int main(){

	scanf("%d %d",&M,&N);
	guloso.push_back(ii(0,0));
	for(int i = 1;i<=N;i++){
		int x;
		scanf("%d",&x);
		guloso.push_back(ii(x,1));
	}
	sort(guloso.begin(),guloso.end());

	while(M > 0){
		int diferenca = guloso.back().first - guloso[guloso.size() - 2].first,tamanho = guloso.back().second;
		//printf("Diferenca %d Tamanho %d\n",diferenca,tamanho);
		ll precisa = diferenca*guloso.back().second;
		if(precisa <= M){
			M -= precisa;
			guloso.pop_back();
			guloso.back().second += tamanho;
		}
		else{
			ll paratodos = M/tamanho;
			ll resta = M % tamanho;
			guloso.back().first -= paratodos;
			guloso.back().second -= resta;
			guloso.push_back(ii(guloso.back().first - 1,resta));
			M = 0;
		}
	}
	
	for(ii pares : guloso){
		resposta += 1LL*pares.first*pares.first*pares.second;
	}

	printf("%lld\n",resposta);

	return 0;
}
