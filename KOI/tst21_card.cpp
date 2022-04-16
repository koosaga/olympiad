#include <bits/stdc++.h>
using namespace std;

bool reversal(int N, int K, vector<string> C){
	for(int i = K; i < N; i++){
		for(int j = K; j < N; j++){
			if(C[i][j] ^ C[i-K][j] ^ C[i][j-K] ^ C[i-K][j-K]) return 0;
		}
	}
	return 1;
}
