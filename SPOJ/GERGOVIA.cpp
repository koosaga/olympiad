// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GERGOVIA/
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <deque>
#include <algorithm>
using namespace std;
int main(){
	int n;
	while(scanf("%d",&n) && n){
		long long int resposta = 0;
		queue< pair<int,int> > comprar;
		deque< pair<int,int> > vender;
		for(int i=0;i<n;i++){
			int davez;
			scanf("%d",&davez);
			if (davez>0) comprar.push(make_pair(davez,i));
			if (davez<0) vender.push_back(make_pair(-davez,i));
		}
		while (!comprar.empty()){
			pair<int,int> frente=comprar.front();
			int c = frente.first, indice = frente.second;
			comprar.pop();
			while (c>0){
				pair<int,int> v = vender.front();
				vender.pop_front();
				int troca = min(v.first,c);
				c -= troca;
				if (troca != v.first) vender.push_front(make_pair(v.first-troca,v.second));
				resposta += abs(v.second - indice)*troca;
			}
		}
		printf("%lld\n",resposta);
	}
	return 0;
}