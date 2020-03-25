#include "Catherine.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;


namespace {
	int A;
	bool determined = 0;
	vector<int> prev_seq;
}  // namespace

void Init(int A, int B) {
	::A = A;
}

bool bad_sign(vector<int> v){
	if(sz(v) >= 4){
		reverse(all(v));
		v.resize(4);
		reverse(all(v));
		if(v == vector<int>({1, 1, 0, 1})) return 1;
		if(v == vector<int>({0, 1, 0, 0})) return 1;
		if(v == vector<int>({1, 0, 1, 0})) return 1;
		if(v == vector<int>({0, 0, 1, 1})) return 1;
		return 0;
	}
	return 0;
}

int Move(std::vector<int> y) {
	if(A >= 3){
		if(sz(prev_seq)) y[prev_seq.back()]++;
		int ans = -1;
		for(int i=0; i<sz(y); i++){
			if(y[i]){
				if(y[(i + A - 1) % sz(y)]) ans = (i + A - 1) % A;
				else ans = i;
				break;
			}
		}
		prev_seq.push_back(ans);
		return ans;
	}
	int deg = accumulate(all(y), 0) + (sz(prev_seq) > 0);
	if(deg == 1){
		determined = 1;
		if(sz(prev_seq)){
			prev_seq.push_back(prev_seq.back());
			return -1;
		}
		int pos = find(all(y), 1) - y.begin();
		prev_seq.push_back(pos);
		return pos;
	}
	if(deg != 2){
		determined = 1;
		if(sz(prev_seq)){
			if(y[prev_seq.back()] == 0){
				prev_seq.push_back(prev_seq.back());
				return -1;
			}
			y[prev_seq.back()]++;
		}
		for(int i=0; i<sz(y); i++){
			if(y[i] == 1){
				prev_seq.push_back(i);
				return i; 
			}
		}
		assert(0);
	}
	vector<int> cands;
	for(int i=0; i<sz(y); i++){
		for(int j=0; j<y[i]; j++) cands.push_back(i);
	}
	if(sz(cands) == 2){
		prev_seq = cands;
		swap(prev_seq[0], prev_seq[1]);
	}
	else{
		prev_seq.push_back(cands[0]);
	}
	if(!determined && bad_sign(prev_seq)){
		determined = 1;
		prev_seq.pop_back();
		prev_seq.push_back(prev_seq.back());
		return -1;
	}
	return cands[0];
}
