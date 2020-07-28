// Ivan Carvalho
// Solution to https://dmoj.ca/problem/valentines18s5
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int carol[MAXN],N,K;

inline int gcd(int x,int y){
	while(x != 0 && y != 0){
		if(x < y) swap(x,y);
		x = x % y;
	}
	return max(x,y);
}

int main(){

	scanf("%d %d",&N,&K);
	for(int i = 2;i<MAXN;i++){
		if(carol[i] != 0) continue;
		for(int j = i;j<MAXN;j+=i){
			int copia = j;
			while(copia % i == 0){
				copia /= i;
				carol[j]++;
			}
		}
	}


	long long somatorio = 0;

	map<int,int> mapa;

	for(int i = 1;i<=N;i++){
		int x;
		scanf("%d",&x);
		mapa[0]++;
		map<int,int> novomapa;
		for(map<int,int>::iterator it = mapa.begin();it != mapa.end();it++){
			int y = (*it).first, freq = (*it).second;
			//printf("Y %d\n",y);
			y = gcd(x,y);
			if(carol[y] == K) somatorio += freq;
			novomapa[y] += freq;
		}
		mapa = novomapa;
		//printf("Oi\n");
	}
	
	printf("%lld\n",somatorio);

	return 0;
}