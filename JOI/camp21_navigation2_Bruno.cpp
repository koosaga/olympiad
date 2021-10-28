#include "Bruno.h"
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

std::vector<int> Bruno(int K, std::vector<int> value) {
	int A[3][3] = {};
	int B[3][3] = {}, piv = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			A[i][j] = value[i*3+j];
			if(A[i][j] == 12) B[i][j] = 12;
		}
	}
	pi center = extract_pattern(A, 12);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(!B[(center.first + i) % 3][(center.second + j) % 3]){
				B[(center.first + i) % 3][(center.second + j) % 3] = ++piv;
			}
		}
	}
	vector<int> res;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			int v = A[(center.first + i) % 3][(center.second + j) % 3];
			if(v == 12) continue;
			if(sz(res) == K) continue;
			if(v <= 4) res.push_back(v - 1);
			else{
				//printf("%d goes %d\n", sz(res), v - 4);
				v -= 4;
				// check perspective of where.
				for(int k = 0; k < 3; k++){
					for(int l = 0; l < 3; l++){
						if(B[k][l] == v){
							int new_x = (center.first + i) % 3;
							int new_y = (center.second + j) % 3;
							while((new_x + 369) % 3 != (k + 2) % 3) new_x--;
							while((new_y + 369) % 3 != (l + 2) % 3) new_y--;
						//	printf("offset is %d %d\n", new_x, new_y);

							if(new_x > 0) res.push_back(2);
							else if(new_x < 0) res.push_back(3);
							else if(new_y > 0) res.push_back(0);
							else if(new_y < 0) res.push_back(1);
							else res.push_back(4);
						}
					}
				}
			}
		}
	}
	return res;
}
