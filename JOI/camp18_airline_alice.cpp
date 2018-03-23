#include "Alicelib.h"
#include <bits/stdc++.h>
using namespace std;

void Alice( int N, int M, int A[], int B[] ){
	using pi = pair<int, int>;
	if(N == 1){
		InitG(1, 0);
		return;
	}
	if(N == 2 && M == 0){
		InitG(2, 0);
		return;
	}
	if(N == 2 && M == 1){
		InitG(3, 0);
		return;
	}
	int idx[1024] = {};
	int pcnt[1024] = {};
	for(int i=1; i<=1023; i++) pcnt[i] = pcnt[i/2] + i%2;
	int ptr = 0;
	for(int i=0; i<N; i++){
		while(pcnt[ptr] >= 9) ptr++;
		idx[i] = ptr++;
	}
	vector<pi> v;
	for(int i=0; i<M; i++) v.emplace_back(A[i], B[i]);
	for(int i=0; i<N; i++) v.emplace_back(i, N);
	for(int i=0; i<9; i++) v.emplace_back(N + i + 1, N + i + 2);
	for(int i=0; i<10; i++){
		for(int j=0; j<N; j++){
			if((idx[j] >> i) & 1) v.emplace_back(j, N + i + 1);
		}
	}
	for(int i=0; i<N+11; i++){
		if(i != N) v.emplace_back(i, N + 11);
	}
	InitG(N + 12, v.size());
	for(int i=0; i<v.size(); i++){
		MakeG(i, v[i].first, v[i].second);
	}
}

