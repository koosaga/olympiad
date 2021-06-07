#include <bits/stdc++.h>
#include "swaps.h"
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

void solve(int n, int _){
	vector<int> ord(n);
	iota(all(ord), 1);
	while(n != (n & -n)) n += (n & -n);
	for(int step = 2; step <= n; step <<= 1){
		vector<pi> buffer;
		auto swap = [&](int x, int y){
			if(y >= sz(ord)) return;
			buffer.emplace_back(x, y);
		};
		auto flush = [&](){
			if(sz(buffer) == 0) return;
			for(auto &[x, y] : buffer){
				schedule(ord[x], ord[y]);
			}
			auto ans = visit();
			for(int i = 0; i < sz(ans); i++){
				int x, y; tie(x, y) = buffer[i];
				if(!ans[i]) std::swap(ord[x], ord[y]);
			}
			buffer.clear();
		};
		for(int j = 0; j < n; j += step){
			for(int k = 0; k < step / 2; k++){
				swap(j + k, j + step - k - 1);
			}
		}
		flush();
		for(int j = step / 4; j >= 1; j >>= 1){
			for(int k = 0; k < n; k++){
				if((j & k) == 0) swap(k, k + j);
			}
			flush();
		}
	}
	answer(ord);
}


