#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

namespace {

int variable_example = 0;

int FunctionExample(int P) { return 1 - P; }

}  // namespace

void Bruno(int N, int L, std::vector<int> A) {
	auto convertBackward = [&](lint X){
		vector<lint> dp(64);
		dp[0] = 1;
		dp[1] = 2;
		for(int i = 2; i <= 63; i++){
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		lint ret = 0;
		for(int i = 62; i >= 0; i--){
			if(X >= dp[i]){
				X -= dp[i];
				ret += (1ll << i);
			}
		}
		return ret;
	};
	vector<int> w;
	int leftmostX = 0, rightmostZ = 0;
	int M = sz(A) - 34;
	for(int i = 16; i >= 0; i--){
		leftmostX <<= 1;
		rightmostZ <<= 1;
		leftmostX += A[M + i];
		rightmostZ += A[M + 17 + i];
	}
	if(leftmostX >= rightmostZ){
		for(int i = 0; i < N; i++) Remove(i);
		return;
	}
	for(int i = 0; i < leftmostX; i++) Remove(i);
	for(int i = rightmostZ+1; i < N; i++) Remove(i);
	vector<int> B;
	for(int i = 0; i < M; i += 44){
		lint conv = 0;
		for(int j = 0; j < 44; j++){
			conv |= ((1ll * A[i+j]) << j);
		}
		lint ans = convertBackward(conv);
		for(int j = 0; j < 63; j++){
			B.push_back((ans >> j) & 1);
		}
	}
	A = B;
	for(int i = leftmostX; i <= rightmostZ; i++){
		if(A[i]) w.push_back(i);
	}
	w.insert(w.begin(), leftmostX);
	for(int i = 1; i < sz(w); i++){
		for(int j = w[i] - 1; j > w[i-1]; j--) Remove(j);
		Remove(w[i]);
	}
	Remove(leftmostX);
}
