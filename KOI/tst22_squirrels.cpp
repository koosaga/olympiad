#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;
 
long long fly(vector<int> D, vector<int> H, vector<int> W, int L, int R){
	map<lint, lint> slopes;
	slopes[0] = L;
	slopes[W[0]] += H[0] - L;
	lint ret = 0;
	lint toRemove;
	auto popBegin = [&](){
		while(toRemove > 0 && sz(slopes)){
			auto x = *slopes.begin();
			slopes.erase(slopes.begin());
			lint delta = min(toRemove, x.second);
			toRemove -= delta;
			x.second -= delta;
			ret += delta * x.first;
			if(x.second > 0){
				slopes.insert(x);
			}
		}
	};
	auto popEnd = [&](){
		while(toRemove > 0 && sz(slopes)){
			auto x = *slopes.rbegin();
			slopes.erase(--slopes.end());
			lint delta = min(toRemove, x.second);
			toRemove -= delta;
			x.second -= delta;
			if(x.second > 0){
				slopes.insert(x);
			}
		}
	};
	for(int i = 1; i < sz(H); i++){
		toRemove = D[i] - D[i - 1];
		popBegin();
		if(toRemove > 0) return -1;
		lint curcap = H[i - 1] - (D[i] - D[i - 1]);
		assert(curcap >= 0);
		if(curcap > H[i]){
			toRemove = curcap - H[i];
			popEnd();
		}
		else if(curcap < H[i]){
			slopes[W[i]] += H[i] - curcap;
		}
		while(slopes.rbegin()->first > W[i]){
			auto x = *slopes.rbegin();
			slopes.erase(--slopes.end());
			slopes[W[i]] += x.second;
		}
	}
	toRemove = R;
	popBegin();
	return ret;
}
 
