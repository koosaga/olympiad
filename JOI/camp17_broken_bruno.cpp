#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;

long long Bruno( int N, int A[] ){
	vector<int> ans;
	for(int i=0; i<150; i+=3){
		int val = (A[i] << 2) | (A[i+1] << 1) | (A[i+2]);
		if(val == 1){
			ans.push_back(0);
		}
		if(val == 2){
			ans.push_back(1);
		}
		if(val == 3){
			ans.push_back(1);
			ans.push_back(0);
		}
		if(val == 4){
			ans.push_back(0);
			ans.push_back(0);
		}
		if(val == 5){
			ans.push_back(1);
		}
		if(val == 6){
			ans.push_back(0);
			ans.push_back(1);
		}
		if(val == 7){
			ans.push_back(1);
			ans.push_back(1);
		}
	}
	long long dap = 0;
	assert(ans.size() >= 60);
	for(int i=0; i<60; i++){
		if(ans[i]) dap |= (1ll << i);
	}
	return dap;
}
