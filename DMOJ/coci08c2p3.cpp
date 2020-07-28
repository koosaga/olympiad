// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci08c2p3
#include <bits/stdc++.h>
using namespace std;

int main(){

	int N;
	cin >> N;

	vector<int> A(N),B(N);
	for(int i = 0;i<N;i++){
		cin >> A[i] >> B[i];
	}

	int best = abs(A[0] - B[0]);

	for(int bitmask = 1;bitmask<(1 << N);bitmask++){
		int produto = 1, soma = 0;
		for(int i = 0;i<N;i++){
			if(!(bitmask & (1 << i))) continue;
			produto *= A[i];
			soma += B[i];
		}
		best = min(best, abs(soma - produto) );
	}

	printf("%d\n",best);

	return 0;

}