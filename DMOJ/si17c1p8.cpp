// Ivan Carvalho
// Solution to https://dmoj.ca/problem/si17c1p8
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
int V[MAXN],T,N;
int main(){
	cin >> N >> T;
	for(int i = 0;i<N;i++) cin >> V[i];
	int resposta = 0;
	for(int bitmask = 1;bitmask< (1 << N);bitmask++){
		int total = 0;
		for(int i = 0;i<N;i++){
			if(bitmask & (1 << i)) total += V[i];
		}
		if(total == T) resposta++;
	}
	printf("%d\n",resposta);
	return 0;
}