#include "cmp.h"
#include <vector>
#include <algorithm>
using namespace std;

// 3 + 3 + 8
void remember(int n) {
	n += 4096;
	while(n > 1){
		bit_set(n);
		n >>= 3;
	}
}

// [4096~8191] [512~1023] [64~127] [8~15] [1]

int compare(int b) {
	b += 4096;
	vector<int> v;
	v.push_back(3000); // suwon - gangnam
	while(b > 1){
		v.push_back(b);
		b >>= 3;
	}
	reverse(v.begin(), v.end());
	int s = 0, e = v.size() - 1;
	while(s != e){
		int m = (s+e)/2;
		if(!bit_get(v[m])) e = m;
		else s = m+1;
	}
	if(v[s] == 3000) return 0;
	if(v[s] % 8 <= 3){
		for(int i=0; i<v[s] % 8; i++){
			if(bit_get(v[s] - v[s] % 8 + i)){
				return 1;
			}
		}
		return -1;
	}
	else{
		for(int i=v[s] % 8 + 1; i<8; i++){
			if(bit_get(v[s] - v[s] % 8 + i)){
				return -1;
			}
		}
		return 1;
	}
}