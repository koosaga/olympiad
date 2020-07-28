// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p2
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

int main(){

	map<int,int> frequencias;
	deque<ii> sequencia;
	int N,vez = 0;

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		int x;
		scanf("%d",&x);
		frequencias[x]++;
	}
	for(map<int,int>::iterator it = frequencias.begin();it != frequencias.end();it++){
		sequencia.push_back(*it);
	}

	while(sequencia.size() > 3){
		int minimo = min(sequencia.front().second,sequencia.back().second);
		sequencia.front().second -= minimo;
		sequencia[1].second += minimo;
		sequencia.back().second -= minimo;
		sequencia[sequencia.size() - 2].second += minimo;
		if(sequencia.front().second == 0) sequencia.pop_front();
		if(sequencia.back().second == 0) sequencia.pop_back();
	}
	while(sequencia.size() == 3){
		if(vez == 0){
			vez ^= 1;
			sequencia.front().second -= 1;
			sequencia[1].second += 1;
			if(sequencia.front().second == 0) sequencia.pop_front();
		}
		else{
			vez ^= 1;
			sequencia.back().second -= 1;
			sequencia[sequencia.size() - 2].second += 1;
			if(sequencia.back().second == 0) sequencia.pop_back();
		}
	}

	if(vez == 0) printf("Slavko\n");
	else printf("Mirko\n");
	printf("%d %d\n",sequencia.front().first,sequencia.back().first);

	return 0;
}
