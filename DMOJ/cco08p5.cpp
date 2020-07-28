// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco08p5
#include <bits/stdc++.h>
using namespace std;
int N,K[101],C[101],tot;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%d %d",&K[i],&C[i]);
		tot += K[i]*C[i];
	}
	bitset<10000001> BS;
	BS.set(0);
	for(int i=1;i<=N;i++){
		int copia = K[i];
		vector<int> pot;
		for(int j = 0;(1 << j) <= K[i];j++){
			if(copia - (1 << j) > 0){
				pot.push_back((1 << j));
				copia -= (1 << j);
			}
		}
		pot.push_back(copia);
		for(int j : pot){
			BS |= BS << (C[i]*j);
		}
	}
	int best = tot;
	for(int v = 0;v<=tot;v++){
		if(BS[v] == 1){
			best = min(best, abs(tot - 2*v) );
		}
	}
	printf("%d\n",best);
	return 0;
}
