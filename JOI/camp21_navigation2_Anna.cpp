#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

namespace {
	const int dx[4] = {0, 1, 1, 1};
	const int dy[4] = {1, -1, 0, 1};
	pi extract_pattern(int A[3][3], int eq){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(A[i][j] == eq){
					for(int k = 0; k < 4; k++){
						if(A[(i + dx[k] + 3) % 3][(j + dy[k] + 3) % 3] == eq){
							return pi(i, j);
						}
					}
				}
			}
		}
		assert(0);
	}
} // namespace

void Anna(int N, int K, std::vector<int> R, std::vector<int> C) {
	int chk[3][3] = {};
	for(int i = 0; i < K; i++){
		chk[R[i] % 3][C[i] % 3] = 1;
	}
	int cnt = 0;
	int A[3][3] = {};
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(!chk[i][j] && cnt < 2){
				A[i][j] = 12;
				cnt++;
			}
		}
	}
	int piv = 0;
	pi center = extract_pattern(A, 12);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(!A[(center.first + i) % 3][(center.second + j) % 3]){
				A[(center.first + i) % 3][(center.second + j) % 3] = ++piv;
			}
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(A[i%3][j%3] == 12) SetFlag(i, j, 12);
			else{
				int to_seek = A[i%3][j%3] - 1;
				if(to_seek >= K){
					SetFlag(i, j, 11);
					continue;
				}
				if(abs(R[to_seek] - i) >= 2 || abs(C[to_seek] - j) >= 2){
					if(R[to_seek] >= i + 2) SetFlag(i, j, 3);
					else if(R[to_seek] <= i - 2) SetFlag(i, j, 4);
					else if(C[to_seek] >= j + 2) SetFlag(i, j, 1);
					else if(C[to_seek] <= j - 2) SetFlag(i, j, 2);
					else assert(0);
				}
				else{
					SetFlag(i, j, 4 + A[R[to_seek] % 3][C[to_seek] % 3]);
				}
			}
		}
	}
}
