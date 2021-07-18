#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

namespace {

int variable_example = 0;

}

void Anna(int N, std::vector<char> S) {
	auto convertForward = [&](lint X){
		vector<lint> dp(64);
		dp[0] = 1;
		dp[1] = 2;
		for(int i = 2; i <= 63; i++){
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		lint ret = 0;
		for(int i = 63; i >= 0; i--){
			if((X >> i) & 1) ret += dp[i];
		}
		return ret;
	};
	int lowestX = N - 1;
	int highestZ = 0;
	for(int i = 0; i < sz(S); i++){
		if(S[i] == 'X'){
			lowestX = i;
			break;
		}
	}
	for(int i = sz(S) - 1; i >= 0; i--){
		if(S[i] == 'Z'){
			highestZ = i;
			break;
		}
	}
	for(int i = 0; i < N; i++){
		if(S[i] == 'Z'){
			int e = i;
			while(e < N && S[e] == 'Z') e++;
			for(int j = i; j < e-1; j++) S[j] = 'X';
			i = e;
		}
	}
	while(sz(S) % 63) S.push_back('X');
	for(int i = 0; i < sz(S) / 63; i++){
		lint ans = 0;
		for(int j = 0; j < 63; j++){
			if(S[i*63+j] == 'Z') ans |= (1ll << j);
		}
		lint conv = convertForward(ans);
		for(int j = 0; j < 44; j++) Send((conv >> j) & 1);
	}
	for(int i = 0; i < 17; i++) Send((lowestX >> i) & 1);
	for(int i = 0; i < 17; i++) Send((highestZ >> i) & 1);
}
