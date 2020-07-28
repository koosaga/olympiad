// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c5p1
#include <bits/stdc++.h>
using namespace std;
int vetor[17],soma[17];
int main(){
	for(int i=1;i<=8;i++){
		cin >> vetor[i];
		vetor[i+8] = vetor[i];
	}
	int resp = 0;
	for(int i=1;i<=16;i++){
		soma[i] = soma[i-1] + vetor[i];
	}
	for(int ini = 1,fim = 4;fim <= 16;ini++,fim++){
		resp = max(resp, soma[fim] - soma[ini-1] );
	}
	cout << resp << endl;
	return 0;
}